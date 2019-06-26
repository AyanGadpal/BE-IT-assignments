/*
 *
 *	 Problem :-
 *	 Binary Tree with operation such as create,
 *	 insert , display ,Height, display Leaves ect
 *
 *
 *	 Author: Ayan Gadpal H11 23370 SE11
 *
 */
#include <iostream>
#include "PriorityQ.h"
#include "PriorityQ.cpp"

using namespace std;

class Node
{
  public:
    int data;
    Node *left, *right;
    Node()
    {
        data = 0;
        left = right = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->left = this->right = NULL;
    }

    friend ostream &operator<<(ostream &out, const Node &c);
};

ostream &operator<<(ostream &out, const Node &c)
{
    out << c.data;
    return out;
}
void line()
{
    cout << "\n======================================\n";
}
class Tree
{
    Node *root;
    int h;

  public:
    PriorityQ<Node *> Q;

    Tree()
    {
        //Initializing Tree
        h = 0;
        root = NULL;
    }

    //Main create which will create tree using recursion
    Node *create(Node *temp)
    {

        char ch;
        Node *n;
        n = new Node();
        cout << "\nEnter - for Null\n+for Data for";
        cin >> ch;
        switch (ch)
        {
        case '-':
            // Return NULL as the parent child is NULL
            return NULL;
            break;
        case '+':
            //Take Input
            cout << "\nEnter the Data";
            cin >> n->data;
            break;
        }

        //First take the Left Child Recursively
        line();

        cout << "\nEnter Left Child for " << n->data;
        n->left = create(n);

        //Then Right Child
        line();

        cout << "\nEnter Right Child for " << n->data;
        n->right = create(n);

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

        cout << "\nTree Created Successfully!";
    }

    // Return true is tree is Empty
    bool isEmpty()
    {
        //Only if root is pointing to NULL ,the tree will be empty
        if (root == NULL)
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
        int hl, hr;
        if (temp == NULL)
            return 0;
        else
        {
            //left height
            hl = 1 + height(temp->left);
            //Right subtree height
            hr = 1 + height(temp->right);
        }
        //taking max from both sides
        if (hl > hr)
            return hl;
        else
            return hr;
    }
    void display(Node *temp)
    {

        if (temp == NULL)
        {
            return;
        }
        if (temp->right == NULL)
        {
            Q.enqueue(temp, 0);
        }
        else
        {
            display(temp->right);
            Q.enqueue(temp, 0);
        }

        display(temp->left);
    }
    void display()
    {
        int h = height(root);

        int th, tabs;
        Node *t = new Node();
        display(root);
        cout << "\n\t\tTREE\n\n";
        while (!Q.isEmpty())
        {
            t = Q.dequeue();
            th = height(t);
            tabs = h - th;
            while (tabs != 0)
            {
                cout << "\t";
                tabs--;
            }
            cout << t->data;
            cout << "\n";
        }
    }

    //Overloaded for Ease of use
    void DisplayLeaves()
    {
        Node *n;
        if (!isEmpty())
        {
            display();
            n = root;
            DisplayLeaves(n);
        }
        else
        {
            cout << "\nTree Is Empty";
        }
    }

    void DisplayLeaves(Node *temp)
    {
        if (temp->left == NULL && temp->right == NULL)
            cout << " " << temp->data;
        else
        {
            DisplayLeaves(temp->right);
            DisplayLeaves(temp->left);
        }
    }

    void levelOrder()
    {
        PriorityQ<Node *> QU;
        Node *temp;
        temp = root;

        display();
        cout << "Level Order : ";

        while (temp != NULL)
        {

            int d = temp->data;
            cout << " " << d << " ";

            if (temp->left != NULL)
                QU.enqueue(temp->left, 0);

            if (temp->right != NULL)
                QU.enqueue(temp->right, 0);

            if (!QU.isEmpty())
                temp = QU.dequeue();
            else
                temp = NULL;
        }
    }

    void insert(int d)
    {
        Node *n = new Node;

        n->data = d;
        if (isEmpty())
        {
            root = n;
        }
        else
        {
            int ch;
            Node *temp = root;

            while (1)
            {
                ch = 0;
                cout << "\n\nCurrent Node - " << temp->data;

                while (ch == 0)
                {
                    cout << "\n Enter \n 1. Traverse left \n 2. Traverse right \n from current node - ";
                    cin >> ch;
                    if (ch != 1 && ch != 2)
                    {
                        cout << "\n Please enter a valid choice... Try again !";
                        ch = 0;
                        continue;
                    }
                    break;
                }

                if (ch == 1)
                {
                    if (temp->left == NULL)
                    {
                        temp->left = new Node;
                        temp = temp->left;
                        temp->data = d;
                        cout << "\n New Node added successfully";
                        return;
                    }
                    else
                        temp = temp->left;
                }
                if (ch == 2)
                {
                    if (temp->right == NULL)
                    {
                        temp->right = new Node;
                        temp = temp->right;
                        temp->data = d;
                        cout << "\n New Node added successfully";
                        return;
                    }
                    else
                        temp = temp->right;
                }
            }
        }
    }
    void setRoot(Node *root)
    {
        this->root = root;
    }
    Node *copy()
    {
        Node *temp = root;
        Node *cRoot;
        cRoot = copy(temp);
        return cRoot;
    }

    Node *copy(Node *temp)
    {
        Node *p = NULL;
        if (temp != NULL)
        {
            p = new Node;
            p->data = temp->data;
            p->left = copy(temp->left);
            p->right = copy(temp->right);
        }
        return p;
    }
};

int main()
{
    Tree T, cT;

    int ch;

    while (ch != 8)
    {
        line();
        cout << "\nEnter Your Choice\n"
                "1) Create \n"
                "2) Display Tree\n"
                "3) Level Order Display\n"
                "4) Insert\n"
                "5) Height\n"
                "6) Display Leaves\n"
                "7) Copy\n"
                "8) EXIT\n"
                "YOUR CHOICE : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            line();
            T.create();
            break;
        case 2:
            line();
            T.display();

            break;
        case 3:
            line();

            T.levelOrder();

            break;
        case 4:
            line();
            int data;
            cout << "Enter the data";
            cin >> data;
            T.insert(data);
            T.display();

            break;
        case 5:
            line();

            cout << "\nHeight of Tree is " << T.height();
            T.display();
            break;
        case 6:
            line();
            cout << "\n\tLeaves\n";
            T.DisplayLeaves();
            line();
            break;
        case 7:
            line();
            cout << "\n\tCopy\n";
            cT.setRoot(T.copy());
            cT.display();
            line();
            break;

        case 8:
            line();
            cout << "\n\tGOOD BYE\n";
            line();
            break;
        }
    }
    return 0;
}
