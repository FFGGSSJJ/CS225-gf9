/* B-Tree
 * Author:	Caleb Baker
 * Date:	10/8/17
 * Summary:	A B-Tree data structure.
 *			Most standard operations run in O(lg(n)) time.
 *			Uses O(n) memory.
 *			Where n is the number of items in the tree.
 */




#include <utility>
#include <vector>
#include "3_BPlus_tree.cpp"

#define SEARCH_KEY_NOT_FOUND 's'
#define REMOVE_KEY_NOT_FOUND 'r'



// Add a new strcture blcok, which gather all the BNode with the same secondary key value
template <typename T>
struct Blocks
{
	//int counter;
	//Blocks();
	std::vector< Person_BP > block;
	void print_block();
};

template <typename T>
void Blocks<T>::print_block()
{
	int element = block.size();
	cout << "There are " << element << " people in this block"<<endl;

	while (element > 0)
	{
		cout << block[element-1].people->id_number << "\t";
		cout << block[element-1].people->firstname << "\t";
		cout << block[element-1].people->risk << "\t";
		cout << block[element-1].people->register_date.first << "\t";
		cout << block[element-1].people->register_date.second << "\n";
		element--;	
	}

}

// struct for representing nodes of a b tree
template <typename T>
struct BNode {

	//BNode();
	BNode<T> **child;	// Array of pointers to children.

	// add a new struture to each node
	std::pair<T, Blocks<T>* > *key;				// Array of keys.
	
	unsigned size;		// Number of keys.
	bool leaf;			// Whether the node is a leaf.
};

// template <typename T>
// BNode<T>::BNode()
// {
// 	child = NULL;
// 	key = NULL;
// 	size = 0;
// 	leaf = true;
// }


typedef char BTREE_EXCEPTION;


// class for representing b trees.
template <typename T>
class BTree {
public:
	// Constructor
	// First parameter is the minimum degree of the tree.
	// Second parameter is the tree's key-comparison function.
	// Fourth parameter is a function that prints keys.

	// (added) Third parameter is a function that check if key is the same

	// Constant time.
	BTree(unsigned, bool (*)(T, T), bool (*)(T,T), void (*)(pair<T, Blocks<T> *>) = NULL);

	// Destructor.
	// Linear time.
	~BTree<T>();

	// Inserts a key into the tree.
	// Logorithmic time.
	void insert(T);

	void register2btree(People* person);


	// Removes a key from the tree.
	// Throws a BTREE_EXCEPTION if no item was found to remove.
	// Logorithmic time.
	T remove(T);

	// Function to find a key in the tree.
	// returnValue.first is the node the item is in.
	// returnValue.second is the correct index in that node's key array
	// Logorithmic time.
	std::pair<BNode<T>*, unsigned> search(T);

	// Uses search but just returns the key rather than the whole node.
	// Useful when T is a key value pair and lessThan only looks at the key.
	// Throws a BTREE_EXCEPTION if no item matching the parameter is found
	// Logorithmic time.
	T searchKey(T);

	// Prints the tree.
	// Linear time
	void print();

	Blocks<T>* search_block(int month, int day);

private:

	// Used for initializing nodes.
	void initializeNode(BNode<T>*);

	// Recursive function called by destructor.
	void freeNode(BNode<T>*);

	// Finds the index of a key in a node.
	unsigned findIndex(BNode<T>*, T);

	// Inserts a key into a node.
	unsigned nodeInsert(BNode<T>*, std::pair<T, Blocks<T>* >);

	// Deletes the key at a given index from a node.
	std::pair<T, Blocks<T>* > nodeDelete(BNode<T>*, unsigned);

	// Function for splitting nodes that are too full.
	void splitChild(BNode<T>*, int);

	// Merges two children of a node at a given index into one child.
	char mergeChildren(BNode<T>*, unsigned);

	// Makes sure the child of a node at a specified index has >= minDegree items.
	char fixChildSize(BNode<T>*, unsigned);

	// Recursively prints a subtree.
	void printNode(BNode<T>*, unsigned);

	// Root node.
	BNode<T> *root;

	// Comparison function used for managing element placement.
	bool (*lessThan)(T, T);

	// (added) Comparison function used for managing block.
	bool (*checkequal)(T, T);

	// Function used to print items in the tree.
	void (*printKey)(pair<T, Blocks<T> *>);

	// Minimum degree of the tree.
	unsigned minDegree;
};



