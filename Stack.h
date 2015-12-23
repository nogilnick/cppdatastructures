#ifndef STACK_H
#define STACK_H
#include "ArrayList.h"
/**
  A template Stack class implemented using the ArrayList
  From project 1. Private inheritance is used because the 
  ArrayList is an implementation detail and is should not
  Be a part of the Stack public interface.
  */
template <typename T>
class Stack : private ArrayList<T>
{
public:
	//Used to throw an exception
	const static int EMPTY_STACK = -1;

	/**
	 * Push a value onto the stack
	 * @param val The value to push
	 */
	void Push(const T& val)
	{ //Add value to list
	  Add(val);
	}
	
	/**
	 * Pop a value from the stack if possible
	 */
	void Pop()
	{ //Remove the top of stack
	  try
	  { //If the list is empty; an exception will be thrown
		//Note BAD_INDX will be thrown here exactly when 
		//Size() == 0. Thus the index will be 0 - 1 = 2^32-1
		//due to unsigned underflow. This corresponds to empty stack
	    Remove(Size() - 1);
	  }
	  catch(int e)
	  { //Catch the exception and throw a more meaningful exception
	    if(e == BAD_INDX)
		  throw EMPTY_STACK; //The stack is empty
	  }
	}
	
	/**
	 * Return the top value from the stack
	 * @return The top value from the stack
	 */
	T& Top() const
	{ //Check if the stack is empty
	  //This is an alternative approach to check for empty stack
	  //This approach is probably most clear
	  if(Size() <= 0)
	    throw EMPTY_STACK;
	  return Get(Size() - 1);
	}
	
	/**
	 * Return the size of the stack
	 * @return The size of the stack
	 */
	unsigned int Size() const 
	{ //Use the scope resolution operator to access Size 
	  //From the inherited ArrayList class
	  return ArrayList<T>::Size(); 
	}
};
#endif