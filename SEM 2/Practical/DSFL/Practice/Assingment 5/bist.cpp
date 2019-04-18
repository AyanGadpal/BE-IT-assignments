#include <iostream>
#include "Q.h"
#include "stack.h"

class NodeTree
{
  public:
    int data;
    NodeTree *left, *right;

    NodeTree()
    {
        left = right = NULL;
    }
    NodeTree(int data)
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

    // NON-RECURSIVE INSERTION
    void insert()
    {
        NodeTree *n, *p;
        int data;
        cout << "Enter the Data : ";
        cin >> data;
        n = new NodeTree(data);
        p = root;

        if (root == NULL)
        {
            root = n;
            return;
        }
        else
        {
            while (1)
            {
                if (data > p->data)
                {
                    if (p->right == NULL)
                    {
                        p->right = n;
                        return;
                    }

                    else
                        p = p->right;
                }
                else if (data < p->data)
                {
                    if (p->left == NULL)
                    {
                        p->left = n;
                        return;
                    }
                    else
                        p = p->left;
                }
                else
                {
                    cout << "\nDuplication Not Allowed!";
                    return;
                }
            }
        }
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
    void inorder()
    {
        Stack<NodeTree *> S;
        NodeTree *temp;
        temp = root;
        while (1)
        {
            while (temp != NULL)
            {
                S.push(temp);
                temp = temp->left;
            }
            if (S.isEmpty())
                return;
            temp = S.pop();
            cout << " " << temp->data;
            temp = temp->right;
        }
    }
    void preorder(NodeTree *n)
    {

        if (n != NULL)
        {
            cout << " " << n->data;
            preorder(n->left);
            preorder(n->right);
        }
    }
    void preorder()
    {
        Stack<NodeTree *> S;
        NodeTree *temp;
        temp = root;
        while (1)
        {
            while (temp != NULL)
            {
                cout << " " << temp->data;
                S.push(temp);
                temp = temp->left;
            }
            if (S.isEmpty())
                return;
            temp = S.pop();
            temp = temp->right;
        }
    }
    void postorder(NodeTree *n)
    {

        if (n != NULL)
        {
            postorder(n->left);
            postorder(n->right);
            cout << " " << n->data;
        }
    }
    void postorder()
    {
        Stack<NodeTree *> stack, stack2;
        NodeTree *temp, *temp1;
        temp = root;
        stack.push(temp);
        while (!stack.isEmpty())
        {
            temp1 = stack.pop();

            stack2.push(temp1);

            if (temp1->left != NULL)
                stack.push(temp1->left);

            if (temp1->right != NULL)
                stack.push(temp1->right);
        }
        while (!stack2.isEmpty())
        {
            cout << " " << stack2.pop()->data;
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
            cout << "\nNon Recursive ";
            inorder();
            cout << "\nRecursive";
            inorder(root);
            break;
        case 2:
            preorder();
            cout << "\nRecursive \n";
            preorder(root);
            break;
        case 3:
            postorder();
            cout << "\nRecursive \n";
            postorder(root);
            break;

        default:
            break;
        }
    }
    void deleteN(int key)
    {
        root = deleteN(key, root);
    }

    NodeTree *deleteN(int key, NodeTree *n)
    {
        if (n == NULL)
        {
            cout << "\nNOT FOUND!";
            return n;
        }
        else if (key > n->data)
            n->right = deleteN(key, n->right);
        else if (key < n->data)
            n->left = deleteN(key, n->left);
        else
        {
            if (n->left == NULL && n->right == NULL) // Case 1
            {
                delete n;
                return NULL;
            }
            if (n->left == NULL) // Case 2.1
            {
                NodeTree *temp;
                temp = n->right;
                delete n;
                return temp;
            }
            if (n->right == NULL) // Case 2.2
            {
                NodeTree *temp;
                temp = n->left;
                delete n;
                return temp;
            }
            // Case 3
            NodeTree *min;

            // Find inorder successor
            min = n->right;
            while (min->left != NULL)
                min = min->left;
            n->data = min->data;

            //Delete inorder successor form right subtree
            n->right = deleteN(min->data, n->right);
        }
        return n;
    }
};

int main()
{
    Tree BST;
    int n;
    cout << "\nHow many Nodes You want ?";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "\n"
             << i + 1 << ") ";
        BST.insert();
    }
    BST.display();
    int key;
    while (1)
    {

        cout << "\nEnter the key to be deleted : ";
        cin >> key;
        BST.deleteN(key);
        BST.display();
    }
    return 0;
}