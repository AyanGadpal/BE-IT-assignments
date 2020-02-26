//===============================================================================================
// Name        : LEX
// Author      : Ayan Gadpal 33308
// Version     : 1.0
// Copyright   : GNU Public License
// Modified    : 26 Feb 2020
// Total Time  : 2 Hours
// Description : 1st Pass of 2 Pass Assembler
// Status      : 22% Done
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
class Table
{
private:
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
class Lexical
{
private:

public:
    int category(char S)
    {
        // NUMERIC TYPE
        if(S >= 48 && S<=57)
            return 1;

        // Name 
        else if((S>=65 && S<=90)||(S>=97 && S<=122))
            return 0;
     

        return -1;
    }

    void Analyze(const char *inputFilename)
    {
        ifstream in;
        Table LitralTable,IdentiferTable;
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
                if(C == 1)
                {
                    cout<<endl<<chstr[i]<<" "<<"NUMBER";
                    char inputBuffer[MAX];
                    int j=0;
                    for(j=0;j<MAX && category(chstr[i])== 1;j++,i++)
                    {
                        inputBuffer[j] = chstr[i];
                    }
                    inputBuffer[j]='\0';
                    LitralTable.add(inputBuffer);
                }
                else if(C == 0)
                {
                    cout<<endl<<chstr[i]<<" "<<"CHAR";
                    char inputBuffer[MAX];
                    int j;
                    for(j=0;j<MAX && isalnum(chstr[i]);j++,i++)
                    {
                        inputBuffer[j] = chstr[i];
                    }
                    inputBuffer[j]='\0';
                    IdentiferTable.add(inputBuffer);
                }
                else
                {
                    cout<<endl<<chstr[i]<<" "<<"SYMBOL";
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
