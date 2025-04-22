/***********************************************************************************
*** DESCRIPTION : This class does various static string processing.              ***
***********************************************************************************/

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

struct QSjob{
    int low;
    int high;

    QSjob(int oldLow = 0, int oldHigh = 0): low(oldLow), high(oldHigh){}
};

class GeneralFunctions{
    public:
        /***********************************************************************************
        *** FUNCTION GeneralFunctions()                                                  ***
        ************************************************************************************
        *** DESCRIPTION : This is the constructor. It runs when a new inst. is created.  ***
        *** INPUT ARGS : N/A                                                             ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        GeneralFunctions();

        /***********************************************************************************
        *** FUNCTION GeneralFunctions(const GeneralFunctions&)                           ***
        ************************************************************************************
        *** DESCRIPTION : This is the copy constructor. It runs when a new instance is   ***
        ***               created with an Error instance as a paramater.                 ***
        *** INPUT ARGS : GeneralFunctions oldGeneralFunctions                            ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        GeneralFunctions(const GeneralFunctions&);

        /***********************************************************************************
        *** FUNCTION ~GeneralFunctions()                                                 ***
        ************************************************************************************
        *** DESCRIPTION : This is the destructor. It runs when a new inst. is destroyed. ***
        *** INPUT ARGS : N/A                                                             ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        ~GeneralFunctions();

        /***********************************************************************************
        *** FUNCTION vector<string> getCmdArgs(int argc, char* argv[])                   ***
        ************************************************************************************
        *** DESCRIPTION : This function puts cmd line args into a vector of strings      ***
        *** INPUT ARGS : int argc, char* argv[]                                          ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : vector<string> args                                                 ***
        ***********************************************************************************/
        static vector<string> getCmdArgs(int, char*[]);

        /***********************************************************************************
        *** FUNCTION void outputCheck(int, int&)                                         ***
        ************************************************************************************
        *** DESCRIPTION : prompts the user for input of the lineCtr is 0                 ***
        *** INPUT ARGS : int maxLines                                                    ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : int lineCtr                                                    ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        static void outputCheck(int, int&);

        /***********************************************************************************
        *** FUNCTION string reExtendFile(string programFile, string extension)           ***
        ************************************************************************************
        *** DESCRIPTION : This function calculates the name of the reextended file.      ***
        *** INPUT ARGS : string programFile, extension                                   ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : string intFile                                                      ***
        ***********************************************************************************/
        static string reExtendFile(string, string);

        /***********************************************************************************
        *** FUNCTION void openInputFileByName(string, fstream&, bool)                    ***
        ************************************************************************************
        *** DESCRIPTION : This function opens a file by a name passed via string. If the ***
        ***               file does not exist, the function will prompt the user for a   ***
        ***               the file again. FIle is opened for reading                     ***
        *** INPUT ARGS : string searchFile, bool binary                                  ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : fstream& file                                                  ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        static void openInputFileByName(string, fstream&, bool = false);

        /***********************************************************************************
        *** FUNCTION string binaryToHex(vector<bool>, int)                               ***
        ************************************************************************************
        *** DESCRIPTION : This function converts a vector of bools to a hex string.      ***
        *** INPUT ARGS : vector<bool> binaryArray, int outSize                           ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : string output                                                       ***
        ***********************************************************************************/
        static string binaryToHex(const vector<bool>&, int);

        /***********************************************************************************
        *** FUNCTION vector<bool> intToBinary(int, int)                                  ***
        ************************************************************************************
        *** DESCRIPTION : This function converts an integer to an array of bools.        ***
        *** INPUT ARGS : int integer, size;                                              ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : vector<bool> bArray                                                 ***
        ***********************************************************************************/
        static vector<bool> intToBinary(int, int);

        /***********************************************************************************
        *** FUNCTION bool openFileForAppOut(fstream&, string)                            ***
        ************************************************************************************
        *** DESCRIPTION : This function opens a file for (append) output, creating it if ***
        ***               it does not exist.                                             ***
        *** INPUT ARGS : string fileName                                                 ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : fstream file                                                   ***
        *** RETURN : bool success                                                        ***
        ***********************************************************************************/
        static bool openFileForAppOut(fstream& file, string fileName);

        /***********************************************************************************
        *** FUNCTION void printArray(const T*, int)                                      ***
        ************************************************************************************
        *** DESCRIPTION : This function prints the array based on the pointer with the   ***
        ***               length given.                                                  ***
        *** INPUT ARGS : const T* arr, int length                                        ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        template <typename T>
        static void printArray(const T*, int);

        /***********************************************************************************
        *** FUNCTION void printVector(vector<T>&)                                        ***
        ************************************************************************************
        *** DESCRIPTION : This function prints the vector given to it.                   ***
        *** INPUT ARGS : N/A                                                             ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : vector<T> vect                                                 ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        template <typename T>
        static void printVector(const vector<T>&);

        /***********************************************************************************
        *** FUNCTION int binarySearch(const vector<T>&, T)                               ***
        ************************************************************************************
        *** DESCRIPTION : This function preforms a binary search of any given data type. ***
        *** INPUT ARGS : vector<T> data, T query                                         ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : int position                                                        ***
        ***********************************************************************************/
        template <typename T>
        static int binarySearch(const vector<T>&, T);

        /***********************************************************************************
        *** FUNCTION void insertionSort(vector<T>)                                       ***
        ************************************************************************************
        *** DESCRIPTION : This function sorts an integer array in ascending order via    ***
        ***               insertion sort.                                                ***
        *** INPUT ARGS : N/A                                                             ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : vector<T> vect                                                 ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        template <typename T>
        static void insertionSort(vector<T>&);

        /***********************************************************************************
        *** FUNCTION void quickSort(vector<T>&)                                          ***
        ************************************************************************************
        *** DESCRIPTION : This function sorts an integer array in ascending order via    ***
        ***               quick sort. Does not use recursion :). Instead uses a vector   ***
        ***               of "jobs" that store the paramaters needed to run the function.***
        *** INPUT ARGS : N/A                                                             ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : vector<T> vect                                                 ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        template <typename T>
        static void quickSort(vector<T>&);

        /***********************************************************************************
        *** FUNCTION int getNonNegNumber(void)                                           ***
        ************************************************************************************
        *** DESCRIPTION : This function gets a positive integer from the user.           ***
        *** INPUT ARGS : N/A                                                             ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : int num                                                             ***
        ***********************************************************************************/
        /* //TEMPLATE CODE
        static int getNonNegNumber(void);
        */
};

//See documentation included with declaration above
template <typename T>
void GeneralFunctions::printArray(const T* arr, int length){
    for(int i = 0; i < length; i++){
        cout << arr[i];
        if(i != length - 1){
            cout << ", ";
        }
    }
    cout << endl;
}

//See documentation included with declaration above
template <typename T>
void GeneralFunctions::printVector(const vector<T>& vect){
    for(int i = 0; i < vect.size(); i++){
        cout << vect[i];
        if(i != vect.size() - 1){
            cout << ", ";
        }
    }
    cout << endl;
}

//See documentation included with declaration above
template <typename T>
int GeneralFunctions::binarySearch(const vector<T>& data, T query){
    int low = 0;
    int high = data.size() - 1;
    int middle;
    int position = -1;

    while(low <= high){
        middle = (low + high) / 2;
        if(data[middle] == query){
            position = middle;
            break;
        }
        else if(data[middle] > query){
            high = middle - 1;
        }
        else{
            low = middle + 1;
        }
    }

    return position;
}

//See documentation included with declaration above
template <typename T>
void GeneralFunctions::insertionSort(vector<T>& vect){
    int runner;
    int temp;

    for(int i = 1; i < vect.size(); i++){
        if(vect[i] >= vect[i - 1]){
            continue;
        }
        temp = vect[i];
        runner = i - 1;
        while(vect[runner] > temp && runner >= 0){
            vect[runner + 1] = vect[runner];
            runner--;
        }
        vect[runner + 1] = temp;
    }
}

//See documentation included with declaration above
template <typename T>
void GeneralFunctions::quickSort(vector<T>& vect){
    vector<QSjob> jobs;
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
        T pivot = vect[low]; // first element pivot
        T sTemp;

        jobs.pop_back();
        
        while(low < high){
            while(vect[low] <= pivot && low < high){
                low++;
            }
            while(vect[high] > pivot){
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