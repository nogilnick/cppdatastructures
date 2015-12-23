#ifndef PQUEUE_H
#define PQUEUE_H
/**
 * An array-based priority queue class, as implemented
 * in class.
 */
template <typename T>
class PQueue
{
public:
    //Error code for "empty queue" exception
	const static int EMPTY_Q = -1;
	
	/**
	 * Adds an element to the priority queue
	 * @param ele Is the element to add
	 */
	void Insert(const T& ele)
	{	//Check if resize is necessary
		if(n >= max) //If so, double the capacity
			ResizeArr(max * 2);
		//Next, find where ele belongs in the array
		int i; //i will be the location where ele belongs
		for(i = 0; i < n; ++i)
		{	//Loop over all elements in q
			if(arr[i] > ele) 
				break; //Found location; break
		}
		//Shift elements to the right to make room
		//for ele
		for(int j = n; j > i; --j)
			arr[j] = arr[j - 1];
		//Insert item at i
		arr[i] = ele;
		//Increment number of elements in the P.Q.
		++n;
	}
	
	/**
	 * Create a queue with default capacity
	 */
	PQueue()
	{   //Use an arbitrary default capacity
		max = DEF_CAPC;
		arr = new T[DEF_CAPC];
		//There are 0 elements in the P.Q.; set n = 0
		n = 0;
	}
	
	/**
	 * Create a Queue with an array having
	 * a certain capacity.
	 * @param c The capacity
	 */
	PQueue(unsigned int c)
	{	//Use the user specified capacity for
		//The underlying array
		max = c;
		arr = new T[max];
		//There are 0 elements in the P.Q.; set n = 0
		n = 0;
	}

	/**
	 * Copy constructor
	 * @param lst  The list to copy
	 */
	PQueue(const PQueue& lst)
	{	//Make sure to set arr to NULL so that
		//Copy does not delete an invalid pointer
		//calling delete on a NULL pointer is OK
		//Calling delete on an uninitialized pointer is BAD
		arr = NULL;
		Copy(lst);
	}

	/**
	 * Destructor
	 */
	~PQueue()
	{	//Free the dynamically allocated array
		delete [] arr;
	}
	
	/**
	 * Gets the element with highest priority
	 * @return The element with highest priority
	 */	 
	T& Max() const
	{	//If the queue is empty; throw an exception
		if(Size() == 0)
			throw EMPTY_Q;
		//Because we insert in sorted order, the last element
		//in the array has highest priority
		return arr[n - 1];
	}
	
	/**
	 * Overloaded assignment operator; perform
	 * deep copy.
	 * @param lst The list to copy
	 * @return A reference to this
	 */
	PQueue& operator=(const PQueue& lst)
	{	//Copy lst's values to calling object
		Copy(lst);
		//Return the calling object by reference
		//for chaining (e.g. pq1 = pq2 = pq3; )
		return *this;
	}

	/**
	 * Removes the highest priority element
	 */
	virtual void RemoveMax()
	{	//If the queue is empty; throw an exception
		if(Size() == 0)
			throw EMPTY_Q;
		//The highest priority element is the last element
		//In the array. Shrink the number of elements by 1
		//To exclude it
		--n;
	}
	
	/**
	 * Gets the size of the list
	 * @return The size
	 */
	virtual unsigned int Size() const
	{	//Return the number of elements in the P.Q.
		return n;
	}
	
private:
	//Default capacity
	const static int DEF_CAPC = 10;

	/**
	 * Copies lst
	 * @param lst The list to copy
	 */
	void Copy(const PQueue& lst)
	{
		if(this == &lst)
			return;
		delete [] arr;
		n = lst.n;
		max = lst.max;
		arr = new T[max];
		//Only need to loop over all elements
		for(unsigned int i = 0; i < n; ++i)
			arr[i] = lst.arr[i];
	}

	/**
	 * Resize the list's array
	 * @param The new size of the array
	 */
	void ResizeArr(unsigned int cap)
	{
		max = cap;
		T* tmp = new T[cap];
		//Only need to loop over all elements
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
