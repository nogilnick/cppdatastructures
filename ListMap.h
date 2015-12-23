#ifndef LISTMAP_H
#define LISTMAP_H
#include "ArrayList.h"
/**
 * A class that implements the Map.h interface.
 * This implements the Map ADT using an ArrayList
 * Two template parameters are used. T1 is the 
 * type of the key T2 is the type of the 
 * value in a (key, value) pair.
 */
template <typename T1, typename T2>
class ListMap : public Map<T1, T2>
{
public:
	/**
	* Attempts to erase the (key, value) pair
	* with key  = k. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key of the pair to erase
	*/
	void Erase(const T1& k)
	{	//Search the list for the key
		for(unsigned int i = 0; i < al.Size(); ++i)
		{
			if(al.Get(i).key == k)
			{	//Delete the (key, value) pair
				al.Remove(i);
				//Return so we don't throw an exception
				return;
			}
		}
		//Key was not found; throw an exception
		throw ELE_DNE;
	}
	 
	/**
	* Attempts to find the corresponding value
	* for a given key. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key to search for
	* @return The value corresponding to k
	*/
	T2& Find(const T1& k) const
	{	//Search the list for the key
		for(unsigned int i = 0; i < al.Size(); ++i)
		{
			if(al.Get(i).key == k)
				return al.Get(i).value;
		}
		//Key was not found; throw an exception
		throw ELE_DNE;
	}

	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	void Put(const T1& k, const T2& v)
	{	//Template type for KeyValue is implied
		KeyValue tmp;
		tmp.key = k;
		tmp.value = v;
		//Add the element to the list
		al.Add(tmp);
	}

	/**
	* Returns the number of elements in the Map
	* @return: Number of elements in map object
	*/
	unsigned int Size() const
	{	//Return the size of the underlying list
		return al.Size();
	}
private:
	/**
	 * Private class for specifying the (key, value)
	 * pair. The template <typename T1, T2> is not needed
	 * here as it is implied from the top level template
	 * declaration on ListMap itself. The implied template
	 * parameters are T1 and T2.
	 */
	class KeyValue
	{	//Make the data members public for easy access
	public:
		T1 key;
		T2 value;
	};
	//Create a list of (key, value) pairs
	//Notice that the template parameter is implied on KeyValue 
	//And does not need to be explicitly stated
	//This is a "has-a" relationship
	ArrayList<KeyValue> al;
};
#endif