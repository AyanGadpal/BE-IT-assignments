#include <iostream>
#include <string.h>
#include "stack.h"
#include "Q.h"
using namespace std;
int determine(char);

class NodeTree
{
  public:
    char data;
    NodeTree *left, *right;

    NodeTree()
    {
        left = right = NULL;
    }
    NodeTree(char data)
    {
        this->data = data;
    }
};

class Tree
{
  public:
    NodeTree *root;
    Tree()
    {
        root = NULL;
    }

    bool create(char exp[])
    {
        Stack<NodeTree *> stack;
        NodeTree *newNodeTree;
        for (int i = 0; exp[i] != '\0'; i++)
        {
            newNodeTree = new NodeTree();
            if (determine(exp[i]) == 1) // operand
            {
                newNodeTree->data = exp[i];
                newNodeTree->left = NULL;
                newNodeTree->right = NULL;
            }
            if (determine(exp[i]) == 2) // operator
            {
                newNodeTree->data = exp[i];
                newNodeTree->right = stack.pop();
                newNodeTree->left = stack.pop();
            }
            stack.push(newNodeTree);
        }
        root = stack.pop();
        if (!stack.isEmpty())
            return false;
        return true;
    }

    void inorder(NodeTree *n)
    {
        if (n != NULL)
        {
            inorder(n->left);
            cout << n->data;
            inorder(n->right);
        }
    }
    void preorder(NodeTree *n)
    {

        if (n != NULL)
        {
            cout << n->data;
            preorder(n->left);
            preorder(n->right);
        }
    }
    void postorder(NodeTree *n)
    {

        if (n != NULL)
        {
            postorder(n->left);
            postorder(n->right);
            cout << n->data;
        }
    }

    void levelOrder()
    {
        Queue<NodeTree *> Q;
        NodeTree *n;
        n = root;
        while (n != NULL)
        {
            cout << n->data;

            if (n->left != NULL)
                Q.enqueue(n->left);
            if (n->right != NULL)
                Q.enqueue(n->right);
            if (!Q.isEmpty())
                n = Q.dequeue();
            else
                n = NULL;
        }
    }

    void display()
    {
        int ch;
        cout << "\nEnter your Choice "
                "\n 1) Inorder"
                "\n 2) Preorder"
                "\n 3) Postorder"
                "\n 4) LevelOrder"
                " \n Your Choice : ";

        cin >> ch;
        switch (ch)
        {
        case 1:
            inorder(root);
            break;
        case 2:
            preorder(root);
            break;
        case 3:
            postorder(root);
            break;
        case 4:
            levelOrder();
            break;

        default:
            break;
        }
    }
};

int determine(char ch)
{
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= 48 && ch <= 57))
        return 1;
    return 2;
}

int main()
{
    Tree ET;
    char postfix[20];
    cout << "\nEnter the PostFix Expression : ";
    cin >> postfix;
    cout <<endl <<strrev(postfix);
    if (!ET.create(postfix))
    {
        cout << "\nInvalid Expression !";
        exit(0);
    }

    ET.display();

    return 0;
}