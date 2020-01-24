//=================================================================================
// Name        : 3 SL-V Assembler's 2 Pass Output
// Author      : Ayan Gadpal 33308
// Version     : 2.0
// Copyright   : GNU Public License
// Date        : 17 Jan 2020
// Description : 2 Pass Assembler
// Status      : 10% Done 
// NOTE - YOU WILL NEED INTERMIDATECODE,SYMBOLTABLE AND LITRAL TABLE FILE 
	     /*              \	 ----   /	
		              \	 |00|  /
		               \ ---- /
		     		-_||_-
		     		  ||	WHEN A CODER GET'S REALLYYYYYYYYY BOREDDDD !!!!
		     		  ||
		     		  ||
		     		 /  \
		     		/    \
		               /      \
		     	       L       L
		  */	
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


class litralTable
{
private:

  struct Row row[20];
  int top;
public:

  litralTable()
  {
	top = 0;
  }
   
  void readFromFile()
  {
		ifstream in;
		in.open("LitralTable.txt");
		string str; 
        int index = 0;
        // Process line by line input
        while (getline(in, str))
        {
        	 // Covert string into char[]
            int n = str.length();
            char chstr[n + 1];
           
            strcpy(chstr, str.c_str());

            // Splite Word by space
            char *token = strtok(chstr, " "); // Index
            
            token = strtok(NULL, " "); // Symbol
           
            row[index].symbol = token;
             	
            token = strtok(NULL, " "); // Address   
             
            row[index].value = atoi(token); 
            index++; 
            top = index;
        }
        
        in.close();
	}
	void display()
	{
		cout<<"\nLitral TABLE \n";
		for(int i =0;i<top;i++)
			cout<<i<<" "<<row[i].symbol<<" "<<row[i].value;
	}

};
// Keep track of Symbols
class symbolTable
{

private:
   struct Row row[20];
   int top; 
   
public:

	symbolTable()
	{
		top = 0;
	}
	
	
	void readFromFile()
	{
		ifstream in;
		in.open("SymbolTable.txt");
		string str; 
        int index = 0;
        // Process line by line input
        while (getline(in, str))
        {
        	 // Covert string into char[]
            int n = str.length();
            char chstr[n + 1];
           
            strcpy(chstr, str.c_str());

            // Splite Word by space
            char *token = strtok(chstr, " "); // Index
            
            token = strtok(NULL, " "); // Symbol
           
            row[index].symbol = token;
             	
            token = strtok(NULL, " "); // Address   
             
            row[index].value = atoi(token); 
            index++; 
            top = index;
        }
        
        in.close();
	}
	void display()
	{
		cout<<"\nSYMBOL TABLE \n";
		for(int i =0;i<top;i++)
			cout<<i<<" "<<row[i].symbol<<" "<<row[i].value<<endl;
	}

};

struct MachineRow
{
	int Address;
	int opcode;
	int reg;
	int memAddress;
	MachineRow()
	{
		Address = opcode = reg = memAddress = 0;
	}
};
class MachineCode
{
private:
	symbolTable ST;
	litralTable LT;
	struct MachineRow Row[20];
	int len;
public:
	MachineCode()
	{
		LT.readFromFile();
		ST.readFromFile();
		len = 0;
	}
	
	// Create Translation Method Here
	void translate()
	{
		ifstream in; // Input file
        ofstream out; // Output file
	
        // Open the file
        in.open("IntermidiateCode.txt");

        // Open the Destination file
        out.open("MachineCode.txt");

        string str; 
        
        while (getline(in, str))
        {
           // Covert string into char[]
           int n = str.length();
           char chstr[n + 1];
           strcpy(chstr, str.c_str());

           // Splite Word by space
           char *token = strtok(chstr, " ");
           out << LC << " ";
           while (token != NULL)
           {                
              token = strtok(NULL, " ");
              // SUBSTRING NIKAL 1 - 2 AND COMPAIR MAAR WITH AD AND IS AND DS 
              
           }
        }
        
		
	}
};


int main()
{
	MachineCode M;
	M.translate();
	return 0;
}

