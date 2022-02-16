#ifndef TEMPLATEDQUEUE_H
#define TEMPLATEDQUEUE_H

#include <string>
using namespace std;

template <class T>
struct QueueNode
{
	T value;
    //string name;
	QueueNode<T> * next;

	QueueNode(T v, QueueNode<T> * n = NULL): value(v), next(n) {};
};


template <class T>
class Queue
{
	private:
		QueueNode<T> *front;
		QueueNode<T> *rear;
		void createClone(const Queue<T> &);
	public:
		Queue();
		Queue(const Queue<T> &);
		void enqueue(T);
		void dequeue(T &);
		bool isEmpty() const; 
		~Queue();
        QueueNode<T>* returnRear();
        QueueNode<T>* returnFront();
};

#include "TemplatedQueue.cpp"
#endif
