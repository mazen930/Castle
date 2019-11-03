#pragma once
template<class T>
class Node
{
	T data;
	Node*next;
	Node*prev;
public:
	//	*constructors*	//
	Node();
	Node(const T& x);
	//	*setters & getters*	//
	void set_data(const T& data);
	T get_data()const;
	void set_next(Node*);
	Node* get_next()const;
	void set_prev(Node*);
	Node*get_prev()const;
};

/////////////constructors/////////////////
template<class T>
Node<T>::Node(const T& x)
{
	next=nullptr;
	prev=nullptr;
	data = x;
}

template<class T>
Node<T>::Node()
{
	next=nullptr;
	prev=nullptr;
}

/////////////setters & getters/////////////

template<class T>
void Node<T>::set_prev(Node<T>*x)
{
	prev=x;
}
template<class T>
Node<T>* Node<T>::get_prev()const
{
	return prev;
}

template<class T>
void Node<T>::set_data(const T& x)
{
	data=x;
}

template<class T>
T Node<T>::get_data()const
{
	return data;
}

template<class T>
void Node<T>::set_next(Node<T>*x)
{
	next=x;
}

template<class T>
Node<T>* Node<T>::get_next()const
{
	return next;
}
