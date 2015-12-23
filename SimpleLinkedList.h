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
		LNode* newNode = new LNode(ele, headPtr);
		//Set the node as the new head node
		headPtr = newNode;
		++n;
		return;
	}
	
	/**
	 * Clears the list
	 */
	virtual void Clear()
	{
		while(headPtr != NULL)
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
		LNode* lstPtr = headPtr;
		//Traverse to the element
		for(Index j = 0; j < (n - i - 1); ++j)
			lstPtr = lstPtr->next;
		return lstPtr->item;
	}
	
	/**
	 * Create an empty list
	 */
	LinkedList()
	{
		headPtr = NULL;
		n = 0;
	}

	/**
	 * Copy constructor
	 */
	LinkedList(const LinkedList& lst)
	{
		n = 0;
		headPtr = NULL;
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
	    LNode* lstPtr = headPtr;
	    //It is the first element
	    if(i == n - 1)
	    {
	        headPtr = headPtr->next;
	        delete lstPtr;
	    }
	    else
	    {
			//Traverse to the element
			for(Index j = 0; j < (n - i - 2); ++j)
				lstPtr = lstPtr->next;
			LNode* oldNode = lstPtr->next;
			//If the next node is NULL; set the next to NULL
			//lstPtr->next = (oldNode == NULL ? NULL : oldNode->next);
			lstPtr->next = oldNode->next;
			delete oldNode;
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
		LNode* lstPtr = headPtr;
		//Traverse to the element
		for(Index j = 0; j < (n - i - 1); ++j)
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
	class LNode
	{
	public:
		LNode() { next = NULL; }
		LNode(const T& ele, LNode* n) {item = ele; next = n;}
		T item;
		LNode* next;
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
			Add(lst.Get(i));
	}

	LNode* headPtr;
	unsigned int n;
};
#endif
