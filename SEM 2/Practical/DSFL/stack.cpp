#include<iostream>

using namespace std;

class stack
{
    public:

    int Data;
    stack *next;

    void push()
    {
        stack *node;
        node = new stack();
        cout<<"\nEnter The Data for the new Node : ";
        cin>>node->Data;
        node->next = next;
        next = node;
    }

    void display()
    {
        stack p;
        p.next=next;
        while(!p.underFlow())
        {   
           cout<<p.pop()<<endl;
           cout<<"-----\n";
        }       
    }

    int pop()
    {
            int e = next->Data;
            next = next->next;
         return e;

    }

    bool underFlow()
    {
        if(next == NULL)
            return true;
        else
            return false;
    }
};

void line()
{
    cout<<endl<<"=======================================\n";
}
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