
//============================================================================
// Name        : Lab19_Heap.cpp
// Author      : Vladimir Plagov
// Version     : 2.0
// Copyright   :
// Description : Insert 10 values into a min-heap from a file.  Display the data, level by level.
//				 Then delete 5 items. After each delete, display the heap, level by level.
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>


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

//function prototypes
void readFile();
void siftUp(int index);
void swapVal(int aI, int bI);
void breadth(struct BinaryTree *leaf);
void enqueue(node *&front, node *&rear, int value);
int dequeue(node *&front, node *&rear);
BinaryTree * search(BinaryTree *leaf, int value);
BinaryTree * unsortedToBST(int i);
int height(BinaryTree* leaf);
void siftDown (int parent);
BinaryTree * searchval(BinaryTree* leaf, int k);

fstream in("input.txt");
fstream out("out.txt");

vector<int> arr;
vector<int> arr2;
int HS;	//HEAPSIZE

int main() {
	if (!in) {
			cout << "Cannot open the input.txt file!";
			return 1;
		}

	readFile();

	HS = arr.size(); //HEAPSIZE

	BinaryTree *BST = new BinaryTree;
	BST = unsortedToBST(0);

	// probably not all elements are inserted
	//-1 is gonna be the NULL (FILL IT OUT TO MAKE A COMPLETE PERFECT TREE)
	for (int i = 0; i < pow(2, height(BST)+1)-1; i++) {
		arr2.push_back(-1);
	}

	//Now make an array with appropriate amount of elements

	for (int i = 0; i < arr.size(); i++)
		arr2[i]=arr[i];

	arr.clear();

	//fill the initial array
	for (int i = 0; i < arr2.size(); i++) {
		arr.push_back(arr2[i]);
	}

	BST = unsortedToBST(0);

	cout << "The PERFECT array:\n";
	for (int i = 0; i < arr.size(); i++)
			cout << arr[i] << " ";

	cout << "\n\nBST from the unsorted perfect array:\n";
	breadth(BST); //		Now WORKS! Changed the search algoright. It worked only with a sorted BST. But min-heap is unsorted

	//----1----
	cout << "\nREMOVE: " << arr[0];
	swapVal(0,9);
	arr[9]=-1;
	siftDown(0);
	cout << "\n";
	BST = unsortedToBST(0);
	breadth(BST);

	//----2----
	cout << "\nREMOVE: " << arr[0];
	swapVal(0,8);
	arr[8]=-1;
	siftDown(0);
	cout << "\n";
	BST = unsortedToBST(0);
	breadth(BST);

	//----3----
	cout << "\nREMOVE: " << arr[0];
	swapVal(0,7);
	arr[7]=-1;
	siftDown(0);
	cout << "\n";
	BST = unsortedToBST(0);
	breadth(BST);

	//----4----
	cout << "\nREMOVE: " << arr[0];
	swapVal(0,6);
	arr[6]=-1;
	siftDown(0);
	cout << "\n";
	BST = unsortedToBST(0);
	breadth(BST);

	//----5----
	cout << "\nREMOVE: " << arr[0];
	swapVal(0,5);
	arr[5]=-1;
	siftDown(0);
	cout << "\n";
	BST = unsortedToBST(0);
	breadth(BST);

}

void readFile() {

	int input;
	int count=0;
	while (in.good()) {
		in >> input;
		arr.push_back(input);
		siftUp(count);
		count++;
	}
}

void siftUp(int index) {
	if (index != 0) {
		int parentIndex = (index-1)/2;
		if (arr[parentIndex] > arr[index]) {
			swapVal(parentIndex, index);
			siftUp(parentIndex);
		}
	}
}

void swapVal(int aI, int bI){
	int tempVal = arr[aI];
	arr[aI] = arr[bI];
	arr[bI] = tempVal;
}

void breadth(struct BinaryTree *leaf) {
	//for the QUEUE currentLevel
	node *clf = NULL;
	node *clr = NULL;
	//for the QUEUE nextLevel
	node *nlf = NULL;
	node *nlr = NULL;

	BinaryTree *current = NULL;
	//cout << "here";
	enqueue(clf, clr, leaf->value);
	while (clf != NULL) {

		current = searchval(leaf, clf->data);
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
 * Recursive search algorithm
 * Returns an address of a node
 */

BinaryTree * searchval(BinaryTree* leaf, int k)
  {
      if (leaf ->value  == k)
          return leaf;

     BinaryTree * n = NULL;

      if (leaf->left != NULL)
          n = searchval(leaf->left, k);
      if (n != NULL) return n;
      if (leaf->right!= NULL)
          n = searchval(leaf->right, k);
      if (n != NULL) return n;

      return NULL;
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

void siftDown (int parentI) {
	int LchildI = (2*parentI) + 1;
	int RchildI = (2*parentI) + 2;


	if (LchildI <= HS){
		int min;
		if (LchildI == HS){
			min = LchildI;
		}

		else {
			if (arr[LchildI] < arr[RchildI])
				min = LchildI;
			else
				min = RchildI;
		}
		if ((arr[parentI] > arr[min]) && (arr[min] != -1))
		{
			swapVal(parentI, min);
			siftDown(min);
		}
	}
}

