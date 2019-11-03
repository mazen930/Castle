#pragma once
#include "list_iterator.h"

template<class T>
class List_iterator;

template<class T>
class List
{
	Node<T>*head;
	Node<T>*End;						//fake Node to indicate the end of the list
	Node<T>*get_ptr(int pos);
	int count;
	bool remove_by_prev_ptr(Node<T>*);
	friend class List_iterator<T>;		//to let the iterator know the end of the list
	//	*sorting*	//
	void merge_sort(T* arr,int size,bool(*cmp)(T,T));									//merge sort algorithm
	void merge(T*left,int lsize,T*right,int rsize,T*arr,int size,bool(*cmp)(T,T));		//merges 2 sorted lists
public:
	//	*constructor*	//
	List();
	//	*insertion*	//
	//inserts at the end of the list
	void push_back(const T& data);
	//inserts a new node at pos
	//pos should be >= 0 and <= list.size(), otherwise the function returns false
	bool insert(int pos, const T& data);
	//inserts a new node at the place pointed to by the iterator
	//the iterator should be >= list.begin() and <= list.end() and be iterator to this list 
	//otherwise the function returns false
	bool insert(const List_iterator<T>& it, const T& data);

	//	*deletion*	//
	//deletes the node pointed to by the iterator, then advances it
	//the iterator should be >= list.begin() and < list.end() and be iterator to this list 
	//otherwise the function returns false
	bool erase(List_iterator<T>& it);

	//	*size*	//
	bool isempty()const;
	int size()const;

	//	*copyconstructor*	//
	List<T>(const List<T>& l);

	//	*assignment operator*	//
	const List<T>& operator=(const List<T>& l);

	//	*iterators*	//
	typedef List_iterator<T> iterator;
	//returns iterator to the beginning of the list
	List_iterator<T> begin();
	//returns iterator to the end of the list
	List_iterator<T> end();
	//	*sorting*	//
	void sort(bool(*cmp)(T,T));
	//	*destructor*	//
	void clear();
	~List();
};

template<class T>
List<T>::List()
{
	count=0;
	End=new Node<T>;
	head=End;
}

template<class T>
Node<T>* List<T>::get_ptr(int pos)		//utility function
{
	if(pos<0 || pos>count)
		return nullptr;
	Node<T>*ptr=head;
	for(int i=0; i<pos ; i++)
		ptr=ptr->get_next();
	return ptr;
}


template<class T>
bool List<T>::isempty()const
{
	return (head==End);
}

template<class T>
int List<T>::size()const
{
	return count;
}

template<class T>
void List<T>::push_back(const T& x)
{
	insert(end(),x);
}

template<class T>
bool List<T>::insert(int pos , const T& data)
{
	if(pos<0||pos>count) return false;
	Node<T>*temp=new Node<T>(data);
	if(pos==0)
	{
		temp->set_next(head);
		head->set_prev(temp);
		head=temp;
	}
	else
	{
		Node<T>*ptr=get_ptr(pos-1);
		Node<T>*place=ptr->get_next();
		temp->set_next(place);
		place->set_prev(temp);
		ptr->set_next(temp);
		temp->set_prev(ptr);
	}
	count++;
	return true;
}

template<class T>
bool List<T>::insert(const List_iterator<T>&it ,const T& data)
{
	if(it.cont != this || it.ptr == nullptr)
		return false;
	Node<T>*temp=new Node<T>(data);
	Node<T>*place = it.ptr;
	if(place == head)
	{
		temp->set_next(head);
		head->set_prev(temp);
		head=temp;
	}
	else
	{
		Node<T>*ptr=place->get_prev();
		temp->set_next(place);
		place->set_prev(temp);
		ptr->set_next(temp);
		temp->set_prev(ptr);
	}
	count++;
	return true;
}

template<class T>
bool List<T>::remove_by_prev_ptr(Node<T>*prev_ptr)		//utility function	
{
	if(isempty())
		return false;
	Node<T>*temp;
	if(prev_ptr==nullptr)	//remove the first element
	{
		temp=head;
		head=head->get_next();
		head->set_prev(nullptr);
	}
	else
	{
		temp=prev_ptr->get_next();
		Node<T>*temp2=temp->get_next();
		prev_ptr->set_next(temp2);
		temp2->set_prev(prev_ptr);
	}
	delete temp;
	count--;
	if(count==0)
		head=End;
	return true;
}

template<class T>
bool List<T>::erase(List_iterator<T>&it)
{
	if(it.cont!=this || it.ptr==End || it.ptr==nullptr)
		return false;
	List_iterator<T> temp=it;
	it++;
	return remove_by_prev_ptr((temp.ptr)->get_prev());
}

template<class T>
List<T>::List(const List<T>& l)
{
	count=l.count;
	End=new Node<T>;
	if(l.isempty())
	{
		head = End;
		return;
	}
	head = new Node<T>(l.head->get_data());
	Node<T>* copy = head;
	Node<T>* original = l.head->get_next();
	Node<T>* newNodePtr;
	while (original != l.End)
	{
		newNodePtr = new Node<T>(original->get_data());
		
		copy->set_next(newNodePtr);
		newNodePtr->set_prev(copy);
		copy = newNodePtr;
		original = original->get_next();
	}
	copy->set_next(End);
	End->set_prev(copy);
}

template<class T>
const List<T>& List<T>::operator=(const List<T>& l)
{
	if(this == &l)	//to prevent self assignment
		return *this;
	clear();
	count=l.count;
	if(l.isempty())
		return *this;
	head = new Node<T>(l.head->get_data());
	Node<T>* copy = head;
	Node<T>* original = l.head->get_next();
	Node<T>* newNodePtr;
	while (original != l.End)
	{
		newNodePtr = new Node<T>(original->get_data());
		copy->set_next(newNodePtr);
		newNodePtr->set_prev(copy);
		copy = newNodePtr;
		original = original->get_next();
	}
	copy->set_next(End);
	End->set_prev(copy);
	return *this;
}

template<class T>
List_iterator<T> List<T>::begin()
{
	return List_iterator<T>(this,head);
}

template<class T>
List_iterator<T> List<T>::end()
{
	return List_iterator<T>(this,End);
}

template<class T>
void List<T>::merge(T*left,int lsize,T*right,int rsize,T*arr,int size,bool(*cmp)(T,T))
{
	int i=0,j=0,k=0;
	while(i<lsize && j<rsize)
	{
		if(cmp(left[i],right[j]))
			arr[k++]=left[i++];
		else
			arr[k++]=right[j++];
	}
	while(i<lsize)
		arr[k++]=left[i++];
	while(j<rsize)
		arr[k++]=right[j++];
}

template<class T>
void List<T>::merge_sort(T* arr,int size,bool(*cmp)(T,T))
{
	if(size<2)
		return;
	int lsize=size/2,rsize=size-lsize;
	T* left=new T[lsize];
	T* right=new T[rsize];
	for(int i=0;i<lsize;i++)
		left[i]=arr[i];
	for(int i=lsize;i<size;i++)
		right[i-lsize]=arr[i];
	merge_sort(left,lsize,cmp);
	merge_sort(right,rsize,cmp);
	merge(left,lsize,right,rsize,arr,size,cmp);
	delete[]left;
	delete[]right;
}

template<class T>
void List<T>::sort(bool(*cmp)(T,T))
{
	T*arr=new T[count];
	int size=0;
	Node<T>*first=head;
	while(first != End)
	{
		arr[size++]=first->get_data();
		first=first->get_next();
	}
	merge_sort(arr,size,cmp);
	first=head;
	for(int i=0;i<size && first!=End;i++,first=first->get_next())
	{
		first->set_data(arr[i]);
	}
	delete[]arr;
}
template<class T>
void List<T>::clear()
{
	Node<T>* ptr = head;
	while (ptr!=End)
	{
		head = ptr->get_next();
		delete ptr;
		ptr = head;
	}
	count=0;
}

template<class T>
List<T>::~List()
{
	clear();
	delete End;
}