#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
template <typename T>
class BinarySearchTree
{
public:
	const static int ELE_DNE = -123;
	//Default constructor
	BinarySearchTree() 
	{ 
		root = NULL;
		n = 0;
	}

	//Copy constructor
	BinarySearchTree(const BinarySearchTree& bst)
	{
		root = NULL;
		n = 0;
		Traverse(bst.root, &BinarySearchTree<T>::AddNode);
	}

	//Virtual Destructor
	virtual ~BinarySearchTree() 
	{ 
		Destroy();
	}

	/**
	 * Inserts a value to the BST
	 * @param val Is the value to insert
	 */
	T& Find(const T& val) const
	{ 	//Use private member function find
		Node* ret = Find(&root, val);
		if(ret == NULL)
			throw ELE_DNE;
		return ret->val;
	}	

	/**
	 * Inserts a value to the BST
	 * @param val Is the value to insert
	 */
	void Insert(const T& val) 
	{ 	//Find the node (remove const qualifier)
		Node*& node = const_cast<Node*&>(Find(&root, val));
		node = new Node(val);
		++n;
	}

	/**
	 * Overloaded assignment operator (performs a deep copy)
	 * @param The BST to copy
	 * @return A reference to the calling object for chaining
	 */
	BinarySearchTree& operator=(const BinarySearchTree& bst)
	{
		if(this == &bst)
			return *this;
		Destroy();
		Traverse(bst.root, &BinarySearchTree<T>::AddNode);
		return *this;
	}
	
	/**
	 * Removes a value from the BST
	 * @param val Is the value to remove
	 */
	void Remove(const T& val) 
	{ 	//Use private member function Remove
		Remove(root, val);
		--n;
	}
	
	/**
	 * Returns the size of the BST
	 */
	unsigned int Size() const
	{
		return n;
	}

private:
	/**
	 * This class represents a node in the search tree
	 */
	class Node
	{
	public:
		Node() { right = left = NULL; }
		Node(const T& v) { right = left = NULL; val = v; }
		Node* right;
		Node* left;
		T val;
	};
	
	/**
	 * Destroys the tree freeing all dynamic memory.
	 * After calling the (now empty) tree is ready to be used
	 */
	void Destroy()
	{
		Traverse(root, &BinarySearchTree<T>::DestroyNode); 
		root = NULL;
		n = 0;
	}

	/**
	 * Helper function for destroying the BST
	 */
	void DestroyNode(Node* ptr)
	{
		delete ptr;
	}

	/**
	 * Used for copy constructor
	 */
	void AddNode(Node* ptr)
	{
		if(ptr != NULL)
			Insert(ptr->val);
	}

	/**
	 * Deletes the node containing val from the tree 
	 * if it exists. Throws ELE_DNE otherwise
	 * @param ptr is the root of the subtree to search from
	 * @param val is the element to remove
	 */
	void Remove(Node*& ptr, const T& val)
	{	//Find the node; remove const qualifier
		Node*& node = const_cast<Node*&>(Find(&ptr, val));
		//If node is null the value to remove dne
		if(node == NULL)
			throw ELE_DNE;
		//At the node to remove
		Node* tempPtr = NULL;
		//Node has two subtrees
		if(node->left && node->right)
		{	//Find the min value in the right subtree
			tempPtr = FindMinNode(node->right);
			//Swap value and remove recursively
			node->val = tempPtr->val;
			Remove(node->right, node->val);
		}
		//Node only has right subtree
		else if(node->right)
		{
			tempPtr = node;
			node = node->right;
			delete tempPtr;
		}
		//Node only has left subtree
		else if(node->left)
		{
			tempPtr = node;
			node = node->left;
			delete tempPtr;
		}
		//Node is external
		else
		{
			delete node;
			node = NULL;
		}
	}

	/**
	 * Attempts to find a value
	 * in a tree given the root
	 */
	Node* const & Find(Node* const * ptr, const T& val) const
	{	//Found it or it DNE
		while(true)
		{
			Node* cur = *ptr;
			if(!cur || val == cur->val)
				return *ptr;
			else if(val < cur->val)
				ptr = &(cur->left);
			else
				ptr = &(cur->right);
		}
	}

	//Finds the minimum valued node from  a given root
	Node* FindMinNode(Node* ptr)
	{	//Proceed down left subtree
		while(ptr->left)
			ptr = ptr->left;
		return ptr;
	}

	/**
	 * Traverse the tree applying the function
	 * fPtr in post-fix order
	 */
	void Traverse(Node* ptr, void (BinarySearchTree::*fPtr)(Node*))
	{
		if(!ptr)
			return;
		//Traverse the left sub-tree
		Traverse(ptr->left, fPtr);
		//Traverse the right sub-tree
		Traverse(ptr->right, fPtr);
		//Call pointer to member function
		(this->*fPtr)(ptr);
	}

	//Data members
	Node* root;
	unsigned int n;
};
#endif
