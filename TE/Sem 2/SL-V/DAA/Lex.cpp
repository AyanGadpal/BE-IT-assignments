//===============================================================================================
// Name        : LEX
// Author      : Ayan Gadpal 33308
// Version     : 1.0
// Copyright   : GNU Public License
// Modified    : 26 Feb 2020
// Total Time  : 2 Hours
// Description : 1st Pass of 2 Pass Assembler
// Status      : 92% Done
//
// Note you will need tu put your code in "program.c"
//
// TODOs
//  1) Make The Identifier Perfect
//  2) Create the Terminal Table by inheritance with Table
//  3) Check for Pattern Error ( invalid name vagera )
//===============================================================================================

#include <bits/stdc++.h>
#define MAX 20
using namespace std;

struct Row
{
    string name;
};

class Table
{
protected:
    string row[20];
    int Top;
public:
    Table()
    {
        Top=0;
    }
    void add(const char *row)
    {
        this->row[Top] = row;
        Top++;
    }
    void display()
    {
        for(int i=0;i<Top;i++)
            cout<<"\n"<<row[i];
    }
};

class UniformSymbolTable : public Table
{
    protected:
        char class[4];
    public:

    void add(const char *row)
    {
        this->row[Top] = row;
        Top++;
    }
    // CONDING HERE <-----------------------------------
}

class Lexical
{
private:
    int size;
    Row TerminalTAB[28];

public:
    Lexical()
    {
        size=28;
        ifstream in;
        in.open("TerminalTable");
        string str;
        int i=0;
        while (getline(in, str))
        {
           TerminalTAB[i].name = str;
           i++;
        }
    }
    int category(char S)
    {
        // NUMERIC TYPE
        if(S >= 48 && S<=57)
            return 1;
        if(S == 34)//"
            return 2;
        // Name 
        else if((S>=65 && S<=90)||(S>=97 && S<=122))
            return 0;
     

        return -1;
    }

    int checkTerminal(const char* symbol)
    {
        for(int i=0;i<size;i++)
        {
            if(strcmp(symbol,TerminalTAB[i].name.c_str())==0)
            return i;
        }
        return -1;

    }

    void Analyze(const char *inputFilename)
    {
        ifstream in;
        Table LitralTable,IdentiferTable,;
        in.open(inputFilename);
        string str;
        while (getline(in, str))
        {
            // Covert string into char[]
            int n = str.length();
            char chstr[n + 1];
            int opcodeSize = 1;
            strcpy(chstr, str.c_str());

            int len = str.length();
            int first = 0;

            for(int i=0;i<len && i<MAX;i++)
            {
                int C = category(chstr[i]);
                // Litral By Opening double inverted comma
                if(C == 2)
                {
                    char inputBuffer[MAX];

                    i++;

                    for(int j=0;j<MAX && category(chstr[i])!= 2;j++,i++)
                        inputBuffer[j] = chstr[i];
                    inputBuffer[j]='\0';

                    LitralTable.add(inputBuffer);
                
                }
                // Litral By 1st char is a number
                else if(C == 1)
                {
                    
                    char inputBuffer[MAX];
                    int j=0;
                    for(j=0;j<MAX && category(chstr[i])== 1;j++,i++)
                    {
                        inputBuffer[j] = chstr[i];
                    }
                    inputBuffer[j]='\0';
                    LitralTable.add(inputBuffer);
                }

                // Identifier or Terminal since it's a word
                else if(C == 0)
                {
                    char inputBuffer[MAX];

                    for(int j=0;j<MAX && isalnum(chstr[i]);j++,i++)
                        inputBuffer[j] = chstr[i];
                    inputBuffer[j]='\0';

                    // Check if the word is an terminal in Terminal table
                    int Tid = checkTerminal(inputBuffer);

                    if(Tid == -1)
                        IdentiferTable.add(inputBuffer);
                    else
                        cout<<endl<<inputBuffer<<" "<<"TERMINAL";
                }
              
                
            }
            
        }
        cout<<"\n\nLitral";
        LitralTable.display();
        cout<<"\n\nIdentifier";
        IdentiferTable.display();
    }
};

int main()
{
    Lexical processor;
    processor.Analyze("program.c");

    return 0;
}
