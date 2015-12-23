#ifndef MAP_H
#define MAP_H
/**
 * A abstract class defining the interface
 * for the Map class. Two template parameters
 * are used. T1 is the type of the key
 * T2 is the type of the value in a 
 * (key, value) pair.
 * Note: Map contains pure virtual functions
 * and therefore is abstract and cannot be
 * instantiated. Use the subclass ListMap
 * HashMap, TreeMap, or SearchTable instead.
 */
template <typename T1, typename T2>
class Map
{
public:
	//Defines an error code used for throwing
	//integer exceptions
	//Element does not exist when it should
	const static int ELE_DNE = -2468;
	//Element exists already
	const static int DUP_ELE = -1234;

	/**
	* Attempts to erase the (key, value) pair
	* with key  = k. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key of the pair to erase
	*/
	virtual void Erase(const T1& k) = 0;
	 
	/**
	* Attempts to find the corresponding value
	* for a given key. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key to search for
	* @return The value corresponding to k
	*/
	virtual T2& Find(const T1& k) const = 0;
	
	/**
	* Returns the number of elements in the Map
	* @return: Number of elements in map object
	*/
	virtual unsigned int Size() const = 0;
	
	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	virtual void Put(const T1& k, const T2& v) = 0;

protected:
	/**
	 * Protected class for specifying the (key, value)
	 * pair. The template <typename T1, T2> is not needed
	 * here as it is implied from the top level template
	 * declaration on ListMap itself. The implied template
	 * parameters are T1 and T2.
	 */
	class KeyValue
	{	//Make the data members public for easy access
	public:
		//Mark the entry as being open
		KeyValue() { open = true; }
		//convenience constructor
		KeyValue(const T1& aKey) { key = aKey; }
		//convenience constructor
		KeyValue(const T1& aKey, const T2& aVal, bool ov = false)
		{
			key = aKey;
			val = aVal;
			open = ov;
		}
		T1 key;
		T2 val;
		bool open;
		//Define comparison operators for KeyValue type
		bool operator<(const KeyValue& rhs) const { return key < rhs.key; }
		bool operator==(const KeyValue& rhs) const { return key == rhs.key; }
		bool operator>(const KeyValue& rhs) const { return key > rhs.key; }
		bool operator>=(const KeyValue& rhs) const { return key >= rhs.key; }
		bool operator<=(const KeyValue& rhs) const { return key <= rhs.key; }
		bool operator!=(const KeyValue& rhs) const { return key != rhs.key; }
	};
	
};
#endif