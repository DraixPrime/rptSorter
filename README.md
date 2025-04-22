This program takes in a .rpt files in the input directory ("InputFiles" by default) and divides them amongst an abritrary number
of threads, given by the user at the command line. It will then parse the files, looking for any of the MGI fields in the MGI file 
("MGIs.txt" by default). Mathces will be placed in a number of output files found in the output directory ("Results" by default) 
named with the thread responsible and a sequential identifier. Files will be divided by an arbitary size, given by the user at 
the command line, for use with other programs, such as R, which only allows 5MB files. Within the .rpt files, at least a header and
data line are assumed to be present. The first line is assumed to be the header, and the every subsequent line is assumed to have 
the MGI as the first field, with the fields being deliniated by '|'. THE OUTPUT DIRECTORY WILL NOT BE CLEARED BETWEEN EXECUTIONS. 
MUST EXECUTE PROGRAM IN A POSIX COMPADIABLE OPERATING SYSTEM.

Command line arguments: MaxOutputFileSize NumberOfRequestedThreads
