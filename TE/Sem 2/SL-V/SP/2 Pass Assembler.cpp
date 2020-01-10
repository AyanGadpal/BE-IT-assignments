//=================================================================================
// Name        : 3 SL-V Assembler's 2 Pass Output
// Author      : Ayan Gadpal 33308
// Version     : 1.0
// Copyright   : GNU Public License
// Date        : 10 Jan 2020
// Description : 2 Pass Assembler
// Status      : 0% Done 
//
// TODOs	
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

class pool
{
private:
   int row[20];
   int top; 
public:
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
		cout<<"SYMBOL TABLE \n";
		for(int i =0;i<top;i++)
			cout<<endl<<i<<" "<<row[i].symbol<<" "<<row[i].value;
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
		cout<<"SYMBOL TABLE \n";
		for(int i =0;i<top;i++)
			cout<<endl<<i<<" "<<row[i].symbol<<" "<<row[i].value;
	}

};

struct BinaryRow
{
	int Address;
	int opcode;
	int reg;
	int memAddress;
	BinaryRow()
	{
		Address = opcode = reg = memAddress = 0;
	}
};
class MachineCode
{
private:
	struct BinaryRow Row[20];
	int len;
public:
	MachineCode()
	{
		len = 0;
	}
	
	// Create Translation Method Here
}


int main()
{
	symbolTable ST;
	
    ST.readFromFile();
	ST.display();
	return 0;
}

