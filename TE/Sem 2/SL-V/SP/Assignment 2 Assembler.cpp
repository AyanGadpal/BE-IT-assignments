//=================================================================================
// Name        : 3 SL-V Assembler's 1 Pass Output
// Author      : Ayan Gadpal 33308
// Version     : 3.0
// Copyright   : GNU Public License
// Date        : 3 Jan 2020
// Description : 2 Pass Assembler
// Status      : 50% Done 
//
// Note you will need tu put your code in input.txt and check output in MachineCode.txt
// 
// TODOs
// 1) Handle Label and Symbol Decalretion
// 2) Complete Other half of symbol table
// 3) Literal and pool table
// 4) Make LC more Accurate, now its simply += 1
// 5) Error Reporting
//=================================================================================
#include <bits/stdc++.h>

using namespace std;

// Basic Row used by Various Classes 
struct Row
{
    string symbol;
    string type;
    int value;
};

// Keep track of Symbols
class symbolTable
{

private:
   struct Row row[20];
   int len; 

public:

	symbolTable()
	{
		len = 0;
	}

	int	add(char *symbol)
	{
		row[len].symbol = symbol;
		row[len].value = -1;
		return len++;
	}

	void display()
	{
		cout<<"SYMBOL TABLE \n";
		for(int i =0;i<len;i++)
			cout<<endl<<i<<" "<<row[i].symbol;
	}

};

class TranslationTable
{

private:
    struct Row row[22]; 
    int len; // length of element present
    int LC;
    bool START;
    symbolTable ST;

public:

    // Initialize the Table
    TranslationTable()
    {
        LC = -1;

        START = false;

        row[0].symbol = "STOP";
        row[0].type = "IS";
        row[0].value = 0;

        row[1].symbol = "ADD";
        row[1].type = "IS";
        row[1].value = 01;

        row[2].symbol = "SUB";
        row[2].type = "IS";
        row[2].value = 02;
        
        row[3].symbol = "MULT";
        row[3].type = "IS";
        row[3].value = 03;

        row[4].symbol = "MOVER";
        row[4].type = "IS";
        row[4].value = 04;

        row[5].symbol = "MOVEM";
        row[5].type = "IS";
        row[5].value = 05;

  		row[6].symbol = "COMP";
        row[6].type = "IS";
        row[6].value = 6;

        row[7].symbol = "BC";
        row[7].type = "IS";
        row[7].value = 7;

 		row[8].symbol = "DIV";
        row[8].type = "IS";
        row[8].value = 8;

        row[9].symbol = "READ";
        row[9].type = "IS";
        row[9].value = 9;

		row[10].symbol = "PRINT";
        row[10].type = "IS";
        row[10].value = 10;

		// R
	
		row[11].symbol = "AREG";
        row[11].type = "R";
        row[11].value = 1;

		row[12].symbol = "BREG";
        row[12].type = "R";
        row[12].value = 2;
	
		row[13].symbol = "CREG";
        row[13].type = "R";
        row[13].value = 3;

		// AD

		row[14].symbol = "START";
        row[14].type = "AD";
        row[14].value = 0;

		row[15].symbol = "END";
        row[15].type = "AD";
        row[15].value = 1;

		row[16].symbol = "ORIGIN";
        row[16].type = "AD";
        row[16].value = 2;

		row[17].symbol = "EQU";
        row[17].type = "AD";
        row[17].value = 3;

		row[18].symbol = "LTORG";
        row[18].type = "AD";
        row[18].value = 4;

        // DS DC
        row[19].symbol = "DS";
        row[19].type = "DL";
        row[19].value = 2;

        row[20].symbol = "DC";
        row[20].type = "DL";
        row[20].value = 1;

        len = 21;
    }

    // Match the symbols to the opcode
    int match(const char *symbol)
    {
        // iterator
        int i;

        // For each entry in table // Consider using hash table for such case to speed up
        for (i = 0; i < len; i++)
            if (strcmp(symbol, row[i].symbol.c_str()) == 0) // Compare with Each symbol
                return i;

        return -1; // Not Found
    }

    char operand(const char *s)
    {
    	char* p;
		long converted = strtol(s, &p, 10);
		
		if (*p) {
		    // conversion failed because the input wasn't a number
		    if(s[0] == 61)
		    	return 'L';
		    else
		    	return 'S';
		}
		
		return 'C';
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
            int label = match(token);

            if(label == -1)
            {

            }

            // if (LC != -1)
            // 	out<<LC++<<" ";

            // For each word in the sentence
            while (token != NULL)
            {
                // Find Opcode
                int id = match(token);

                if(START)
                {
                	stringstream covertor(token); 
                	covertor >> LC;
                	START = false;
                }

                if (id == 14)
					START = true;


                // Opcode
                if (id != -1)
                {
                    if( LC==-1 || strcmp("AD", row[id].type.c_str()) == 0)
                    	out <<"     (" << row[id].type << ","<<row[id].value<<")";

                    else if(LC != -1 && (strcmp("IS", row[id].type.c_str()) == 0 || strcmp("DL", row[id].type.c_str()) == 0)) 
                    	out <<LC++<<" "<<"(" << row[id].type << ","<<row[id].value<<")";

                }
                
                // No Opcode, i.e unidentified symbol or label or Operand
                else
                {
                	char s = operand(token);
                	if(s == 83)
                	{
                		 out<<" ("<<s<<","<<ST.add(token)<<")";
                	}
                	else
                		out<<" ("<<s<<","<<token<<")";

                }
                
                // Go to next word
                token = strtok(NULL, " ");
            }
            out << endl;
        }
        ST.display();
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
