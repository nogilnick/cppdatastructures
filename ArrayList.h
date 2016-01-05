#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "List.h"
#include "QSort.h"
template <typename T>
class ArrayList : public List<T>
{
public:
	/**
	 * Adds an element to the end of the list
	 * @param ele Is the element to add
	 */
	virtual void Add(const T& ele)
	{	//Check if resize is necessary
		if(n >= max)
			ResizeArr(max * 2);
		arr[n++] = ele;
	}
	
	/**
	 * Adds an element to list at index i
	 * Throws BAD_INDX if i >= Size || i < 0
	 * @param ele Is the element to add
	 * @param i Is the index to insert ele
	 */
	virtual void Add(const T& ele, Index i)
	{	//If index is out of range; throw an exception
		if(Size() <= i)
			throw this->BAD_INDX;
		//Check if resize is necessary
		if(n + 1 == max)
			ResizeArr(max * 2);
		//Shift elements to the right
		for(Index j = n; j > i; --j)
			arr[j] = arr[j - 1];
		//Insert item at i
		arr[i] = ele;
		++n;
	}
	/**
	 * Create an array with a capacity
	 * of 10.
	 * @param c The capacity
	 */
	ArrayList()
	{
		max = DEF_CAPC;
		arr = new T[DEF_CAPC];
		n = 0;
	}
	
	/**
	 * Create an array with a certain
	 * capacity.
	 * @param c The capacity
	 */
	ArrayList(unsigned int c)
	{
		max = c;
		arr = new T[max];
		n = 0;
	}

	/**
	 * Copy constructor
	 * @param lst  The list to copy
	 */
	ArrayList(const ArrayList& lst)
	{
		n = max = 0;
		arr = 0;
		Copy(lst);
	}

	/**
	 * Destructor
	 */
	virtual ~ArrayList()
	{
		delete [] arr;
	}

	/**
	 * Clears the list
	 */
	virtual void Clear()
	{
		delete [] arr;
		n = 0;
		max = DEF_CAPC;
		arr = new T[max];
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
			throw this->BAD_INDX;
		return arr[i];
	}
	
	/**
	 * Overloaded assignment operator; perform
	 * deep copy.
	 * @param lst The list to copy
	 * @return A reference to this
	 */
	ArrayList& operator=(const ArrayList& lst)
	{
		Copy(lst);
		return *this;
	}

	/**
	 * List concatenation operator
	 * @param l1 The first list
	 * @param l2 The second list
	 * @return The concatenation of l1 and l2
	 */
	friend ArrayList operator+(const ArrayList& l1, const ArrayList& l2)
	{	//Use R.V.O. to return by value efficiently
		ArrayList l3 = ArrayList(l1.Size() + l2.Size());
		for(unsigned int i = 0; i < l1.Size(); ++i)
			l3.Add(l1.Get(i));
		for(unsigned int i = 0; i < l2.Size(); ++i)
			l3.Add(l2.Get(i));
		return l3;
	}

	/**
	 * Removes an element from the list
	 * @param i The index of the element to remove
	 */
	virtual void Remove(Index i)
	{	//If index is out of range; throw an exception
		if(Size() <= i)
			throw this->BAD_INDX;
		//Overwrite element
		for(Index j = i + 1; j < Size(); ++j)
			arr[j - 1] = arr[j];
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
			throw this->BAD_INDX;
		arr[i] = val;
	}

	void Sort()
	{
		QuickSort(arr, 0, n - 1);
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
	//Default capacity
	const static int DEF_CAPC = 10;

	/**
	 * Copies lst
	 * @param lst The list to copy
	 */
	void Copy(const ArrayList& lst)
	{
		if(this == &lst)
			return;
		Clear();
		for(unsigned int i = 0; i < lst.Size(); ++i)
			Add(lst.Get(i));
	}

	/**
	 * Resize the list's array
	 * @param The new size of the array
	 */
	void ResizeArr(unsigned int cap)
	{
		max = cap;
		T* tmp = new T[cap];
		for(unsigned int i = 0; i < n; ++i)
			tmp[i] = arr[i];
		delete [] arr;
		arr = tmp;
	}
	//The array
	T* arr;
	//The size of the array
	unsigned int n;
	//The capacity of the array
	unsigned int max;
};

#endif
