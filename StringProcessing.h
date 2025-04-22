/***********************************************************************************
*** DESCRIPTION : This class does various static string processing.              ***
***********************************************************************************/

#pragma once

#include <iostream>

using namespace std;

class StringProcessing{
    public:
        /***********************************************************************************
        *** FUNCTION StringProcessing()                                                  ***
        ************************************************************************************
        *** DESCRIPTION : This is the constructor. It runs when a new inst. is created.  ***
        *** INPUT ARGS : N/A                                                             ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        StringProcessing();

        /***********************************************************************************
        *** FUNCTION StringProcessing(const StringProcessing&)                           ***
        ************************************************************************************
        *** DESCRIPTION : This is the copy constructor. It runs when a new instance is   ***
        ***               created with an Error instance as a paramater.                 ***
        *** INPUT ARGS : StringProcessing oldStringProcessing                            ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        StringProcessing(const StringProcessing&);

        /***********************************************************************************
        *** FUNCTION ~StringProcessing()                                                 ***
        ************************************************************************************
        *** DESCRIPTION : This is the destructor. It runs when a new inst. is destroyed. ***
        *** INPUT ARGS : N/A                                                             ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : N/A                                                                 ***
        ***********************************************************************************/
        ~StringProcessing();

        /***********************************************************************************
        *** FUNCTION string removeFrontWhitespace(string)                                ***
        ************************************************************************************
        *** DESCRIPTION : Erases all spaes, tabs, and endline characters from a string   ***
        ***               until somehing else is reached.                                ***
        *** INPUT ARGS : N/A                                                             ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : string line                                                    ***
        *** RETURN : string p[rocessed]String                                            ***
        ***********************************************************************************/
        static string removeFrontWhitespace(string);

        /***********************************************************************************
        *** FUNCTION void getNextTextBlock(string&, char, bool, bool)                    ***
        ************************************************************************************
        *** DESCRIPTION : From workLine, returns the next block of text and erases it    ***
        ***               if requested.                                                  ***
        *** INPUT ARGS : bool erase, incCommonDoubles; char endChar                      ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : string workLine                                                ***
        *** RETURN : string output                                                       ***
        ***********************************************************************************/
        static string getNextTextBlock(string&, char = ' ', bool = false, bool = false);

        /***********************************************************************************
        *** FUNCTION string trimEndChars(string)                                         ***
        ************************************************************************************
        *** DESCRIPTION : returns string w/o end/newline characters at its end.          ***
        *** INPUT ARGS : string line                                                     ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : string output                                                       ***
        ***********************************************************************************/
        static string trimEndChars(string);

        /***********************************************************************************
        *** FUNCTION string adjustCase(string, bool)                                     ***
        ************************************************************************************
        *** DESCRIPTION : Returns an ajusted case version of the passed string.          ***
        *** INPUT ARGS : string line, bool uppercase                                     ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : string output                                                       ***
        ***********************************************************************************/
        static string adjustCase(string, bool);

        /***********************************************************************************
        *** FUNCTION string filterString(string, bool, bool, bool)                       ***
        ************************************************************************************
        *** DESCRIPTION : Returns a filtered string from alpha, digit, and/or sp. char.  ***
        *** INPUT ARGS : string line; bool alpha, num, spchar                            ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : string output                                                       ***
        ***********************************************************************************/
        static string filterString(string, bool = false, bool = false, bool = false);

        /***********************************************************************************
        *** FUNCTION int countChars(string)                                              ***
        ************************************************************************************
        *** DESCRIPTION : This funciton returns the number of a certian char in a string ***
        *** INPUT ARGS : sting inLine, char interest                                     ***
        *** OUTPUT ARGS : N/A                                                            ***
        *** IN/OUT ARGS : N/A                                                            ***
        *** RETURN : int count                                                           ***
        ***********************************************************************************/
        static int countChars(string, char);
};