#ifndef TREEMAP_H
#define TREEMAP_H
#include "AVLTree.h"
/**
 * A class that implements the Map.h interface.
 * This implements the Map ADT using an AVL tree. 
 * T1 is the type of the key T2 is the type of the 
 * value in a (key, value) pair.
 */
template <typename T1, typename T2>
class AVLMap : public Map<T1, T2>
{
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
			avl.Remove(KeyValue(k));
		}
		catch(int error)
		{	//Check the exception error code
			if(error == avl.ELE_DNE)
				throw ELE_DNE;
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
		KeyValue kv(k);
		try
		{
			kv = avl.Find(kv);
		}
		catch(int error)
		{	//Check the exception error code
			if(error == avl.ELE_DNE)
				throw ELE_DNE;
		}
		return kv.val;
	}

	//Overloaded assignment operator
	AVLMap& operator=(const AVLMap& tm)
	{	//Self-assignment check already handled by AVLTree
		avl = tmp.avl;
		return *this;
	}

	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	void Put(const T1& k, const T2& v)
	{	//Add the element to the AVLTree
		avl.Insert(KeyValue(k, v));
	}

	/**
	* Returns the number of elements in the Map
	* @return: Number of elements in map object
	*/
	unsigned int Size() const
	{	//Return the size of the underlying list
		return avl.Size();
	}
	
	//Already handled by AVLTree class
	AVLMap() { }

	//Copy constructor
	AVLMap(const AVLMap& tm) : avl(tm.avl) {}

	//Virtual distructor; Already handled by AVLTree class
	virtual ~AVLMap() { }
	  
private:
	//AVLTree
	AVLTree<KeyValue> avl;
};
#endif