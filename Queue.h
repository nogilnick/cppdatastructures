#ifndef QUEUE_H
#define QUEUE_H
#include "ArrayList.h"
template <typename T>
/**
  A template Queue class implemented using the ArrayList
  From project 1. Private inheritance is used because the 
  ArrayList is an implementation detail and is should not
  Be a part of the Queue public interface.
  */
class Queue : private ArrayList<T>
{
public:
	//Used to throw an exception
	const static int EMPTY_QUEUE = -1;

	/**
	 * Add a value to the queue
	 * @param val The value to enqueue
	 */
	void Enqueue(const T& val)
	{ //Add value to end list
	  Add(val);
	}
	
	/**
	 * Remove a value from the queue
	 */
	void Dequeue()
	{ //Remove the value from the list
	  try
	  { //The front of queue is at index 0
	    //If the list is empty an exception BAD_INDX
		//Will be thrown
	    Remove(0);
	  }
	  catch(int e)
	  { //If the list was empty, we have an empty queue
	    //Thrown the appropriate exception
	    if(e == BAD_INDX)
		  throw EMPTY_QUEUE;
	  }
	}
	
	/**
	 * Return the top value from the front of the queue
	 * @return The element at the front of the queue
	 */
	T& Front() const
	{ //check if the queue is empty
	  if(Size() <= 0)
	    throw EMPTY_QUEUE;
	  return Get(0);
	}
	
	/**
	 * Return the size of the queue
	 * @return The size of the queue
	 */
	unsigned int Size() const 
	{ //Use the scope resolution operator to access Size 
	  //From the inherited ArrayList class
	  return ArrayList<T>::Size(); 
	}
};
#endif
