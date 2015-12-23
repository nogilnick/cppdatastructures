#ifndef AVLTREE_H
#define AVLTREE_H
template <typename T>
class AVLTree
{
public:
	const static int ELE_DNE = -123;

	//Default constructor
	AVLTree() 
	{ 
		root = nullptr;
		n = 0;
	}

	//Copy constructor
	AVLTree(const AVLTree& bst)
	{
		root = nullptr;
		n = 0;
		Traverse(bst.root, &AVLTree<T>::AddNode);
	}

	//Virtual Destructor
	virtual ~AVLTree() 
	{ 
		Destroy();
	}

	/**
	 * Destroys the tree freeing all dynamic memory.
	 * After calling the (now empty) tree is ready to be used
	 */
	void Destroy()
	{
		Traverse(root, &AVLTree<T>::DestroyNode); 
		root = nullptr;
		n = 0;
	}

	/**
	 * Finds a value in the AVL tree
	 * @param val Is the value to find
	 */
	T& Find(const T& val) const
	{ 	//Use private member function find
		Node* ret = *(Find(&root, val).c);
		if(ret == nullptr)
			throw ELE_DNE;
		return ret->val;
	}	

	/**
	 * Inserts a value to the AVL tree
	 * @param val Is the value to insert
	 */
	void Insert(const T& val) 
	{ 	//Find the node (remove const qualifier)
		Link l = Find(&root, val);
		Node** node = const_cast<Node**>(l.c);
		(*node) = new Node(val, l.p == nullptr ? nullptr : *(l.p));
		++n;
		Balance(*node);
	}

	/**
	 * Overloaded assignment operator (performs a deep copy)
	 * @param The AVL tree to copy
	 * @return A reference to the calling object for chaining
	 */
	AVLTree& operator=(const AVLTree& bst)
	{
		if(this == &bst)
			return *this;
		Destroy();
		Traverse(bst.root, &AVLTree<T>::AddNode);
		return *this;
	}
	
	/**
	 * Removes a value from the AVL tree
	 * @param val Is the value to remove
	 */
	void Remove(const T& val) 
	{ 	//Use private member function Remove
		Remove(root, val);
		--n;
	}
	
	/**
	 * Returns the size of the AVL tree
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
		Node() { left = right = up = nullptr; hs = 0; }
		Node(const T& v, Node* u = nullptr) { left = right = nullptr; val = v; up = u; hs = 0;}
		Node* left;
		Node* right;
		Node* up;
		//The height score
		int hs;
		T val;
	};

	//This class is used to identify the parent and child
	//When inserting or deleting a node
	class Link
	{
	public:
		Link(Node* const * prev, Node* const * cur) { p = prev; c = cur; }
		Node* const * p;
		Node* const * c;
	};

	/**
	 * Used for copy constructor
	 */
	void AddNode(Node* ptr)
	{
		if(ptr != nullptr)
			Insert(ptr->val);
	}

	/**
	 * This function performs the balance
	 * routing for an AVL tree starting at
	 * node n and traveling up the tree to
	 * the root
	 * @param n Is the node to start at
	 */
	void Balance(Node* n)
	{
		while(n != nullptr)
		{	//Loop until the root is reached
			n->hs = HeightScore(n);
			//Imbalance to left
			if(n->hs == 2)
			{	//Left-right
				if(n->left->hs == -1)
					RotLR(GetParentPtr(n));
				//Left-left
				n = RotLL(GetParentPtr(n));
			}
			//Imbalance to right
			else if(n->hs == -2)
			{	//Right-left
				if(n->right->hs == 1)
					RotRL(GetParentPtr(n));
				//Right-right
				n = RotRR(GetParentPtr(n));
			} //Loop done; one level up
			n = n->up;
		}
	}

	/**
	 * Helper function for destroying the BST
	 */
	void DestroyNode(Node* ptr)
	{
		delete ptr;
	}

	/**
	 * Attempts to find a value
	 * in a tree given the root
	 */
	Link Find(Node* const * ptr, const T& val) const
	{	//Found it or it DNE
		Node* const * past = nullptr;
		while(true)
		{
			if(!(*ptr) || val == (*ptr)->val)
				return Link(past, ptr);
			past = ptr;
			if(val < (*ptr)->val)
				ptr = &((*ptr)->left);
			else
				ptr = &((*ptr)->right);
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
	 * Gets a pointer to
	 * the parent node's pointer to
	 * node n
	 */
	Node** GetParentPtr(Node* n)
	{	//The only node with null "up" is root node
		if(n->up == nullptr)
			return &root;
		if(n->up->left == n)
			return &n->up->left;
		return &n->up->right;
	}

	//Returns the height of the subtree rooted
	//At node n
	int Height(Node* n)
	{
		if(n == nullptr)
			return -1;
		return 1 + max(Height(n->left), Height(n->right));
	}

	//Compute the height score of a node
	//for an AVL tree: height(left) - height(right)
	int HeightScore(Node* n)
	{
		if(n == nullptr)
			return 0;
		return Height(n->left) - Height(n->right);
	}

	/**
	 * Deletes the node containing val from the tree 
	 * if it exists. Throws ELE_DNE otherwise
	 * @param ptr is the root of the subtree to search from
	 * @param val is the element to remove
	 */
	void Remove(Node*& ptr, const T& val)
	{	//Find the node; remove const qualifier
		Node** node = const_cast<Node**>(Find(&ptr, val).c);
		//If node is null the value to remove dne
		if(node == nullptr)
			throw ELE_DNE;
		//At the node to remove
		Node* tempPtr = nullptr;
		//Node has two subtrees
		if((*node)->left && (*node)->right)
		{	//Find the min value in the right subtree
			tempPtr = FindMinNode((*node)->right);
			//Swap value and remove recursively
			(*node)->val = tempPtr->val;
			Remove((*node)->right, (*node)->val);
		}
		//Node only has right subtree
		else if((*node)->right)
		{
			tempPtr = (*node);
			(*node)->right->up = (*node)->up;
			(*node) = (*node)->right;
			delete tempPtr;
			Balance((*node)->up);
		}
		//Node only has left subtree
		else if((*node)->left)
		{
			tempPtr = (*node);
			(*node)->left->up = (*node)->up;
			(*node) = (*node)->left;
			delete tempPtr;
			Balance((*node)->up);
		}
		//Node is external
		else
		{
			tempPtr = (*node)->up;
			delete (*node);
			(*node) = nullptr;
			Balance(tempPtr);
		}
	}

	//AVL Left-Right rotation
	void RotLR(Node** n)
	{
		Node *five = (*n);
		Node *three = five->left;
		Node *four = three->right;
		Node* B = four->left;
		five->left = four;
		four->up = five;
		four->left = three;
		three->up = four;
		three->right = B;
		if(B)
			B->up = three;
	}

	//AVL Right-Left rotation
	void RotRL(Node** n)
	{
		Node *three = (*n);
		Node *five = three->right;
		Node *four = five->left;
		Node* C = four->right;
		three->right = four;
		four->up = three;
		four->right = five;
		five->up = four;
		five->left = C;
		if(C)
			C->up = five;
	}

	//AVL Left-Left rotation
	Node* RotLL(Node** n)
	{
		Node *five = (*n);
		Node *four = five->left;
		Node *three = four->left;
		Node* C = four->right;
		(*n) = four;
		four->up = five->up;
		four->right = five;
		five->up = four;
		five->left = C;
		if(C)
			C->up = five;
		//Fix balance factors
		three->hs = HeightScore(three);
		five->hs = HeightScore(five);
		four->hs = HeightScore(four);
		return four;
	}

	//AVL Right-right rotation
	Node* RotRR(Node** n)
	{
		Node *three = (*n);
		Node *four = three->right;
		Node *five = four->right;
		Node* B = four->left;
		(*n) = four;
		four->up = three->up;
		four->left = three;
		three->up = four;
		three->right = B;
		if(B)
			B->up = three;
		//Fix balance factors
		three->hs = HeightScore(three);
		five->hs = HeightScore(five);
		four->hs = HeightScore(four);
		return four;
	}

	/**
	 * Traverse the subtree rooted at ptr 
	 * applying the member function fPtr 
	 * in post-fix order
	 * @param ptr Is the root of the subtree to traverse
	 * @param fPtr Is a pointer to an AVLTree member function
	 * That takes one argument of type Node*
	 */
	void Traverse(Node* ptr, void (AVLTree::*fPtr)(Node*))
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
