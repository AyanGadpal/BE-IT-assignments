#include <iostream>
using namespace std;

template <typename T>
class NodeQ
{
  public:
    T data;
    NodeQ<T> *next;
    NodeQ()
    {
        next = NULL;
    }
    NodeQ(T data)
    {
        this->data = data;
        next = NULL;
    }
};
template <typename T>
class Queue
{
  public:
    NodeQ<T> *front, *rear;
    Queue()
    {
        front = rear = NULL;
    }
    bool isEmpty()
    {
        return (front == NULL && rear == NULL);
    }
    void enqueue(T data)
    {
        NodeQ<T> *n;
        n = new NodeQ<T>(data);
        if (isEmpty())
        {
            front = rear = n;
        }
        else
        {
            rear->next = n;
            rear = n;
        }
    }
    T dequeue()
    {
        NodeQ<T> *temp;
        T data;
        if (!isEmpty())
        {
            temp = front;
            if (front == rear)
                front = rear = NULL;
            else
                front = front->next;
            data = temp->data;
            delete (temp);
            return data;
        }
        else
        {
            cout << "Empty!";
            exit(1);
        }
    }
};

