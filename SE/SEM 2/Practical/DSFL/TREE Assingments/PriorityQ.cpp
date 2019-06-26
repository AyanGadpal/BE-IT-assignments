/*
 * PriorityQ.cpp
 *
 *  Created on: 21-Jan-2019
 *      Author: Ayan 23370
 */
#include <iostream>
#include "PriorityQ.h"
using namespace std;


	template <typename T>
		PriorityQ<T>::PriorityQ() {
			front.next=NULL;
			rear.next=NULL;
		}

	template <typename T>
	void PriorityQ<T>::enqueue(T a,int priority)
	{
		node *temp,*t;

		temp = new node;
		temp->item = a;
		temp->priority = priority;
		if(isEmpty())
		{
			front.next = temp;
			rear.next = temp;
			temp->next = NULL;
			return;
		}
		else
		{
			t = &front;

			while(t->next != NULL)
			{
				if(t->next->priority < priority)
				{
					temp->next = t->next;
					t->next = temp;
					return;
				}
				if(t->next->priority >= priority)
				{
					t = t->next;
				}


			}

			rear.next -> next = temp;
			rear.next=temp;
		}

	}

	template <typename T>
	T PriorityQ<T>::dequeue(void)
	{
		T temp;
		node *t;
		t = new node;
		if(!isEmpty())
		{
			temp = front.next->item;
			t = front.next;
			if(front.next==rear.next)
			{
				front.next = rear.next = NULL;
			}
			else
				front.next = front.next->next;
			delete(t);
		}
		else
		{
			cout<<"\nQUEUE ERROR:IS EMPTY\n";
		}
		return temp;
	}

	template <typename T>
	bool PriorityQ<T>::isEmpty(void)
	{
			if(front.next == NULL && rear.next == NULL)
				return true;

			return false;
	}

	template <typename T>
	T PriorityQ<T>::getFront()
	{
		return front.next->item;
	}

	template <typename T>
	void PriorityQ<T>::display()
	{
		struct node *t;
		t = new node;
		t = front.next;
		if(!isEmpty())
		{
			while(t!=NULL)
			{
				cout<<t->item;
				t = t->next;
			}
		}

	}

	template <typename T>
	PriorityQ<T>::~PriorityQ() {}
