//============================================================================
// Name        : Lab15_DeleteTree.cpp
// Author      : Vladimir Plagov
// Version     : 2.0
// Copyright   :
// Description : -Implementing a delete function for a tree
//				 -In addition, what`s been told in class I implemented a parentOf(node) function
//				 	I need it to remove the link from the parent to deleted item.
//					I probably need it because I didn`t do a recursive deletion function
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

//struct for the BT
struct BinaryTree {
	int value ;
	BinaryTree *left = NULL;
	BinaryTree *right = NULL;
};

//struct for a queue
struct node{
	int data;
	node *next;
};

fstream in("input.txt");
fstream out("output.txt");

//function prototypes
void readFile(struct BinaryTree *&leaf);
void insert(struct BinaryTree *&leaf, int value );
BinaryTree * search(BinaryTree *leaf, int value);
void remove(BinaryTree *&leaf, int value);
BinaryTree * parentOf(BinaryTree *leaf, int value);
int minleft(BinaryTree *leaf);
void preOrder(struct BinaryTree *leaf, fstream &out);
void inOrder(struct BinaryTree *leaf, fstream &out);
void postOrder(struct BinaryTree *leaf, fstream &out);
void breadth(struct BinaryTree *leaf, fstream &out);
void enqueue(node *&front, node *&rear, int value);
int dequeue(node *&front, node *&rear);

int main() {
	if (!in) {
		cout << "Cannot find the input.txt file!";
		return 1;
	}

	if (!out) {
		cout << "Cannot find the output.txt file!";
		return 1;
	}

	//For the Binary Tree
	BinaryTree *leaf = NULL;

	readFile(leaf);

	out << "Pre-Order: "; preOrder(leaf, out);

	out << "\nIn-Order: "; inOrder(leaf, out);

	out << "\nPost-Order: "; postOrder(leaf, out);

	out << "\nBreadth:\n";breadth(leaf, out);

	in.close();
	out.close();
}

void readFile(struct BinaryTree *&leaf){
	string input;
	while (in.good()){
		in >> input;
		if ((input.compare("delete")) == 0) {
			in >> input;
			if (search(leaf, stoi(input)) == NULL)
				insert(leaf, stoi(input));
			else
				remove(leaf, stoi(input));
		}
		else
		insert(leaf, stoi(input));
	}
}
/*
 * using recursion - tail insertion algorithm
 * NOTE: We insert greater value to the right and lesser to the left
 * NOTE_2: We create a linked list of duplicates under the original leaf
 */

void insert(struct BinaryTree *&leaf, int value) {

	//if empty tree
	if (leaf == NULL) {
		leaf = new BinaryTree;
		leaf -> right = NULL;
		leaf -> left = NULL;
		leaf->value = value;
	}
	//if new value is greater than leaf, then we send it to the right
	else if (leaf->value > value) {
		insert(leaf->left, value);
	}
	//if new value is lesser than leaf, then we send it to the left
	else if (leaf->value < value) {
		insert(leaf->right, value);
	}
	//if new value is equal to the leaf, then you do not provide the promised conditions
	else if (leaf->value == value) {
		cout << "This program does not handle duplicates!";
	}

}

/*
 * Non-recursive search algorithm
 * Returns an addres of a node
 */
BinaryTree * search(BinaryTree *leaf, int value){
	bool flag = false;
	while ((leaf!=NULL) && !flag) {
		//if found, then flagg=true thats it
		if (value == leaf->value) {
			flag = true;
			return leaf;
		}
		//if value is lesser than leaf,
		// start looking on the left
		else if (value < leaf -> value) {
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

//Returns the address of a parrent of a node
BinaryTree *parentOf(BinaryTree *leaf, int value){
	bool flag = false;
		while ((leaf!=NULL) && !flag) {
			//if found, then flagg=true thats it
			if ( ((leaf -> left != NULL) && (value == leaf->left -> value)) ||
					((leaf -> right != NULL) && (value == leaf->right -> value)) )
			{
				flag = true;
				return leaf;
			}
			//if value is lesser than leaf,
			// start looking on the left
			else if (value < leaf -> value) {
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

//Remove function
void remove(BinaryTree *&leaf, int value){

	struct BinaryTree *current = search (leaf, value);

	//check if search function actually found the item
	if (current != NULL) {

		//IF NO CHILDREN
		if ((current -> left == NULL) && (current -> right == NULL)) {

			//Find the parrent of the current
			BinaryTree *parent = parentOf(leaf, current->value);

			//If no parent, then the current is only one with no children in the tree and we need to delete it
			if (parent == NULL) {
				leaf = NULL;
			}
			//If there is a parrent then there are more items
			//delete appropriate connection(we only now that there is a parent and we don`t know
			//what is the side where the current comes from) of the parrent with the current
			else
				if ((parent -> left != NULL) && (parent -> left -> value == current -> value)) {
					parent -> left = NULL;
				}
				else {
					if ((parent -> right != NULL) && (parent -> right -> value == current -> value))
					parent -> right = NULL;
				}
			delete current;
		}
		//IF TWO CHILDREN
		else
			if ((current->left != NULL) && (current->right != NULL)) {
				int leftvalue = minleft(current->right);
				current -> value = leftvalue;
				remove(current->right, leftvalue);
			}
		//IF ONE CHILD
			else if ((current->left != NULL) || (current->right != NULL)) {
				//Find the parrent of the current
				BinaryTree *parent = parentOf(leaf, current->value);

				//If no parent, then the current is the top parrent with one children and
				//we need to connect the head-leaf to the child
				if (parent == NULL) {
					if(current -> left != NULL) {
						leaf = current -> left;
					}
					else {
						leaf = current -> right;
					}
				}
				//if there is a parent then we are somewhere in the middle
				//conncet the appropriate node with the parrent
				else
					//if the current is on the left of its parrent
					if ((parent -> left != NULL) && (parent -> left -> value == current -> value)) {
						//if the current has a child on its left then connect parent`s left to the current`s left
						if (current -> left != NULL)
							parent -> left = current -> left;
						//otherwise, connect parrent`s left to the current right
						else
							parent -> left = current -> right;
				}
				else {
					//if the current is on the right of its parrent
					if ((parent -> right != NULL) && (parent -> right -> value == current -> value)) {
						//if the current has a child on its left then connect parent`s right to the current`s left
						if (current-> left != NULL)
							parent -> right = current -> left;
						//otherwse, connect parrent`s right to the current right
						else
							parent->right = current -> right;
					}
				}
				delete current;
			}
	}
}
//Returns the leftest (min) value of a given subtree or a tree
int minleft(BinaryTree *leaf) {

	if (leaf -> left == NULL) {
		return leaf -> value;
	}
	else return minleft(leaf->left);
}

//Display in Pre Order format - RECURSIVE
void preOrder(struct BinaryTree *leaf, fstream &out) {
	if (leaf != NULL) {
		out << leaf -> value;
		preOrder(leaf->left, out);
		preOrder(leaf -> right, out);
	}
}
//Display in In Order format - RECURSIVE
void inOrder(struct BinaryTree *leaf, fstream &out) {
	if (leaf != NULL) {
		inOrder(leaf -> left, out);
		out << leaf -> value;
		inOrder(leaf -> right, out);
	}
}
//Display in Post Order format - RECURSIVE
void postOrder(struct BinaryTree *leaf, fstream &out) {
	if (leaf != NULL) {
		postOrder(leaf -> left, out);
		postOrder(leaf -> right, out);
		out << leaf -> value;
	}
}

void breadth(struct BinaryTree *leaf, fstream &out) {
	//for the QUEUE currentLevel
	node *clf = NULL;
	node *clr = NULL;
	//for the QUEUE nextLevel
	node *nlf = NULL;
	node *nlr = NULL;

	BinaryTree *current = NULL;

	enqueue(clf, clr, leaf->value);
	while (clf != NULL) {

		current = search(leaf, clf->data);
		out << clf->data;
		dequeue(clf, clr);
		if (current -> left != NULL)
			enqueue(nlf, nlr, current->left->value);
		if (current -> right != NULL)
			enqueue(nlf, nlr, current->right->value);

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
