#ifndef LIST_H
#define LIST_H
typedef unsigned int Index;
template <typename T>
class List
{
public:
	//Indicates an incorrect index
	const static int BAD_INDX = -1;

	/**
	 * Adds an element to the end of the list
	 * @param ele Is the element to add
	 */
	virtual void Add(const T& ele) = 0;

	/**
	 * Clears the list
	 */
	virtual void Clear() = 0;
	
	/**
	 * Gets the i-th element of the list
	 * @param i The index
	 * @return The element at index i; an exception
	 * is thrown if it does not exist
	 */	 
	virtual T& Get(Index i) const = 0;
	
	/**
	 * Virtual destructor
	 */
	virtual ~List() {}

	/**
	 * Removes an element from the list
	 * @param i The index of the element to remove
	 */
	virtual void Remove(Index i) = 0;
	
	/**
	 * Sets the i-th element
	 * @param i The index
	 * @param val The element to set
	 */
	virtual void Set(Index i, const T& val) = 0;
	
	/**
	 * Gets the size of the list
	 * @return The size
	 */
	virtual unsigned int Size() const = 0;
};
#endif
