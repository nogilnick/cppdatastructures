#ifndef HASHMAP_H
#define HASHMAP_H
#include <cstdlib>
typedef unsigned int Index;

/**
 * A map implementation that uses a  hash table
 * with a multiplicative hash function internally. 
 */
template <typename T1, typename T2>
class HashMap : public Map<T1, T2>
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
	virtual void Erase(const T1& k)
	{
		Index i = F(k);
		Index j = i;
		while(true)
		{	//Loop until key is found
			if(arr[j].open) //Opening found; key d.n.e.
				throw this->ELE_DNE;
			else if(arr[j].key == k)
			{//Found it
				arr[j].open = true;
				Rehash(max);
				return;
			}
			j = (j + 1) % max;
			if(j == i)	//Check to see if all values searched
				throw this->ELE_DNE;
		}
	}

	/**
	* Attempts to find the corresponding value
	* for a given key. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key to search for
	* @return The value corresponding to k
	*/
	virtual T2& Find(const T1& k) const
	{	
		Index i = F(k);
		Index j = i;
		while(true)
		{	//Loop until open spot is found
			if(arr[j].open) //Opening found; key d.n.e.
				throw this->ELE_DNE;
			else if(arr[j].key == k)	//Found it
				return arr[j].val;
			j = (j + 1) % max;
			if(j == i)	//Check to see if all values searched
				throw this->ELE_DNE;
		}
	}
	
	/**
	* Create a map with a default initial
	* capacity
	*/
	HashMap()
	{
		max = DEF_CAPC;
		n = 0;
		arr = new KeyValue[max];
		//Assign random values for a and b
		a = (unsigned int) rand();
		b = (unsigned int) rand();
	}
	
	/**
	* Create a map with a initial capacity
	* @param capc The initial capacity
	*/
	HashMap(unsigned int capc)
	{
		max = capc;
		n = 0;
		arr = new KeyValue[max];
		//Assign random values for a and b
		a = (unsigned int) rand();
		b = (unsigned int) rand();
	}
	
	//Copy constructor
	HashMap(const HashMap& hm)
	{
		arr = NULL;
		Copy(hm);
	}

	//Desctructor 
	virtual ~HashMap() { delete [] arr; }
	
	//Overloaded assignment operator
	HashMap& operator=(const HashMap& hm)
	{
		Copy(hm);
		return *this;
	}

	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	virtual void Put(const T1& k, const T2& v)
	{	//Double size to prevent degraded performance
		if(n == max / 2)
			Rehash(max * 2);
		Index i = F(k);
		//Loop until a spot is found
		while(true)
		{	//Loop until open spot is found
			if(arr[i].open) //Opening found; Put element
			{	
				arr[i] = KeyValue(k, v);
				++n;
				break;
			}
			i = (i + 1) % max;
		}
	}
	
	/**
	 * Returns the number of elements in the Map
	 * @return: Number of elements in map object
	 */
	virtual unsigned int Size() const
	{
		return n;
	}
	
private:
	//Default capacity of the underlying array
	const static int DEF_CAPC = 10;

	/**
	 * Copies a HashMap
	 */
	void Copy(const HashMap& hm)
	{
		if(this == &hm)
			return;
		a = hm.a;
		b = hm.b;
		max = hm.max;
		n = hm.n;
		delete [] arr;
		arr = new KeyValue[max];
		for(unsigned int i = 0; i < max; ++i)
			arr[i] = hm.arr[i];
	}
	
	/**
	* Resize the map's array
	* @param The new size of the array
	*/
	void Rehash(unsigned int cap)
	{	//Create a new hash function
		a = (unsigned int) rand();
		b = (unsigned int) rand();
		//Create new array
		int oldMax = max;
		max = cap;
		KeyValue* tmp = arr;
		arr = new KeyValue[cap];
		//Reset size
		n = 0;
		//Recreate hash table
		for(int i = 0; i < oldMax; ++i)
		{
			if(!tmp[i].open)
				Put(tmp[i].key, tmp[i].val);
		}
		//Delete the old array
		delete [] tmp;
	}

	/**
	* The hash function
	* @param The element to be hashed
	* @return The resulting hash index
	*/
	Index F(const T1& ele) const
	{
		return (a * ele + b) % max;
	}
	//The hash table
	KeyValue* arr;
	//Number of elements, capcity, and hash function values
	unsigned int n, max, a, b;
};
#endif
