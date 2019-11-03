#pragma once
#include "Node.h"
#include<iterator>
#include<cassert>
using namespace std;
template<class T>
class List;

template<class T> 
class List_iterator:public iterator<bidirectional_iterator_tag,int>
{
	friend class List<T>;						//to check the end of the list
	Node<T>* ptr;							//pointer to the current node
	const List<T>*cont;					//pointer to the list that contains the current node
public:
	//	*constructors*	//
	List_iterator();
	List_iterator(const List<T>* listPtr, Node<T>*nptr);
	//	*overloaded operators*	//
	List_iterator<T>& operator++();	//prefix
	const List_iterator<T> operator++(int);	//postfix
	T operator*()const;
	List_iterator<T>& operator--();	//prefix
	const List_iterator<T> operator--(int);	//postfix
	bool operator==(const List_iterator<T>&it)const;
	bool operator!=(const List_iterator<T>&it)const;
};
//	*constructors*	//
template<class T> 
List_iterator<T>::List_iterator()
{
	ptr=nullptr;
	cont = nullptr;
}

template<class T> 
List_iterator<T>::List_iterator(const List<T>* listPtr, Node<T>*nptr):cont(listPtr)
{
	ptr = nptr;
}

//	*overloaded operators*	//

template<class T> 
List_iterator<T>& List_iterator<T>::operator++()	//prefix
{
	assert(ptr != nullptr && ptr != cont->End);	//check if it didn't reach the end of the list or if it points to null
	ptr=ptr->get_next();
	return *this;
}

template<class T> 
const List_iterator<T> List_iterator<T>::operator++(int)	//postfix
{
	List_iterator<T> temp=*this;
	assert(ptr != cont->End && ptr != nullptr);
	ptr=ptr->get_next();
	return temp;
}

template<class T> 
T List_iterator<T>::operator*()const
{
	assert(ptr != cont->End && ptr != nullptr);	//check if it didn't reach the end of the list or if it points to null
	return ptr->get_data();
}

template<class T> 
List_iterator<T>& List_iterator<T>::operator--()	//prefix
{
	assert(ptr != nullptr);
	ptr=ptr->get_prev();
	return *this;
}

template<class T> 
const List_iterator<T> List_iterator<T>::operator--(int)	//postfix
{
	List_iterator<T> temp=*this;
	assert(ptr != nullptr);
	ptr=ptr->get_prev();
	return temp;
}

template<class T> 
bool List_iterator<T>::operator==(const List_iterator<T>&it)const
{
	return (ptr==it.ptr && cont==it.cont);	//check if they were the same and there list is the same
}

template<class T> 
bool List_iterator<T>::operator!=(const List_iterator<T>&it)const
{
	return (ptr!=it.ptr || cont!=it.cont);
}