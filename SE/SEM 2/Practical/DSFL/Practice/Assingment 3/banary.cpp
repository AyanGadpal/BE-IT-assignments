#include <iostream>

using namespace std;

class Node
{
  public:
    Node *left, *right;
    int data;
    Node()
    {
        left = right = NULL;
    }
};

class Tree
{
  public:
    Node *root;
    Tree()
    {
        root = NULL;
    }
    Tree(Node *r)
    {
        root = r;
    }
    void Create()
    {
        root = create();
        cout << "\nTree Created!";
    }
    Node *create()
    {
        Node *n;
        char ch;
        n = new Node();
        cout << "\nEnter + for data,- for NULL";
        cin >> ch;
        switch (ch)
        {
        case '+':
            cout << "Enter the data";
            cin >> n->data;
            break;
        case '-':
            return NULL;
            break;

        default:
            break;
        }

        cout << "\nEnter Left Child for " << n->data;
        n->left = create();

        cout << "\nEnter Right Child for " << n->data;
        n->right = create();

        return n;
    }
    void inorder(Node *n)
    {
        if (n != NULL)
        {
            inorder(n->left);
            cout << n->data;
            inorder(n->right);
        }
    }
    void preorder(Node *n)
    {

        if (n != NULL)
        {
            cout << n->data;
            preorder(n->left);
            preorder(n->right);
        }
    }
    void postorder(Node *n)
    {

        if (n != NULL)
        {
            postorder(n->left);
            postorder(n->right);
            cout << n->data;
        }
    }

    void display()
    {
        int ch;
        cout << "\nEnter your Choice "
                "\n 1) Inorder"
                "\n 2) Preorder"
                "\n 3) Postorder"
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

        default:
            break;
        }
    }
    void height()
    {
        int h;
        h = height(root);
        cout << "\nHeight : " << h;
    }
    int height(Node *temp)
    {
        if (temp == NULL)
            return 0;
        int hl, hr;
        hl = height(temp->left);
        hr = height(temp->left);
        if (hl >= hr)
            return hl + 1;
        else
            return hr + 1;
    }
    void displayLeafs()
    {
        displayLeafs(root);
    }
    void displayLeafs(Node *n)
    {
        if (n != NULL) //to Handle Segmentation fault (my best friend)
            if (n->right == NULL && n->left == NULL)
                cout << " " << n->data;
            else
            {
                displayLeafs(n->left);
                displayLeafs(n->right);
            }
    }
    Node* copy()
    {
        Node *n;
        n = copy(root);
        return n;
    }
    Node* copy(Node *t)
    {
        Node *n;
        n = new Node();
        if (t != NULL)
        {
            n->data = t->data;
            n->left = copy(t->left);
            n->right = copy(t->right);
            return n;
        }
        else
            return NULL;
    }
};
int main()
{
    Tree T,C;
    T.Create();
    T.display();
    T.height();
    T.displayLeafs();
    C = T.copy();
    C.display();
    return 0;
}