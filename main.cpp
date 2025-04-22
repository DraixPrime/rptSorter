/*
This program takes in a .rpt files in the input directory ("InputFiles" by default) and divides them amongst an abritrary number
of threads, given by the user at the command line. It will then parse the files, looking for any of the MGI fields in the MGI file 
("MGIs.txt" by default). Mathces will be placed in a number of output files found in the output directory ("Results" by default) 
named with the thread responsible and a sequential identifier. Files will be divided by an arbitary size, given by the user at 
the command line, for use with other programs, such as R, which only allows 5MB files. Within the .rpt files, at least a header and
data line are assumed to be present. The first line is assumed to be the header, and the every subsequent line is assumed to have 
the MGI as the first field, with the fields being deliniated by '|'. THE OUTPUT DIRECTORY WILL NOT BE CLEARED BETWEEN EXECUTIONS. 
MUST EXECUTE PROGRAM IN A POSIX COMPADIABLE OPERATING SYSTEM.

Command line arguments: MaxOutputFileSize NumberOfRequestedThreads
*/

//include libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <filesystem>
#include <string>
#include <iomanip>
#include "GeneralFunctions.h"
#include "StringProcessing.h"

//define constants
#define InputDirectory "InputFiles"
#define MGIfileName "MGIs.txt"
#define OutputDirectory "Results"
namespace fs = std::filesystem;

//other directives
using namespace std;

//data type and global variable declarations
//struct for storing file path and file size
struct FileInfo{
    fs::path filePath;
    long fileSize;

    FileInfo(fs::path oldFilePath = "", long oldFileSize = 0): filePath(oldFilePath), fileSize(oldFileSize){}
};
//struct for passing argument to threads
struct ThreadArgs{
    int vectorIndex;

    ThreadArgs(int oldVectorIndex = 0): vectorIndex(oldVectorIndex){}
};
long maxOutputFileSize;                             //max file size storage
vector<string> requestedMGIs = {};               //vector with all requested MGIs
vector<vector<fs::path>> threadJobData = {{}};   //job assignments for each thread

//function headers
bool validateCmdArg(vector<string>, long&, int&);
bool validateOutputDirectory(fs::path);
void secondFieldQuickSort(vector<FileInfo>&);
bool threadDeploymentManager(int);
void* threadProcessJob(void*);
bool OpenNewOutputFile (fs::path, fs::path, fs::path, ThreadArgs, int, fstream&, fstream&);

//main function
int main(int argc, char* argv[]){
    vector<string> cmdArgs;                                       //storage for command arguments
    fs::path inputPath = fs::current_path() / InputDirectory;     //file path to child directory with the input files
    fs::path outputPath = fs::current_path() / OutputDirectory;   //file path to child directory with the output files
    vector<FileInfo> inputFileData = {};                          //vector for input file listing
    fstream MGIfile;                                              //fstream for file with requested MGIs
    string tempMGI;                                               //current MGI being transferred to var "requestedMGIS"
    int numThreads;                                               //number of requested threads

    //get size of output files from command line
    cmdArgs = GeneralFunctions::getCmdArgs(argc, argv);

    //validate command line arguments (max_output_file_size num_threads)
    if(!validateCmdArg(cmdArgs, maxOutputFileSize, numThreads)){
        return 0;
    }

    //ensures input directory exists
    if(!fs::exists(inputPath) || !fs::is_directory(inputPath)){
        cout << "ERROR: Child Directory \"" << InputDirectory << "\" does not exist." << endl;
        return 0;
    }

    //ensure output directory exists, attempt to create if it does not
    if(!validateOutputDirectory(outputPath)){
        return 0;
    }

    //gathers data for all .rpt files from the input directory
    for(auto& file : fs::directory_iterator(inputPath)){
        if(file.path().extension() == ".rpt"){ // Only .rpt files
            inputFileData.emplace_back(file.path(), fs::file_size(file.path()));
        }
    }

    //sorts files by size
    secondFieldQuickSort(inputFileData);

    //outputs files and thier sizes for verbosity purposes
    cout << inputFileData.size() << " files Found in \"" << ".\\" << InputDirectory << "\":" << endl;
    cout << left << setw(50) << "Name" << "Size" << endl;
    for(int i = 0; i < inputFileData.size(); i++){
        cout << left << setw(50) << inputFileData[i].filePath << inputFileData[i].fileSize << endl;
    }
    cout << endl;

    //open file with relevent MGIs requested, error if not found
    MGIfile.open(MGIfileName, ios::in);
    if(MGIfile.fail() || !MGIfile){
        cout << "ERROR: MGI file: " << MGIfileName << " could not be opened." << endl;
        return 0;
    }

    //read and store MGI entries
    while(!MGIfile.eof()){
        getline(MGIfile, tempMGI);
        requestedMGIs.emplace_back(tempMGI);
    }

    //close opened MGI file
    MGIfile.close();

    //sort requested MGIs for later binary searching
    GeneralFunctions::quickSort(requestedMGIs);

    //pring sorted MGIs for verbosity purposes
    cout << "Filtering data for all entries with the following MGIs:" << endl;
    for(int i = 0; i < requestedMGIs.size(); i++){
        cout << requestedMGIs[i] << endl;
    }
    cout << endl;

    //divide the files amoungst threads via the threadJobDataVector
    threadJobData.resize(numThreads);
    for(int i = 0; i < inputFileData.size(); i++){
        threadJobData[i % numThreads].emplace_back(inputFileData[i].filePath);
    }

/*  //debug code to check job distribution
    for(int i = 0; i < threadJobData.size(); i++){
        for(int j = 0; j < threadJobData[i].size(); j++){
            cout << i << " " << j << " " << threadJobData[i][j] << endl;
        }
    }
*/

    //thread deployment and management
    if(!threadDeploymentManager(numThreads)){
        return 0;
    }

    //report end of program
    cout << "File filtering complete." << endl << endl;

    return 0;
}

//validate first item in vector is a valid integer, and is at least 500 (need some space to work with)
//and the second item is a valid integer at least 0.
bool validateCmdArg(vector<string> cmdArgs, long& outputFileSize, int& numThreds){
    try{
        if(cmdArgs.size() > 0){
            outputFileSize = stoi(cmdArgs[0]);
            if(outputFileSize < 500){
                cout << "ERROR: The first cmd arg (max output file size) must be at least 500." << endl;
                return false;
            }
        }
        else{
            cout << "ERROR: The first cmd arg (max output file size) was not provided." << endl;
            return false;
        }
    }
    catch(invalid_argument){
        cout << "ERROR: The first cmd arg (max output file size) was not a valid integer" << endl;
        return false;
    }

    try{
        if(cmdArgs.size() > 1){
            numThreds = stoi(cmdArgs[1]);
            if(numThreds < 1){
                cout << "ERROR: The second cmd arg (number of requestd therads) must be at least 1." << endl;
                return false;
            }
        }
        else{
            cout << "ERROR: The second cmd arg (number of requestd therads) was not provided." << endl;
            return false;
        }
    }
    catch(invalid_argument){
        cout << "ERROR: The second cmd arg (number of requestd therads) was not a valid integer" << endl;
        return false;
    }

    return true;
}

//check if output directory exists. If it does not, attempt to create it
bool validateOutputDirectory(fs::path outputPath){
    if(!fs::exists(outputPath) || !fs::is_directory(outputPath)){
        try{
            if(fs::create_directory("Results")){
                cout << "Creating output Directory: \"" << ".\\" << OutputDirectory << "\"" << endl << endl;
            } 
            else{
                cout << "Output Directory does not exist and could not be created." << endl;
                return false;
            }
        }
        catch(exception& e){
            cout << "Error: " << e.what() << endl;
            return false;
        }
    }

    return true;
}

//modified GeneralFunctions quick sort that sorts based on the second field of the struct within the passed vector
void secondFieldQuickSort(vector<FileInfo>& vect){
    vector<QSjob> jobs; //vector to act as stack for "recursion"

    jobs.push_back({0, int(vect.size() - 1)});

    while(!jobs.empty()){
        int lowJ = jobs[jobs.size() -1].low;
        int highJ = jobs[jobs.size() -1].high;
        int low = lowJ;
        int high = highJ;
        if(low >= high){ // we are done; this job is terminated
        jobs.pop_back();
            continue;
        }
        FileInfo pivot = vect[low]; // first element pivot
        FileInfo sTemp; 

        jobs.pop_back();
        
        while(low < high){
            while(vect[low].fileSize <= pivot.fileSize && low < high){
                low++;
            }
            while(vect[high].fileSize > pivot.fileSize){
                high--; 
            }                          
            if(low < high){
                sTemp = vect[low];
                vect[low] = vect[high];
                vect[high] = sTemp;
            } 
        }        
        
        vect[lowJ] = vect[high];
        vect[high] = pivot; 

        jobs.push_back({lowJ, high - 1});
        jobs.push_back({high + 1, highJ});
    }
}

//set up thread arguments (identifiers for job index), create and deploy threads, and ensure all jobs are taken.
//If threads cannot be created, move foward with that we could create and try again after previous threads are done.
bool threadDeploymentManager(int numThreads){
    vector<pthread_t> threadUIDs = {};        //UIDs for threads
    int badThreads = 0;                       //counter for bad threads
    vector<int> unfilledJobs = {};            //tracks jobs that could not be completed
    vector<ThreadArgs> threadArgsVect = {};   //storage for thread arguments

    while(numThreads > 0){
        //reset vars
        threadUIDs.clear();
        threadArgsVect.clear();
        threadUIDs.resize(numThreads);
        threadArgsVect.resize(numThreads);

        //seed thread arguments
        for(int i = 0; i < numThreads; i++){
            threadArgsVect[i] = i;
        }

        //create threads, if threads are not created, exec with what we have, then attempt to reallocate the rest.
        //Do so unitl all data is parsed or OS gives us no threads.
        for(int i = 0; i < numThreads; i++){
            if(pthread_create(&threadUIDs[i], nullptr, threadProcessJob, &threadArgsVect[i])){
                badThreads++;
                unfilledJobs.push_back(i);
            }
        }
        if(badThreads > 0){
            if(badThreads == numThreads){
                cout << "Error: No threads could be allocated." << endl;
                return false;
            }
            else{
                cout << "Warning: " << badThreads << " threads were not created; contuning with " << 
                 numThreads - badThreads << " threads." << endl;
            }
        }

        //wait unitl all threads are finished
        for(int i = 0; i < numThreads; i ++){
            pthread_join(threadUIDs[i], nullptr);
        }

        //update "threads_to_go" and reset bad thread counter
        numThreads -= numThreads - badThreads;
        badThreads = 0;
    }

    return true;
}

//each thread will processes its job queue
void* threadProcessJob(void* args){
    ThreadArgs localArgs = *((ThreadArgs*)args);   //the arguments we were passed (our ID)
    fstream inputFile;                             //input fstream (file)
    fstream outputFile;                            //output fstream (file)
    fs::path outputFilePath;                       //outputfile path with appended data
    string currentLine;                            //holds line we are sorting
    string selectedField;                          //holds selected data field for filter checking
    int outputFileSize;                            //size of the current outout file
    int curOutputFile;                             //what output file we are on for the current input file
    fs::path inputFilePath;                        //path of input file
    fs::path baseOutputFilePath;                   //name of output file path without appended data
    string storedHeader;                           //store header in memory in case there is no data and we want no output file

    for(int i = 0; i < threadJobData[localArgs.vectorIndex].size(); i++){
        //reset vars
        curOutputFile = 0;
        inputFilePath = fs::current_path() / InputDirectory / threadJobData[localArgs.vectorIndex][i].filename();
        baseOutputFilePath = fs::current_path() / OutputDirectory / inputFilePath.filename();
        selectedField = "";

        //open file with relevent MGIs requested, error if not found
        inputFile.open(inputFilePath, ios::in);
        if(inputFile.fail() || !inputFile){
            cout << "WARNING: Data file: " << inputFilePath << " could not be opened; skipping." << endl;
            continue;
        }

        //read assumed header and store for the time being
        getline(inputFile, storedHeader);

        //start filtering the input file to the output file
        while(!inputFile.eof()){
            getline(inputFile, currentLine);

            selectedField = StringProcessing::getNextTextBlock(currentLine, '|');

            //if we find a match...
            if(GeneralFunctions::binarySearch(requestedMGIs, selectedField) != -1){
                //get a output file open if the current one is full or we don't have one.
                //Pending no errors, add the header, then test if we can add the data line.
                //Skip file if size is an issue, otherwise add the data
                if(!outputFile || outputFileSize + currentLine.size() > maxOutputFileSize){
                    if(outputFile){
                        outputFile.close();
                        outputFileSize = 0;
                    }
                    if(!OpenNewOutputFile(baseOutputFilePath, outputFilePath, inputFilePath, localArgs, curOutputFile, outputFile, 
                        inputFile)){
                        break;
                    }
                    else{
                        curOutputFile++;
                    }
                    if(storedHeader.size() + currentLine.size() > maxOutputFileSize){
                        cout << "WARNING: Header and 1st (output) data line for output file: " << outputFilePath 
                         << " and input file: " << inputFilePath << " exceeds max file size. Skipping." << endl;
                        break;
                    }
                    else{
                        outputFile << storedHeader << endl << currentLine << endl;
                        outputFileSize = storedHeader.size() + currentLine.size();
                    }
                }
                else{
                    outputFile << currentLine << endl;
                    outputFileSize += currentLine.size();
                }
            }
        }
        
        //close current files, if they are open (can be in different states with errors)
        if (inputFile.is_open()) {
            inputFile.close();
        }
        if (outputFile.is_open()) {
            outputFile.close();
        }
    }

    pthread_exit(nullptr);
}

bool OpenNewOutputFile (fs::path baseOutputFilePath, fs::path outputFilePath, fs::path inputFilePath, ThreadArgs localArgs, 
 int curOutputFile, fstream& outputFile, fstream& inputFile){

    //generate next output file name
    outputFilePath = GeneralFunctions::reExtendFile(baseOutputFilePath, "_filteredData_thread" + 
        to_string(localArgs.vectorIndex + 1) + "file" + to_string(curOutputFile + 1) + ".rpt");
    //create a new output file
    outputFile.open(outputFilePath, ios::trunc | ios::out);
    if(outputFile.fail() || !outputFile){
        cout << "WARNING: Data file: " << outputFilePath << " could not be created; skipping " << inputFilePath << endl;
        inputFile.close();
        return false;
    }

    return true;
}