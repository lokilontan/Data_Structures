//============================================================================
// Name        : Lab18_Trees<->Arrays.cpp
// Author      : Vladimir Plagov
// Version     : v 1.0
// Copyright   :
// Description : Given a list of numbers in sorted order, create a binary search tree.
//				 Insert the contents of the binary search tree into an unsorted array.
//				 Using the unsorted array, reconstruct the binary search tree.
//				 Display the binary search tree in in-order format.
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

struct BinaryTree {
	int value;
	BinaryTree *left = NULL;
	BinaryTree *right = NULL;
};

//struct for a queue
struct node{
	int data;
	node *next;
};

using namespace std;

fstream in("input.txt");

//prototypes
void breadth(struct BinaryTree *leaf);
void enqueue(node *&front, node *&rear, int value);
int dequeue(node *&front, node *&rear);
BinaryTree * search(BinaryTree *leaf, int value);
int height(BinaryTree* leaf);
BinaryTree * sortedToBST(vector<int> arr, int start, int end);
void BSTtoUnsorted(BinaryTree *leaf, int i);
BinaryTree * unsortedToBST(int i);
int BSTtoSorted(BinaryTree *leaf, int i);

vector<int> arr;

int main() {

	if (!in) {
		cout << "Cannot open the input.txt file!";
		return 1;
	}

	int num=0;

	while (in.good()) {
		in >> num;
		arr.push_back(num);
	}

	//***1***
	BinaryTree *BST = new BinaryTree;
	BST = sortedToBST(arr, 0, arr.size()-1);

	cout << "Sorted array to a BST: \n"; breadth(BST);

	//***2***
	cout << endl << "BST to an unsorted array:\n";
	arr.clear();

	//-1 is gonna be the NULL
	for (int i = 0; i < pow(2, height(BST)+1)-1; i++) {
		arr.push_back(-1);
	}

	BSTtoUnsorted(BST, 0);

	for (int i=0; i < arr.size(); i++) {
			cout << arr[i] << " ";
	}

	//***3***
	cout << "\n\nUnsorted array to a BST:\n";
	BinaryTree *BST2 = new BinaryTree;
	BST2 = unsortedToBST(0);
	breadth(BST2);

	//***4***
	cout << "\nBST to a sorted array (In-order format displaying):\n";
	arr.clear();
	//-1 is gonna be the NULL
	for (int i = 0; i < pow(2, height(BST)+1)-1; i++) {
		arr.push_back(-1);
	}
	BSTtoSorted(BST2, 0);
	for (int i=0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}

}

void breadth(struct BinaryTree *leaf) {
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
		cout << clf->data << " ";
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

			cout << endl;
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

int height(BinaryTree* leaf) {
	if (leaf==NULL)
		return (-1);
	else
	{
		int L = height(leaf->left);
		int R = height(leaf->right);
		if (L>R)
			return (L+1);
		else
			return (R+1);
	}
}


BinaryTree * sortedToBST(vector<int> arr, int start, int end) {
	if (start > end) {
		return NULL;
	}

	int mid = (start+end)/2;

	BinaryTree *root = new BinaryTree;
	root->value = arr[mid];

	root->left = sortedToBST(arr, start, mid-1);
	root->right = sortedToBST(arr, mid+1, end);
	return root;

}

void BSTtoUnsorted(BinaryTree *leaf, int i){
	if (leaf != NULL) {
		arr[i] = leaf->value;
		BSTtoUnsorted(leaf->left, (2*i)+1);
		BSTtoUnsorted(leaf->right, (2*i)+2);
	}
}

BinaryTree * unsortedToBST(int i) {
	BinaryTree *leaf = NULL;
	if (arr[i] != -1) {
		leaf = new BinaryTree;
		leaf->value = arr[i];
		if (((i*2)+2) < arr.size()) {
			leaf->left = unsortedToBST((i*2)+1);
			leaf->right = unsortedToBST((i*2)+2);
		}
	}
	return leaf;
}

int BSTtoSorted(BinaryTree *leaf, int i){
	if (leaf->left != NULL) {
		i=BSTtoSorted(leaf->left,i);
	}
	arr[i++] = leaf->value;
	if (leaf -> right != NULL) {
		i=BSTtoSorted(leaf->right, i);
	}
	return i;
}
