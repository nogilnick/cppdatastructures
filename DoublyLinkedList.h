#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "List.h"
template <typename T>
class LinkedList : public List<T>
{
public:
	/**
	 * Adds an element to the end of the list
	 * @param ele Is the element to add
	 */
	virtual void Add(const T& ele)
	{	//Create the new list node
		Node* newNode = new Node(ele, NULL, tail);
		if(tail == NULL)
		{	//List is empty
			head = tail = newNode;
		}
		else
		{
			//Add the node to the end of the list
			tail->next = newNode;
			tail = newNode;
		}
		++n;
		return;
	}

	/**
	 * Clears the list
	 */
	virtual void Clear()
	{
		while(Size() > 0)
			Remove(0);
	}
	
	/**
	 * Gets the i-th element of the list
	 * @param i The index
	 * @return The element at index i, or null
	 * if it does not exist.
	 */	 
	virtual T& Get(Index i) const
	{	//If index is out of range; throw an exception
		if(Size() <= i)
			throw List<T>::BAD_INDX;
		Node* lstPtr = head;
		//Traverse to the element
		for(Index j = 0; j < i; ++j)
			lstPtr = lstPtr->next;
		return lstPtr->item;
	}
	
	/**
	 * Create an empty list
	 */
	LinkedList()
	{
		head = tail = NULL;
		n = 0;
	}

	/**
	 * Copy constructor
	 */
	LinkedList(const LinkedList& lst)
	{
		head = tail = NULL;
		n = 0;
		Copy(lst);
	}

	/**
	 * LinkedList destructor
	 */
	virtual ~LinkedList()
	{
		Clear();
	}

	/**
	 * Overloaded assignment operator; perform
	 * deep copy.
	 * @param lst The list to copy
	 * @return A reference to this
	 */
	LinkedList& operator=(const LinkedList& lst)
	{	//Test for self-assignment
		Copy(lst);
		return *this;
	}

	/**
	 * List concatenation operator
	 * @param l1 The first list
	 * @param l2 The second list
	 * @return The concatenation of l1 and l2
	 */
	friend LinkedList operator+(const LinkedList& l1, const LinkedList& l2)
	{	//Use R.V.O. to return by value efficiently
		LinkedList ll;
		for(unsigned int i = 0; i < l1.Size(); ++i)
			ll.Add(l1.Get(i));
		for(unsigned int i = 0; i < l2.Size(); ++i)
			ll.Add(l2.Get(i));
		return ll;
	}

	/**
	 * Removes an element from the list
	 * @param i The index of the element to remove
	 */
	virtual void Remove(Index i)
	{	//If index is out of range; throw an exception
		if(Size() <= i)
			throw List<T>::BAD_INDX;
	    Node* lstPtr = head;
		if(n == 1)
		{	//Only have one element
			delete head;
			head = tail = NULL;
			n = 0;
			return;
		}
		//We know there are > 1 elements
		//Traverse to the element
		for(Index j = 0; j < i; ++j)
			lstPtr = lstPtr->next;
		if(lstPtr->prev == NULL)
		{	//At the front of the list
			head = head->next;
			head->prev = NULL;
			delete lstPtr;
		}	
		else if(lstPtr->next == NULL)
		{	//At the end
			tail = tail->prev;
			tail->next = NULL;
			delete lstPtr;
		}			
		else
		{	//In the middle
			lstPtr->prev->next = lstPtr->next;
			lstPtr->next->prev = lstPtr->prev;
			delete lstPtr;
		}
	    --n;
	}
	
	/**
	 * Sets the i-th element
	 * @param i The index
	 * @param val The element to set
	 */
	virtual void Set(Index i, const T& val)
	{	//If index is out of range; throw an exception
		if(Size() <= i)
			throw List<T>::BAD_INDX;
		Node* lstPtr = head;
		//Traverse to the element
		for(Index j = 0; j < i; ++j)
			lstPtr = lstPtr->next;
		lstPtr->item = val;
	}
	
	/**
	 * Gets the size of the list
	 * @return The size
	 */
	virtual unsigned int Size() const
	{
		return n;
	}
	
private:

	//Linked list node
	class Node
	{
	public:
		Node() { next = prev = NULL; }
		Node(const T& ele, Node* n, Node* p) {item = ele; next = n; prev = p;}
		T item;
		Node* prev;
		Node* next;
	};
	
	/**
	 * Copies lst
	 * @param lst The list to copy
	 */
	void Copy(const LinkedList& lst)
	{
		if(this == &lst)
			return;
		Clear();
		for(unsigned int i = 0; i < lst.Size(); ++i)
			this->Add(lst.Get(i));
	}
	
	Node* tail;
	Node* head;
	unsigned int n;
};
#endif
