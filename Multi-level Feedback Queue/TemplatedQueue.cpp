#include <iostream>
#include "TemplatedQueue.h"

using namespace std;

//Default constructor
template <class T>
Queue<T>::Queue()
{
	front = NULL;
	rear = NULL;
}

//Function createClone copies the content of the parameter
//into lhs (deep)
template <class T>
void Queue<T>::createClone(const Queue<T> & copy)
{
	if (copy.front == NULL) 
	{
		front = NULL;
		rear = NULL;
	}
	else
	{
		QueueNode<T> * temp = copy.front;
		front = new QueueNode<T>(temp->value, NULL);
		rear = front;

		while(temp->next != NULL) 
		{
			temp = temp->next;
			rear->next = new QueueNode<T>(temp->value, NULL);
			rear = rear->next;
		}
	}
}

//Copy constructor
template <class T>
Queue<T>::Queue(const Queue<T> & copy)
{
	createClone(copy);
}


// Function enqueue inserts the value        
// at the rear of the queue.                 
template <class T>
void Queue<T>::enqueue(T elmt)
{
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode<T>(elmt);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode<T>(elmt);
		rear = rear->next;
	}
}



// Function isEmpty returns true if the queue 
// is empty, and false otherwise.             
template <class T>
bool Queue<T>::isEmpty() const
{
	if (front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Function dequeue deletes the first element in the queue
//and assigns its value to the parameter
template <class T>
void Queue<T>::dequeue(T &elmt)
{
	QueueNode<T> *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		elmt = front->value;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//destructor
template <class T>
Queue<T>::~Queue()
{
	T temp;
	while(!isEmpty())
	{
		dequeue(temp);
	}
}

template <class T>
QueueNode<T>* Queue<T>::returnRear()
{
    return rear;
}

template <class T>
QueueNode<T>* Queue<T>::returnFront()
{
    return front;
}
