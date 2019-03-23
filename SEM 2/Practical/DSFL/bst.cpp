
//Name         : BST.cpp
// Author      : Ayan Gadpal
// Description : Perform following operations using Binary Search Tree
// 				 1. Insert 1
//				 2. Delete
//				 3. Search
//				 4. Mirror Image
//				 6. Display 1
//				 7. Display level wise 1
//				 8. Height of the tree 1


#include<iostream>
#include "PriorityQ.h"
#include "PriorityQ.cpp"

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

class BST
{
    Node *root;

    public:
        PriorityQ<Node*> Q;
        BST()
        {
            root = NULL;
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
            cout<<"\n~~~~~~~~~~~~ BST ~~~~~~~~~~~\n\n";
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

        void insert(int d)
        {
            Node *temp = root;
            if(isEmpty())
            {
                    temp = new Node;
                    temp->left = NULL;
                    temp->right = NULL;
                    temp->data = d;
                    root=temp;
                    cout<<"\n Data was inserted in the tree successfully !";
                    return;
            }
           root = insert(d,temp);

        }

        

        Node *insert(int data,Node *root)
        {

            if(root == NULL)
            {
                Node *temp = new Node;
                temp->data = data;
                temp->left = NULL;
                temp->right = NULL;

                root = temp;
                return root;
            }
            else
            {
                if(data < root->data)
                {
                    root->left = insert(data,root->left);

                }
                else if(data > root->data)
                {
                    root->right = insert(data,root->right);
                }
                else
                {
                    cout<<"\n\nDuplication Is Not Allowed";
                }
                return root;
            }

            return root;
        }

        Node* mirrorImage()
        {
            return mirrorImage(root);
        }
        
        Node* mirrorImage(Node *root)
        {
            Node *temp;
                if(root != NULL)
                {
                    temp = root->left;
                    root->left = root->right;
                    root->right = temp;
                    mirrorImage(root->left);
                    mirrorImage(root->right);
                }
		    return root;
	    }

        void deleteNode(int key)
        {
            if(isEmpty())
            {
                cout<<"\nERROR : EMPTY TREE !";
                return;
            }
            
            root = deleteNode(root,key);
        }

        Node* deleteNode(Node* root, int key)
        {
            if (root == NULL) return root;
            if (key < root->data)
                root->left = deleteNode(root->left, key);
            else if (key > root->data)
                root->right = deleteNode(root->right, key);
            else
            {
                if (root->left == NULL)
                {
                    Node *temp = root->right;
                    delete root;
                    return temp;
                }
                else if (root->right == NULL)
                {
                    Node *temp = root->left;
                    delete root;
                    return temp;
                }

                Node* temp = minNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);

            }
            return root;
        }

        Node * minNode(Node* node)
        {
            Node* current = node;

            while (current->left != NULL)
                current = current->left;

            return current;
        }

        void search(int data)
        {
            Node *temp = root;

            while(temp != NULL){
                if(data < temp->data && temp->left != NULL){
                    temp = temp->left;
                }else if(data > temp->data && temp->right != NULL){
                    temp = temp->right;
                }else if(temp->data == data){
                    cout<<"\nData Found !!";
                    return;
                }
                else
                {
                        cout<<"\nERROR : Data Not Found";
                        return;
                }
            }
        }

        void inOrder(Node *root)
        {
            if(isEmpty())
            {

                cout<<"EMTYY";

            }            
            else if(root != NULL)
            {
                inOrder(root->left);
                cout<<" "<<root->data;
                inOrder(root->right);
            }
        }

        void levelOrder()
        {
            PriorityQ<Node*> QU;
            Node *temp ;
            temp = root;

            display();
            cout<<"Level Order : ";

            while(temp!=NULL)
            {

                int d = temp->data;
                cout<<" "<<d<<" ";

                if(temp->left!=NULL)
                    QU.enqueue(temp->left,0);

                if(temp->right!=NULL)
                    QU.enqueue(temp->right,0);

                if(!QU.isEmpty())
                {
                    temp = QU.dequeue();
                }
                else
                    temp = NULL;
            }
        }
};

int main()
{
    BST T;
    Node *temp;
     int d;
    char choice;

    while ( choice != '7' )
    {
        line();
        cout<<
            "\n~~~~~~~~~~~~~~ MAIN MENU ~~~~~~~~~~~~~~\n"
            "\nPlease Select An Option\n"
            "1) Insert \n"
            "2) Delete\n"
            "3) Search\n"
            "4) Display\n"
            "5) Display Level\n"
            "6) Height\n"
            "7) Exit\n"
            "YOUR CHOICE : "
            ;
            cin>>choice;

            switch(choice)
            {
                case '1':
                sLine();
                    do
                    {
                       
                        cout<<"\nEnter the Value";
                        cin>>d;
                        T.insert(d);
                        cout<<"\nDo you want to Enter More? (y/n) \n CHOICE : ";
                        cin>>choice;
                    } while( choice != 'n');
                
                break;

                case '2':
                sLine();
                    cout<<"\nEnter the Value";
                    cin>>d;
                    T.deleteNode(d);
                break;

                case '3':
                sLine();
                  cout<<"\nEnter the Value";
                  cin>>d;
                  T.search(d);
                
                break;

                case '4':
                sLine();
                    T.display();
                break;


                case '5':
                sLine();
                    T.levelOrder();
                break;

                case '6':
                sLine();
                    cout<<"HEIGHT : "<<T.height();
                break;

                case '7':
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
