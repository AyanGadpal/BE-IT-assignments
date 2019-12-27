//=================================================================================
// Name        : 2 SL-V Assembler
// Author      : Ayan Gadpal 33308
// Version     : 1.0
// Copyright   : GNU Public License
// Date 	   : 20 Dec 2019
// Description : Assembler
// Note you will input.txt and MachineCode.txt
//=================================================================================

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

// Each Row contain one entry for Translation Table
struct Row
{
    int opcode; // Opcode to be Translate into
    string symbol; // Symbol to Translate
    
    // Intializing Opcode to zero
    Row()
    {
        opcode = 0;
    }
};

// Our Translation Table to which handle the contain symbol -> opcode table and perform translation
class TranslationTable
{
private:
    struct Row row[20]; // Table of 20 Row(symbol,opcode)
    int len; // length of element present

public:
    // Initialize the Table
    TranslationTable()
    {
        row[0].symbol = "START";
        row[0].opcode = 1;

        row[1].symbol = "END";
        row[1].opcode = 2;

        row[2].symbol = "MOVER";
        row[2].opcode = 3;

        row[3].symbol = "AREG";
        row[3].opcode = 4;

        row[4].symbol = "BREG";
        row[4].opcode = 5;

        len = 5;
    }

    // Match the symbols to the opcode
    int match(const char *symbol)
    {
        // iterator
        int i;

        // For each entry in table // Consider using hash table for such case to speed up
        for (i = 0; i < len; i++)
            if (strcmp(symbol, row[i].symbol.c_str()) == 0) // Compare with Each symbol
                return row[i].opcode; // Return opcode if found

        return -1; // Not Found
    }

    // Translate the ASM ( taken "txt" for simplicity ) file into Machine Code
    void Translate(const char *inputFilename)
    {
        ifstream in; // Input file
        ofstream out; // Output file

        // Open the file
        in.open(inputFilename);

        // Open the Destination file
        out.open("MachineCode.txt");

        string str; 
        
        // Process line by line input
        while (getline(in, str))
        {
            // Covert string into char[]
            int n = str.length();
            char chstr[n + 1];
            strcpy(chstr, str.c_str());

            // divide by space
            char *token = strtok(chstr, " ");

            // Check whether label
            if (match(token) != -1)
                out << "_";

            // For each word in the sentence
            while (token != NULL)
            {
                // Find Opcode
                int id = match(token);

                // Got Opcode
                if (id != -1)
                    out << " " << id;
                // No Opcode, i.e unidentified symbol or label
                else
                    out << " " << token;
                
                // Go to next word
                token = strtok(NULL, " ");
            }
            out << endl;
        }

        // Close the Files
        in.close();
        out.close();
    }
};

// Driver Code
int main()
{
    // Create the table
    TranslationTable T;

    // Call the translator
    T.Translate("input.txt");

    return 0;
}

// End of code
