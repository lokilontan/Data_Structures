//============================================================================
// Name        : Lab17_AVLTrees.cpp
// Author      : Vladimir Plagov
// Version     : 1.0
// Copyright   :
// Description : AVL Trees
//============================================================================

#include <iostream>
#include <fstream>


using namespace std;

//struct for a queue
struct node{
	int data;
	node *next;
};

struct BinaryTree {
	int key;
	int height = 0;
	BinaryTree *left = NULL;
	BinaryTree *right = NULL;
};



//function prororypes
void readFile(struct BinaryTree *&leaf);
BinaryTree* insert(BinaryTree*& leaf, int key);
BinaryTree * rebalance(BinaryTree *&leaf);
int getBalance(BinaryTree *leaf);
BinaryTree *rotateLeft(BinaryTree *&x);
BinaryTree *rotateRight(BinaryTree *&x);
void breadth(struct BinaryTree *leaf, fstream &out);
void enqueue(node *&front, node *&rear, int value);
int dequeue(node *&front, node *&rear);
BinaryTree * search(BinaryTree *leaf, int value);
int height(BinaryTree *leaf);

fstream in("input.txt");
fstream out("output.txt");

int main() {


	if (!in) {
		cout << "Cannot open the input.txt file!";
		return 1;
	}

	if (!out) {
		cout << "Cannot open the output.txt file!";
		return 1;
	}


	BinaryTree *leaf = NULL;

	readFile(leaf);




	breadth(leaf, out);




	in.close();
	out.close();
}

void readFile(struct BinaryTree *&leaf){
	int input;
	while (in.good()){
		in >> input;
		insert(leaf, input);
	}
}

//non-tail recursive algorithm because of rebalance
BinaryTree* insert(BinaryTree*& leaf, int key)
{
    //recursive Code for inserting a node
    //When insert happens set height to 0 for the node
    if (leaf == NULL){
        leaf = new BinaryTree;
        leaf -> key = key;
    	return leaf;
    }
    if (key < leaf->key)
        leaf->left  = insert(leaf->left, key);
    else
        leaf->right = insert(leaf->right, key);
    leaf=rebalance(leaf);  //update heights and rebalance
    return leaf;
}

//This is not a recursive algorithm
BinaryTree * rebalance(BinaryTree *&leaf){
    leaf->height = max(height(leaf->left), height(leaf->right)) + 1;
    int balance = getBalance(leaf);  //node->left - node->right

    //do rotations as necessary
    //If Left heavy outside :  return rightRotate(node);
    if ((balance == 2) && (getBalance(leaf->left) > 0)) {
    	rotateRight(leaf);
    }
    //If right heavy outside:  return leftRotate(node);
    if ((balance == -2) && (getBalance(leaf->right) < 0)) {
        rotateLeft(leaf);
    }
    //If left heavy inside:  left rotation first, right rotation 2nd, return top node
    if ((balance == 2) && (getBalance(leaf->left) < 0)) {
    	leaf->left =  rotateLeft(leaf->left);
    	rotateRight(leaf);
    }
    //if right heavy inside: right rotation first, left rotation 2nd, return top node
    if ((balance == -2) && (getBalance(leaf->right) > 0)) {
		leaf->right = rotateRight(leaf->right);
        rotateLeft(leaf);
    }
    return leaf;
}

int getBalance(BinaryTree *leaf){
	return (height(leaf->left) - height(leaf->right));
}

int height(BinaryTree *leaf) {

	if (leaf == NULL) {
		return -1;
	}
	else {
		return leaf->height;
	}

}

BinaryTree *rotateLeft(BinaryTree *&x){
   struct BinaryTree *y = x->right;
   //add more code to rotate to the left, update heights for x and y
   struct BinaryTree *z = y->left;
   y->left = x;
   x->right = z;
   x->height = max(height(x->left), height(x->right))+1;
   y->height = max(height(y->left), height(y->right))+1;
   return y;
}

BinaryTree *rotateRight(BinaryTree *&x){
   struct BinaryTree *y = x->left;
   //add more code to rotate to the right, update heights for x and y
   struct BinaryTree *z = y->right;
   x->left = z;
   y->right = x;
   x->height = max(height(x->left), height(x->right))+1;
   y->height = max(height(y->left), height(y->right))+1;
   return y;
}

void breadth(struct BinaryTree *leaf, fstream &out) {
	//for the QUEUE currentLevel
	node *clf = NULL;
	node *clr = NULL;
	//for the QUEUE nextLevel
	node *nlf = NULL;
	node *nlr = NULL;

	BinaryTree *current = NULL;

	enqueue(clf, clr, leaf->key);
	while (clf != NULL) {

		current = search(leaf, clf->data);
		out << clf->data << "(" << max(height(current->left), height(current->right))+1 << "," << getBalance(current)<<")";
		dequeue(clf, clr);
		if (current -> left != NULL)
			enqueue(nlf, nlr, current->left->key);
		if (current -> right != NULL)
			enqueue(nlf, nlr, current->right->key);

		if (clf == NULL) {

			clf = nlf;
			clr = nlr;

			nlf = NULL;
			nlr = NULL;

			out << endl;
		}
	}
}

//adds to the back - QUEUE
void enqueue(node *&front, node *&rear, int value){

	node *nn = new node;
	nn -> data = value;
	nn -> next = NULL;

	if (front == NULL) {
		front = nn;
		rear = nn;
	}
	else {
		rear -> next = nn;
		rear = nn;
	}

}

//removes from the front - QUEUE
int dequeue(node *&front, node *&rear){

	int tempVal = -404;
	if (front != NULL) {
		node *temp = front;
		tempVal = front -> data;
		front = front -> next;
		delete temp;
		if (front == NULL) {
			rear = NULL;
		}
	}
	return tempVal;
}

/*
 * Non-recursive search algorithm
 * Returns an addres of a node
 */
BinaryTree * search(BinaryTree *leaf, int value){
	bool flag = false;
	while ((leaf!=NULL) && !flag) {
		//if found, then flagg=true thats it
		if (value == leaf->key) {
			flag = true;
			return leaf;
		}
		//if value is lesser than leaf,
		// start looking on the left
		else if (value < leaf -> key) {
			leaf = leaf -> left;
		}
		//Otherwise,
		//start looking on the right
		else {
			leaf = leaf -> right;
		}
	}
	return NULL;
}
