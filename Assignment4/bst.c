/*
 File: bst.c
 Implementation of the binary search tree data structure.
 
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bst.h"
#include "structs.h"

struct Node {
	TYPE         val;
	struct Node *left;
	struct Node *right;
};

struct BSTree {
	struct Node *root;
	int          cnt;
};



/*----------------------------------------------------------------------------*/
/*
 function to create newNode with input Val
 param value to be saved
 pre: input is of correct type
 post: returns new node
 */
struct Node * newNode(TYPE val) {
    struct Node * created = (struct Node *) malloc(sizeof(struct Node));
    assert(created);
    created->val = val;
	created->left = created->right = NULL;
    return created;
}
 
 
 
/*----------------------------------------------------------------------------*/
/*
 function to initialize the binary search tree.
 param tree
 pre: tree is not null
 post:	tree size is 0
		root is null
 */

void initBSTree(struct BSTree *tree)
{
	tree->cnt  = 0;
	tree->root = 0;
}

/*
 function to create a binary search tree.
 param: none
 pre: none
 post: tree->count = 0
		tree->root = 0;
 */

struct BSTree*  newBSTree()
{
	struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
	assert(tree != 0);

	initBSTree(tree);
	return tree;
}

/*----------------------------------------------------------------------------*/
/*
function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
 pre: none
 post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
	if (node != 0) {
		_freeBST(node->left);
		_freeBST(node->right);
		free(node);
	}
}

/*
 function to clear the nodes of a binary search tree
 param: tree    a binary search tree
 pre: tree ! = null
 post: the nodes of the tree are deallocated
		tree->root = 0;
		tree->cnt = 0
 */
void clearBSTree(struct BSTree *tree)
{
    if ( tree->root != 0) {
	_freeBST(tree->root);
	tree->root = 0;
    }
	tree->cnt  = 0;
}

/*
 function to deallocate a dynamically allocated binary search tree
 param: tree   the binary search tree
 pre: tree != null;
 post: all nodes and the tree structure itself are deallocated.
 */
void deleteBSTree(struct BSTree *tree)
{
	if (tree->root != 0) {
		clearBSTree(tree);
	}
        free(tree);
}

/*----------------------------------------------------------------------------*/
/*
 function to determine if  a binary search tree is empty.

 param: tree    the binary search tree
 pre:  tree is not null
 */
int isEmptyBSTree(struct BSTree *tree) { 
    return (tree->cnt == 0); 
}

/*
 function to determine the size of a binary search tree

param: tree    the binary search tree
pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { return tree->cnt; }

/*----------------------------------------------------------------------------*/
/*
 recursive helper function to add a node to the binary search tree.
 HINT: You have to use the compare() function to compare values.
 param:  cur	the current root node
		 val	the value to be added to the binary search tree
 pre:	val is not null
 */
struct Node *_addNode(struct Node *cur, TYPE val)
{   
	if (cur == NULL)                            // Base case
		return newNode(val);
	else if (compare(val, cur->val) <= 0)       // input <= current
		cur->right = _addNode(cur->right, val); // go right
	else                                        // input > current
		cur->left = _addNode(cur->left, val);   // go left
        
    return cur;
}

/*
 function to add a value to the binary search tree
 param: tree   the binary search tree
		val		the value to be added to the tree

 pre:	tree is not null
		val is not null
 pose:  tree size increased by 1
		tree now contains the value, val
 */
void addBSTree(struct BSTree *tree, TYPE val)
{
	tree->root = _addNode(tree->root, val);
	tree->cnt++;
}


/*
 function to determine if the binary search tree contains a particular element
 HINT: You have to use the compare() function to compare values.
 param:	tree	the binary search tree
		val		the value to search for in the tree
 pre:	tree is not null
		val is not null
 post:	none
 */

/*----------------------------------------------------------------------------*/
int containsBSTree(struct BSTree *tree, TYPE val)
{
    // Check input
    assert(tree);
    assert(val);
    
    // Start at root
    struct Node * cur = tree->root;
    
    // If you encounter NULL, item is not present
    while (cur != NULL ) {
		if (compare(val, cur->val) == 0)             //input = current
			return 1;                               // return true
		else if (compare(val, cur->val) < 0)        // input < current
			cur->right = _addNode(cur->right, val); // go right
		else                                        // input > current
			cur->left = _addNode(cur->left, val);   // go left
    }
    
    return 0;                                       // Item not present
        
}

/*
 helper function to find the left most child of a node
 return the value of the left most child of cur
 param: cur		the current node
 pre:	cur is not null
 post: none
 */

/*----------------------------------------------------------------------------*/
TYPE _leftMost(struct Node *cur)
{
    assert(cur);
    
    // Go all the way left
    // function can be recursive, but no real need
    while (cur->left) 
        cur = cur->left;
    
    // Return left most child value
    return cur->val;
}


/*
 recursive helper function to remove the left most child of a node
 HINT: this function returns cur if its left child is NOT NULL. Otherwise,
 it returns the right child of cur and free cur.

Note:  If you do this iteratively, the above hint does not apply.

 param: cur	the current node
 pre:	cur is not null
 post:	the left most node of cur is not in the tree
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{
    // Check input
    assert(cur);
    
    // Pointer to store child when left == NULL
    struct Node * rightChild;
    
    // Recursively find where left child = NULL
    if (cur->left) {           // Base Case
        cur->left = _removeLeftMost(cur->left);
        return cur;
    }
    else {
        rightChild = cur->right;
        free(cur->val);     // Free stored value
        free(cur);          // Free current SAFELY
        cur = NULL;         // Remove access
        return rightChild;
    }
}
/*
 recursive helper function to remove a node from the tree
 HINT: You have to use the compare() function to compare values.
 param:	cur	the current node
		val	the value to be removed from the tree
 pre:	val is in the tree
		cur is not null
		val is not null
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
    assert(cur);
    assert(val);
    
    // Temp node to help free
    struct Node * temp;

	if (compare(val, cur->val) == 0) {          //Base case
		if (!cur->right) {                      // No right child
			temp = cur->left;                   // To update cur
			free(cur->val);                     // Free value stored
			free(cur);                          // Free cur
			cur = NULL;                         // Remove access
			return temp;
		}
		else {                                  // Special removal
			cur->val = _leftMost(cur);
			cur->right = _removeLeftMost(cur);
		}
	}

	else if (compare(val, cur->val) < 0)        // input < current
		cur->right = _addNode(cur->right, val); // go right
	else                                        // input > current
		cur->left = _addNode(cur->left, val);   // go left
        
    // Return to build tree back update
    return cur;

}
/*
 function to remove a value from the binary search tree
 param: tree   the binary search tree
		val		the value to be removed from the tree
 pre:	tree is not null
		val is not null
		val is in the tree
 pose:	tree size is reduced by 1
 */
void removeBSTree(struct BSTree *tree, TYPE val)
{
	if (containsBSTree(tree, val)) {
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	}
}

/*----------------------------------------------------------------------------*/


#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
	 if (cur == 0) return;
	 printf("(");
	 printNode(cur->left);	 
	 /*Call print_type which prints the value of the TYPE*/
	 print_type(cur->val);
	 printNode(cur->right);
	 printf(")");
}

void printTree(struct BSTree *tree) {
	 if (tree == 0) return;	 
	 printNode(tree->root);	 
}
/*----------------------------------------------------------------------------*/

#endif


#if 1

// Test value stuff -----

struct TestValues
{
    struct data* values;
    int n;
};

void initValue(struct data* value, int number, const char* name)
{
    value->number = number;
    value->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(value->name, name);
}

void freeValue(struct data* value)
{
    free(value->name);
}

struct TestValues* createValues()
{
    struct TestValues* values = malloc(sizeof(struct TestValues));
    values->n = 4;
    values->values = malloc(values->n * sizeof(struct data));
    
    initValue(&(values->values[0]), 50, "rooty");
    initValue(&(values->values[1]), 13, "lefty");
    initValue(&(values->values[2]), 110, "righty");
    initValue(&(values->values[3]), 10, "lefty of lefty");
    
    return values;
}

void destroyValues(struct TestValues* values)
{
    for (int i = 0; i < values->n; ++i)
    {
        freeValue(&(values->values[i]));
    }
    free(values->values);
    free(values);
}

// -----

void printTestResult(int predicate, char *nameTestFunction, char *message){
    if (predicate)
        printf("%s(): PASS %s\n",nameTestFunction, message);
    else
        printf("%s(): FAIL %s\n",nameTestFunction, message);        
}

/**
 * Tests adding 4 nodes to the BST.
 */
void testAddNode()
{
    struct TestValues* tv = createValues();
    struct BSTree *tree	= newBSTree();
    
    // Add all values to the tree
    for (int i = 0; i < tv->n; ++i)
    {
        addBSTree(tree, &(tv->values[i]));
        if (tree->cnt != i + 1)
        {
            printf("addNode() test: FAIL to increase count when inserting\n");
            return;
        }
    }
    
    // Check that root node is rooty
    if (tree->root->val != &(tv->values[0]))
    {
        printf("addNode() test: FAIL to insert 50 as root\n");
        return;
    }
    else
    {
        printf("addNode() test: PASS when adding 50 as root\n");
    }
    
    if (tree->root->left->val != &(tv->values[1]))
    {
        printf("addNode() test: FAIL to insert 13 as left child of root\n");
        return;
    }
    else
    {
        printf("addNode() test: PASS when adding 13 as left of root\n");
    }
    
    if (tree->root->right->val != &(tv->values[2]))
    {
        printf("addNode() test: FAIL to insert 110 as right child of root\n");
        return;
    }
    else
    {
        printf("addNode() test: PASS when adding 110 as right of root\n");
    }
    
    if (tree->root->left->left->val != &(tv->values[3]))
    {
        printf("addNode() test: FAIL to insert 10 as left child of left of root\n");
        return;
    }
    else
    {
        printf("addNode() test: PASS when adding 10 as left of left of root\n");
    }
    
    deleteBSTree(tree);
    destroyValues(tv);
}

/**
 * Tests that the BST contains the added elements,
 * and that it does not contain an element that was not added.
 */
void testContainsBSTree()
{
    struct TestValues* tv = createValues();
    struct BSTree *tree	= newBSTree();
    
    // Create value not added to the tree
    struct data notInTree;
    notInTree.number = 111;
    notInTree.name = "not in tree";
    
    // Add all other values to the tree
    for (int i = 0; i < tv->n; ++i)
    {
        addBSTree(tree, &(tv->values[i]));
    }
    
    printTestResult(containsBSTree(tree, &(tv->values[0])), "containsBSTree", "when test containing 50 as root");
    printTestResult(containsBSTree(tree, &(tv->values[1])), "containsBSTree", "when test containing 13 as left of root");
    printTestResult(containsBSTree(tree, &(tv->values[2])), "containsBSTree", "when test containing 110 as right of root");
    printTestResult(containsBSTree(tree, &(tv->values[3])), "containsBSTree", "when test containing 10 as left of left of root");
    
    printTestResult(!containsBSTree(tree, &notInTree), "containsBSTree", "when test containing 111, which is not in the tree");
    
    deleteBSTree(tree);
    destroyValues(tv);
}

/**
 * Tests leftMost.
 */
void testLeftMost()
{
    struct TestValues* tv = createValues();
    struct BSTree *tree	= newBSTree();

    for (int i = 0; i < tv->n; ++i)
    {
        addBSTree(tree, &(tv->values[i]));
    }
    
    printTestResult(_leftMost(tree->root) == &(tv->values[3]), "_leftMost", "left most of root");
    printTestResult(_leftMost(tree->root->left) == &(tv->values[3]), "_leftMost", "left most of left of root");
    printTestResult(_leftMost(tree->root->left->left) == &(tv->values[3]), "_leftMost", "left most of left of left of root");
    printTestResult(_leftMost(tree->root->right) == &(tv->values[2]), "_leftMost", "left most of right of root");
    
    deleteBSTree(tree);
    destroyValues(tv);
}

/**
 * Tests left-most removal of 3 nodes.
 */
void testRemoveLeftMost()
{
    struct TestValues* tv = createValues();
    struct BSTree *tree	= newBSTree();

    for (int i = 0; i < tv->n; ++i)
    {
        addBSTree(tree, &(tv->values[i]));
    }
    
    struct Node* oldRoot = tree->root;
    tree->root = _removeLeftMost(tree->root);
    --(tree->cnt);
    printTestResult(tree->root == oldRoot, "_removeLeftMost", "removing leftmost of root 1st try");
    
    tree->root->right = _removeLeftMost(tree->root->right);
    --(tree->cnt);
    printTestResult(tree->root->right == NULL, "_removeLeftMost", "removing leftmost of right of root 1st try");
    
    oldRoot = tree->root;
    tree->root = _removeLeftMost(tree->root);
    --(tree->cnt);
    printTestResult(tree->root == oldRoot, "_removeLeftMost", "removing leftmost of root 2st try");
    
    deleteBSTree(tree);
    destroyValues(tv);
}

/**
 * Tests removal of all nodes.
 */
void testRemoveNode()
{
    struct TestValues* tv = createValues();
    struct BSTree *tree	= newBSTree();

    for (int i = 0; i < tv->n; ++i)
    {
        addBSTree(tree, &(tv->values[i]));
    }
    
    tree->root = _removeNode(tree->root, &(tv->values[3]));
    --(tree->cnt);
    printTestResult(tree->root->val == &(tv->values[0]) && tree->root->left->left == NULL, "_removeNode", "remove left of left of root 1st try");
	        
    tree->root = _removeNode(tree->root, &(tv->values[2]));
    --(tree->cnt);
    printTestResult(tree->root->val == &(tv->values[0]) && tree->root->right == NULL, "_removeNode", "remove right of root 2st try");
	   
    tree->root = _removeNode(tree->root, &(tv->values[1]));
    --(tree->cnt);
    printTestResult(tree->root->val == &(tv->values[0]) && tree->root->left == 0, "_removeNode", "remove right of root 3st try");
        
    tree->root = _removeNode(tree->root, &(tv->values[0]));
    --(tree->cnt);
    printTestResult(tree->root == NULL, "_removeNode", "remove right of root 4st try");
    
    deleteBSTree(tree);
    destroyValues(tv);
}

/*

Main function for testing different fucntions of the Assignment#4.

*/

int main(int argc, char *argv[]){	

   //After implementing your code, please uncommnet the following calls to the test functions and test your code 

  	testAddNode();
	
	printf("\n");
  	//testContainsBSTree();
	
	printf("\n");
       //testLeftMost();
	
	printf("\n");
    //testRemoveLeftMost();
	
	printf("\n");
    //testRemoveNode();
    
	
	return 0;


}

#endif
