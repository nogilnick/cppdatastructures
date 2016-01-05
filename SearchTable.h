#ifndef SEARCHTABLE_H
#define SEARCHTABLE_H
#include "QSort.h"
/**
 * A class that implements the Map.h interface.
 * This implements the Map ADT using a search table
 * T1 is the type of the key T2 is the type of the 
 * value in a (key, value) pair.
 */
template <typename T1, typename T2>
class SearchTable : public Map<T1, T2>
{	//Typedef to access Map's KeyValue pair
	//Necessary only in g++
	typedef typename Map<T1, T2>::KeyValue KeyValue;
public:	 
	/**
	* Attempts to erase the (key, value) pair
	* with key  = k. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key of the pair to erase
	*/
	void Erase(const T1& k)
	{ 	//Attempt to find the element
		int i;
		if(!BinarySearch(k, i))
			throw this->ELE_DNE;
		//Overwrite element
		for(unsigned int j = i + 1; j < n; ++j)
			arr[j - 1] = arr[j];
		--n;
	}
	 
	/**
	* Attempts to find the corresponding value
	* for a given key. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key to search for
	* @return The value corresponding to k
	*/
	T2& Find(const T1& k) const
	{	//Attempt to find the element
		int i;
		if(!BinarySearch(k, i))
			throw this->ELE_DNE;
		return arr[i].val;
	}

	//Overloaded assignment operator
	SearchTable& operator=(const SearchTable& st)
	{	//Self-assignment check handled by copy
		Copy(st);
		return *this;
	}
	
	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	void Put(const T1& k, const T2& v)
	{	//Check if resize is necessary
		if(n >= max) //If so, double the capacity
			ResizeArr(max * 2);
		//Next, find where ele belongs in the array
		int i;
		if(BinarySearch(k, i))
			throw this->DUP_ELE;
		//Shift elements to the right to make room
		for(int j = (int) n; j > i; --j)
			arr[j] = arr[j - 1];
		//Insert item at i
		arr[i] = KeyValue(k, v);
		++n;
	}

	//Default constructor
	SearchTable()
	{
		max = DEF_CAPC;
		arr = new KeyValue[DEF_CAPC];
		n = 0;
	}

	//Copy constructor 
	SearchTable(const SearchTable& st)
	{
		arr = NULL;
		Copy(st);
	}

	//Convenience constructor
	SearchTable(const T1* keys, const T2* vals, unsigned int numEle)
	{
		n = numEle;
		max = (numEle * 3) / 2;
		arr = new KeyValue[max];
		for(unsigned int i = 0; i < numEle; ++i)
			arr[i] = KeyValue(keys[i], vals[i]);
		Sort();
	}

	//Virtual destructor
	virtual ~SearchTable()
	{
		delete [] arr;
	}

   /**
	* Returns the number of elements in the Map
	* @return: Number of elements in map object
	*/
	unsigned int Size() const
	{
		return n;
	}
	
private:
	//Default capacity
	const static int DEF_CAPC = 10;;
	
	void Copy(const SearchTable& st)
	{
		if(this == &st)
			return;
		n = st.n;
		max = st.max;
		delete [] arr;
		arr = new KeyValue[max];
		for(unsigned int i = 0; i < max; ++i)
			arr[i] = st.arr[i];
	}

	/**
	 * Performs a binary search on the sorted array
	 * @param k The key to search for
	 * @param m Output variable of the location of the element
	 * (if it exists) or the location it should be (if it does not)
	 * @return True if the element is found false otherwise
	 */
	bool BinarySearch(const T1& k, int& m) const
	{
		int s = 0;
		int e = n - 1;
		while(true)
		{	//Compute the midpoint of the array
			m = s + (e - s) / 2;
			if(s > e)
				break;
			//Test the value at the point
			if(arr[m].key == k)	//found it
				return true;
			else if(arr[m].key > k)
				e = m - 1;
			else
				s = m + 1;
		}
		return false;
	}
	
	/**
	 * Resize the list's array
	 * @param The new size of the array
	 */
	void ResizeArr(unsigned int cap)
	{
		max = cap;
		KeyValue* tmp = new KeyValue[cap];
		for(unsigned int i = 0; i < n; ++i)
			tmp[i] = arr[i];
		delete [] arr;
		arr = tmp;
	}


	//Sorts the underlying array
	void Sort()
	{
		QuickSort(arr, 0, n - 1);
	}

	//Number of elements in the SearchTable
	unsigned int n;
	//Capacity of arr
	unsigned int max;
	//The underlying array
	KeyValue* arr;
};
#endif
