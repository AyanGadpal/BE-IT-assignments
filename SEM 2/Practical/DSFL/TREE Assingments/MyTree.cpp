#include <iostream>
#include "PriorityQ.h"
#include "PriorityQ.cpp"

using namespace std ; 

class Node
{
    public:
        int data;
        Node *left,*right;
    Node()
    {
        data = 0;
        left = right = NULL;

    }
    Node(int data)
    {
        this->data = data;   
    }
    friend ostream & operator << (ostream &out, const Node &c); 
};

ostream & operator << (ostream &out, const Node &c) 
{ 
    out << c.data; 
    return out; 
} 
void line()
{
    cout<<"\n======================================\n";
}
class Tree 
{
    Node *root;
    int h;

    public:

    PriorityQ<Node*> Q;

    Tree()
    {
        root = NULL;
    }

    //Main create which will create tree using recursion
    Node* create(Node *temp)
    {
   
        char ch;
        Node *n;
        n = new Node();
        cout<<"\nEnter - for Null\n+for Data for";
        cin>>ch;
        switch(ch)
        {
            case '+':
                    //Take Input
                    cout<<"\nEnter the Data";
                    cin>>n->data;
                break;
            case '-':
                    // Return NULL as the parent child is NULL
                    return NULL;
                break;
        }
        
        //First take the Left Childs Recurively
        line();
       
        cout<<"\nEnter Left Child for "<<n->data;
        n->left=create(n);

        //Then Right Child
         line();
        
        cout<<"\nEnter Right Child for "<<n->data;
        n->right=create(n);

        //Return the new node, the subtree below it is automatically attached
        return n;

    }

    // Overloaded create for Ease of Use
    void create()
    {
        //for next node
        Node *n = new Node();
        
        display();

        root = create(n);

        cout<<"\nTree Created Successfully!";
    }

    // Return true is tree is Empty
    bool isEmpty()
    {
        //Only if root is pointing to NULL ,the tree will be empty
        if(root == NULL)
            return true;
        else
            return false;
    }
    
    //Returns the Height : Overloaded for Ease of Use
    int height()
    {
        int hi;
        hi = height(root);
        return hi;

    }

    int height(Node *temp)
    {
        int hl,hr;
        if(temp==NULL)
		    return 0;
        else
        {
            hl = 1 + height(temp->left);
            hr = 1 + height(temp->right);
        }
        if(hl>hr)
            return hl;
        else
		    return hr;
    }
    
    void display(Node *temp)
    {
       

        if(temp == NULL)
        {
            return;
        }
        if(temp->right == NULL)
        {
            Q.enqueue(temp,0);
        }
        else
        {
            display(temp->right);
            Q.enqueue(temp,0);
           
        }

        display(temp->left);
        
        
    }
    void display()
    {
      int h= height(root);
   
      int th,tabs;
      Node *t = new Node();
      display(root);
      cout<<"\n\t\tTREE\n\n";
      while(!Q.isEmpty())
      {
          t = Q.dequeue();
          th = height(t);
          tabs = h - th;
          while(tabs != 0)
          {
              cout<<"\t";
              tabs--;
          }
          cout<<t->data;
          cout<<"\n";
      }
    }


//WORKING HERE
    void levelorder()
    {
        PriorityQ<Node *> Q;
        Node *temp = root;
        
        while(temp!=NULL)
        {
            cout<<" "<<temp->data<<" ";
            Q.enqueue(temp->left,0);
            Q.enqueue(temp->right,0);

            if(!Q.isEmpty())
            {
                temp = Q.dequeue();
            }
            else
                temp = NULL;		
        }
    }

    


};



int main()
{
    Tree T;
    T.create();
    T.display();
    T.levelorder();


    
    return 0;
}
