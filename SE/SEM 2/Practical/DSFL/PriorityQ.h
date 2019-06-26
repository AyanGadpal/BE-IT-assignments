/*
 * PriorityQ.h
 *
 *  Created on: 21-Jan-2019
 *      Author: h11
 */
#include <iostream>
#ifndef PRIORITYQ_H_
#define PRIORITYQ_H_

using namespace std;



	template <typename T>
	class PriorityQ {
		struct node
		{
			T item;
			int priority;
			node *next;
		};
		struct node front,rear;
	public:
		PriorityQ();
		void enqueue(T,int);
		T dequeue();
		bool isEmpty();
		void display();
		T getFront();
		void makeEmpty();
		virtual ~PriorityQ();
	};




#endif /* PRIORITYQ_H_ */

