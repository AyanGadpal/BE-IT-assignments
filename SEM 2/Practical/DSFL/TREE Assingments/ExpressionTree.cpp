/*
 *
 *	 Problem :-
 *	 Take a postfix expression and covert it into Expression Tree 
 *   with Recursive and Non-Recursive inorder, preorder and postorder
 *  
 *   Author: Ayan Gadpal H11 23370 SE11
 *
 */


#include <iostream>
#include "stack.h"
#include "PriorityQ.h"
#include "PriorityQ.cpp"
#include <string.h>

using namespace std;

//============ TO PROVIDE A LINE IN OUTPUT ============
inline void line() // INLINE FOR BETTER PERFORMANCE
{
    cout<<"\n=======================================\n";
}
inline void sLine() // INLINE FOR BETTER PERFORMANCE
{
    cout<<"\n_______________________________________\n";
}

class Node
{
    public:
        char data;
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

//'<<' operator overloaded for ease of use with 'cout'
ostream & operator << (ostream &out, const Node &c) 
{ 
    out << c.data; 
    return out; 
} 

//=========== TO IDENTIFY THE LITERALS AND OPERATORS ================
int determine(char ch)
{
    if((ch >= 65 && ch <= 91) || (ch >= 97 && ch <= 123) || (ch >= 48 && ch <= 57))
		return 1;
    else
        return 0;
}




class Tree
{
    //-------TO STORE THE ROOT OF TREE--------
    Node *root;
    int h; // HEIGHT

    public:

    PriorityQ<Node*> Q,Q2; // FOR RECURSION
    stack<Node*> Stack; // FOR RECURSION

    
    //========= CONSTRUCTORS ===========
    Tree()
    {
    	//Initializing Tree
    	h = 0;
    	root = NULL; // EMPTY TREE
    }

    Tree(Node* n)
    {
    	//Initializing Tree with some other tree root
        root = n; 
        h = height();
    }

    //=========== FUNCTIONS DEFINATIONS =============
    void create(char exp[])
    {
        for(int i=0;exp[i];i++)
        {
            Node *newNode = new Node; // Create new node 

            if(determine(exp[i]) == 1) // If Alphabet or Number
            {
                              
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->data = exp[i];
           
            }
            if(determine(exp[i]) == 0) // If Operator
            {
               
                newNode->data = exp[i];
                newNode->right = Stack.pop();
                newNode->left = Stack.pop();
               
            }
            
            Stack.push(newNode);
        }

     //Finally, The Only Remaining Element in Stack is Pointed by Root
	 root = Stack.pop();

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



    //Finding height using Recursion
    int height(Node *temp)
    {
        int hl,hr;
        if(temp==NULL)
      	    return 0;
        else
        {
            //left height
           	hl = 1 + height(temp->left);
            //Right subtree height
           	hr = 1 + height(temp->right);
        }
           //taking max from both sides
        if(hl>hr)
            return hl;
        else
      		return hr;
    }

    void display(Node *temp)
    {
        if(temp == NULL)
            return;
        if(temp->right == NULL)
            Q.enqueue(temp,0);
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
      cout<<"\n~~~~~~~~~~~~ Expression TREE ~~~~~~~~~~~\n\n";
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

    //GETTERS AND SETTERS FOR ROOT
    void setRoot(Node* root)
    {
    	this -> root = root;
    }
    Node* getRoot()
    {
        return this->root;
    }


    //---------NON RECURSIVE ALGO---------
    void inorder()
    {
        Node * temp = root;
        while(1)
        {
            while(temp != NULL)
            {
                Stack.push(temp);
                temp = temp->left;
            }
            if(Stack.isEmpty())
                return;

            temp = Stack.pop();
            cout<<" "<<temp->data;
            temp = temp->right;
        }
    }
    void preorder()
    {
        Node * temp = root;
        while(1)
        {
            while(temp != NULL)
            {
                cout<<" "<<temp->data;
                Stack.push(temp);
                temp = temp->left;
            }
            if(Stack.isEmpty())
                return;

            temp = Stack.pop();
            temp = temp->right;
        }
    }
    void postorder()
    {
        stack<Node *>Stack2;
        Node * temp = root;
        Node * temp1;

        Stack.push(temp);

        while(!Stack.isEmpty())
        {
            temp1 = Stack.pop();
            Stack2.push(temp1);

            if(temp1->left != NULL)
                Stack.push(temp1->left);
            if(temp1->right != NULL)
                Stack.push(temp1->right);
        }

        while(!Stack2.isEmpty())
        {
            cout<<" "<<Stack2.pop()->data;
        }
    }
    

    //---------RECURSIVE ALGO---------
    void inorder(Node *temp)
    {
        if(temp!=NULL)
        {
                inorder(temp->left);
                cout<<" "<<temp->data<<" ";
                inorder(temp->right);
        }
    }

    void preorder(Node *temp)
    {
        if(temp!=NULL)
        {
            cout<<" "<<temp->data<<" ";
            preorder(temp->left);
            preorder(temp->right);
        }
    }

    void postorder(Node *temp)
    {
        if(temp!=NULL)
        {
            postorder(temp->left);
            postorder(temp->right);
            cout<<" "<<temp->data<<" ";
        }
    }

};

//-------- DISPLAY NON RECURSIVE ALGO MENU ------------

void displayNR(Tree ET)
{
    char ch;
    
    while(1)
    {  
        cout<<
                "\n\n~~~~~~~~~ NON RECURSIVE ALGO ~~~~~~~~~\n"
                "\nPlease Select An Option\n"
                "1) Inorder\n"
                "2) Preorder\n"
                "3) Postoder\n"
                "4) Back to Main Menu\n"
                "YOUR CHOICE : ";
        cin>>ch;

        ET.display();
        switch(ch)
        {
            case '1':
                sLine();
                cout<<"\nInoder : ";
                ET.inorder();

        break;
            case '2':
                sLine();
                cout<<"\nPreorder : ";
                ET.preorder();

                
        break;
            case '3':
                sLine();
                cout<<"\nPostorder : ";
                ET.postorder();

                
        break;
            case '4':
                return;

                
        break;
        default: 
            cout<<"ERROR : Please Select Options from 1 to 4 ONLY";
        }
    }

}

//--------DISPLAY RECURSIVE ALGO MENU------------

void displayR(Tree ET)
{
    char ch;
    
    while(1)
    {  
        cout<<
                "\n\n~~~~~~~~~~ RECURSIVE ALGO ~~~~~~~~~~\n"
                "\nPlease Select An Option\n"
                "1) Inorder\n"
                "2) Preorder\n"
                "3) Postoder\n"
                "4) Back to Main Menu\n"
                "YOUR CHOICE : ";
        cin>>ch;
        
        switch(ch)
        {
            case '1':
                sLine();
                cout<<"\nInoder : ";
                ET.inorder(ET.getRoot());

            break;
            case '2':
                sLine();
                cout<<"\nPreorder : ";
                ET.preorder(ET.getRoot());

                
            break;
            case '3':
                sLine();
                cout<<"\nPostorder : ";
                ET.postorder(ET.getRoot());

                
            break;
            case '4':
                return;

            default: 
                cout<<"ERROR : Please Select Options from 1 to 4 ONLY";
        }
    }

}

int main()
{
   Tree ET;
   char postfix[20];
   postfix[0]='\0';
   
   
   char choice;
   
   while ( choice != '6' )
        {
            line();
            cout<<
            "\n~~~~~~~~~~~~~~ MAIN MENU ~~~~~~~~~~~~~~\n"
            "\nPlease Select An Option\n"
            "1) Enter Postfix Expression \n"
            "2) Display Postfix Expression\n"
            "3) Display Tree\n"
            "4) Display Non Recursive\n"
            "5) Display Recursive\n"
            "6) EXIT\n"
            "YOUR CHOICE : "
            ;
                    cin>>choice;

                    switch(choice)
                    {
                        case '1':
                                sLine();
                                    cout<<"\nEnter The Postfix Expression : ";
                                    cin>>postfix;
                                    ET.create(postfix);
                                break;
                        case '2':
                                sLine();
                                    if(postfix[0]!='\0')
                                    {
                                        cout<<"\nPostfix Expression is : "<<postfix;
                                    }
                                    else
                                    {
                                        cout<<"\nNo Expression Found !";
                                    }
                             
                                break;
                        case '3':
                                sLine();
                                if(!ET.isEmpty())
                                    ET.display();
                                else
                                    cout<<"ERROR : Enter The Expression First !";
                                break;
                        case '4':
                                sLine();
                                displayNR(ET);

                                break;
                        case '5':
                                sLine();
                                displayR(ET);

                                break;

                        case '6':
                                line();
                                cout<<"\n\t\tGOOD BYE\n";
                                line();
                                break;
                        default:
                                sLine();
                                cout<<"ERROR : Wrong Option Selected !!";

                    }
        }
	return 0;
}

