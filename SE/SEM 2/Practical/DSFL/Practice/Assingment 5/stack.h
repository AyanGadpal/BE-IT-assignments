#include <iostream>

using namespace std;

template <typename T>
class Node
{
  public:
    Node<T> *down;
    T data;
    Node()
    {
        down = NULL;
    }
    Node(T data)
    {
        this->data = data;
    }
};

template <typename T>
class Stack
{
  public:
    Node<T> *Top;

    Stack()
    {
        Top = NULL;
    }

    bool isEmpty() // Returns whearther stack is empty or not
    {
        return (Top == NULL);
    }

    void push(T data) // Push data into the top of the stack
    {
        Node<T> *n;
        n = new Node<T>(data);
        n->down = Top;
        Top = n;
    }
    T pop() // Pop the data out of the stack
    {
        if (!isEmpty())
        {
            Node<T> *temp;
            T data;
            temp = Top;
            data = temp->data;
            Top = Top->down;
            delete (temp);
            return data;
        }
        cout << "\nStack Underflow\n";
        exit(0);
    }
    T seek()
    {
        if (!isEmpty())
            return Top->data;
        else
            cout << "\nStack Underflow\n";
    }
};