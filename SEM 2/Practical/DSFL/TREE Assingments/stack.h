#include<iostream>

using namespace std;

template <typename T>
class stack
{
    T Data;
    stack *next;

    public:
    
    stack()
    {
      next = NULL;  
    }
    
    void push(T eData)
    {
        stack *node;
        node = new stack();
        node->Data = eData;
        node->next = next;
        next = node;
    }

    void display()
    {
        stack p;
        p.next=next;
        while(!p.isEmpty())
        {   
           cout<<p.pop()<<endl;
           cout<<"-----\n";
        }       
    }

    T pop()
    {
            T e ;
            if(isEmpty())
            {
            	cout<<"\nSTACK ERROR : UNDERFLOW \n";
            	return e;
            }
            e = next->Data;
            next = next->next;
         return e;

    }

    T Top()
    {	
        return next->Data;
    }
     void reverse()
     {
               stack *p,*c,*n;
               p = NULL;
               c = NULL;
               n = next;

               while(n != NULL)
               {
                      c = n;
                      n = n->next;
                      c->next = p;
                      p = c;
               }
               next = p;
               display();
      }

    bool isEmpty()
    {
        if(next == NULL)
            return true;
        else
            return false;
    }
};