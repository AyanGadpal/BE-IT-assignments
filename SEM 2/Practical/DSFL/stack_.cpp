#include<iostream>
#include "stack.h"

using namespace std;


int main()
{
    stack top;
    int c;
    top.next = NULL;
    top.Data = -1;
    while(c!=4)
    {
        line();
        cout<<"Enter your Choice\n";
        cout<<"1) Push\n"
              "2) Pop\n"
              "3) Display Stack\n"
              "4) Display Stack\n"
                "Your Choice : ";
        cin>>c;
        line();
        switch(c)
        {
            case 1: top.push();
                    break;
        
            case 2: if(!top.underFlow())
                        cout<<top.pop();
                    else
                        cout<<"STACK UNDERFLOW";
                    break;
        
            case 3: if(!top.underFlow())
                    {
                        cout<<"TOP\n";
                        top.display();
                        cout<<"NULL\n";
                    }
                    else
                        cout<<"STACK UNDERFLOW";
                    break;
            case 4: 
                    break;                
                    
        }
        line();
    }
    return 0;
}