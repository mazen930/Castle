#pragma once
#include"Node.h"

template<class T>
class queue
{
	Node<T>*front;
	Node<T>*end;
	int count;
public:
	queue();											//default constructor
	void enqueue(const T&);								//insertion ( at end )
	bool dequeue();										//deletion	( from begin )
	bool isempty()const;								
	T peekFront();										//first element
	const queue<T>& operator=(const queue<T>& l);		//assignment operator
	queue(const queue<T>& l);							//copy constructor
	void  clear();	
	int get_count()const;
	~queue();											//destructor		
};

template<class T>
queue<T>::queue()
{
	front=nullptr;
	end=nullptr;
	count=0;
}

template<class T>
void queue<T>::enqueue(const T& x)
{
	Node<T>*newnode=new Node<T>(x);
	if(isempty())
	{
		front=end=newnode;
		count++;
		return;
	}
	end->set_next(newnode);
	end=newnode;
	count++;
}

template<class T>
bool queue<T>::dequeue()
{
	if(isempty())
		return false;
	Node<T>*temp=front;
	if(front==end)					//one element
	{
		front=end=nullptr;
		count--;
	}
	else
	{
		front=front->get_next();  //shift front
		count--;
	}
	delete temp;
	return true;
}

template<class T>
bool queue<T>::isempty()const
{
	return (!front&&!end);			//front and end are equal to null
}

template<class T>
T queue<T>::peekFront()
{
	return front->get_data();
}

template<class T>
queue<T>::queue(const queue<T>& l)
{
	if(l.isempty())										//empty queue
	{
		front = nullptr;
		end = nullptr;
		return;
	}
	front = new Node<T>(l.front->get_data());
	Node<T>* copy = front;
	Node<T>* original = l.front->get_next();
	Node<T>* newNodePtr;
	while (original)
	{
		newNodePtr = new Node<T>(original->get_data());
		copy->set_next(newNodePtr);
		newNodePtr->set_prev(copy);
		copy = newNodePtr;
		original = original->get_next();
	}
	end = copy;
}

template<class T>
const queue<T>& queue<T>::operator=(const queue<T>& l)
{
	if(this == &l)								//to prevent self assignment
		return *this;
	clear();									//clearing the data of the left operand
	if(l.isempty())								//empty queue
	{
		front = nullptr;
		end = nullptr;
		count = 0;
		return*this;
	}
	front = new Node<T>(l.front->get_data());
	Node<T>* copy = front;
	Node<T>* original = l.front->get_next();
	Node<T>* newNodePtr;
	count = l.count;
	while (original)
	{
		newNodePtr = new Node<T>(original->get_data());
		copy->set_next(newNodePtr);
		newNodePtr->set_prev(copy);
		copy = newNodePtr;
		original = original->get_next();
	}
	end = copy;
	return *this;
}

template<class T>
void queue<T>::clear()
{
	while (!isempty())
	{
		dequeue();
	}
	count=0;
}

template<class T>
int queue<T>:: get_count()const
{
	return count;
}

template<class T>
queue<T>::~queue()
{
	clear();
}