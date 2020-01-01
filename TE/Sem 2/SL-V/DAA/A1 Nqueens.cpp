//=================================================================================
// Name        : A1 SL-V DAA N-queens
// Author      : Ayan Gadpal 33308
// Version     : 1.0
// Copyright   : GNU Public License
// Date 	   : 27 Dec 2019
// Description : The N Queen is the problem of placing N chess queens on an N×N
//               chessboard so that no two queens attack each other
//=================================================================================

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

class ChessBoard
{
private:
    int *Board;
    int n;

public:
    int count,subCount;
    bool solved;
    // Set size of chessboard
    ChessBoard()
    {
        this->n = 4;
        this->Board = new int[n];
        count = 0;
        subCount = 0;
        solved = false;
    }
    ChessBoard(int size)
    {
        this->n = abs(size);
        this->Board = new int[n];
        count = 0;
        subCount = 0;
        solved = false;
    }

    // nqueens path
    bool nqueens()
    {
        cout << "Started Solution Finding\n";
        if(n<4)
        {
            cout<<"No Solution Available !";
            return false;
        }
        nqueenParser(0);
        if (!solved)
        {
        	cout<<"PASS END HERE \nNo More Solutions are Available";
        }
        else
        	cout<<"Solved";
        if(count == 0)
            cout<<"No Solution Available !";
        return true;
    }
    void nqueenParser(int row)
    {
        // cout<<"\n\n";
        //  cout<<"Q("<<row<<")\n";
        for (int i = 0; i < n; i++)
        {
            if (isSafe(row, i))
            {
                //cout<<"\nSafe col "<<i;
                passDisplay(row);
                Board[row] = i;
                if (row >= n - 1)
                    display();
                else
                    nqueenParser(row + 1);
            }
            //cout<<"\nFailed "<<row<<" "<<i;
            if (i == n - 1)
            {
                //cout<<"\nBACKTRACKING TO "<<row-1;
            }
        }
    }
    // isSafe
    bool isSafe(int row, int col)
    {
        for (int i = 0; i < row; i++)
        {
            if (Board[i] == col || (abs(Board[i] - col) == abs(i - row)))
                return false;
        }
        return true;
    }

     void passDisplay(int row)
    {
        solved = false;
        cout << "---------------"<<endl<<"Pass : "<<(++subCount)<<endl;
        for (int i = 0; i < n; i++)
        {
            for(int j=0;j<n;j++)
            {
                if(Board[i]!=j)
                    cout<<"_,";
                else
                	if(isSafe(i,j))
                		cout<<"Q,";
                	else
                		cout<<"_,";

                    
            }
            cout<<endl;
            // cout << Board[i] + 1;
        }
        cout << "\n";
    }
    // Need Modification
   

 	 void display()
    {
        cout << endl<<"Solution : "<<(++count)<<endl;
        for (int i = 0; i < n; i++)
        {
            for(int j=0;j<n;j++)
            {
                if(Board[i]!=j)
                    cout<<"_,";
                else
                    cout<<"Q,";
            }
            cout<<endl;
            // cout << Board[i] + 1;
        }
        solved = true;
        cout << "=================================="<<endl;
        subCount = 0;
        cout << "\n";
    }
};

int main()
{
    int n;
    cout<<"Enter Queens Number : ";
    cin>>n;
    ChessBoard nqueens(n);
    nqueens.nqueens();
    return 0;
}
