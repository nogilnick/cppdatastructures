#ifndef TREEMAP_H
#define TREEMAP_H
#include "BinarySearchTree.h"
/**
 * A class that implements the Map.h interface.
 * This implements the Map ADT using a binary
 * search tree. T1 is the 
 * type of the key T2 is the type of the 
 * value in a (key, value) pair.
 */
template <typename T1, typename T2>
class TreeMap : public Map<T1, T2>
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
	{ 	
		try
		{
			bst.Remove(KeyValue(k));
		}
		catch(int error)
		{	//Check the exception error code
			if(error == bst.ELE_DNE)
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
	T2& Find(const T1& k) const
	{	//Attempt to find the element
		try
		{
			return bst.Find(KeyValue(k)).val;
		}
		catch(int error)
		{	//Check the exception error code
			if(error == bst.ELE_DNE)
				throw this->ELE_DNE;
		}
		throw this->ELE_DNE;
	}

	//Overloaded assignment operator
	TreeMap& operator=(const TreeMap& tm)
	{	//Self-assignment check already handled by BST
		bst = tm.bst;
		return *this;
	}

	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	void Put(const T1& k, const T2& v)
	{	//Add the element to the BST
		bst.Insert(KeyValue(k, v));
	}

	/**
	* Returns the number of elements in the Map
	* @return: Number of elements in map object
	*/
	unsigned int Size() const
	{	//Return the size of the underlying list
		return bst.Size();
	}
	
	//Already handled by BST class
	TreeMap() { }

	//Copy constructor
	TreeMap(const TreeMap& tm) : bst(tm.bst) {}

	//Virtual distructor; Already handled by BST class
	virtual ~TreeMap() { }
	  
private:
	//BST
	BinarySearchTree<KeyValue> bst;
};
#endif
