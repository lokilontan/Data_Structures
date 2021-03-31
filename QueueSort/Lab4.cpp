//============================================================================
// Name        : Lab4.cpp
// Author      : Vladimir Plagov
// Version     : 1.0
// Copyright   : bla-bla-bla
// Description : Implementing the Queue for a sorting of positive numbers from
//				 a set of different numbers
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

struct node{
	int data;
	node *next;
};

//function prototypes
void enqueue(node *&front, node *&rear, int value);	//adds to the back
int dequeue(node *&front, node *&rear);	//removes from the front
void traverse(node *current);

ifstream in("input.txt");


int main() {
	//Check the input stream
	if (!in) {
			cout<<"Cannot open input file!\n";
			return 1;
	}

	node *front = NULL;
	node *rear = NULL;

	int tempVal = -404;

	//Fill up the Queue
	while (!in.eof()) {
		in >> tempVal;
		enqueue(front, rear, tempVal);
	}

	cout << "Initial queue \n"; traverse(front);

	//Sorting algorithm
	node *stopHere = rear;
	while (front) {
		tempVal = dequeue(front, rear);
		if (tempVal > 0) enqueue(front, rear, tempVal);
		if (front == stopHere) {
			tempVal = dequeue(front, rear);
			if (tempVal > 0) enqueue(front, rear, tempVal);
			break;
		}
	}

	cout << "\nFinal queue \n"; traverse(front);

}

//function definitions
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
void traverse(node *current){
	while (current) {
			cout << current->data << endl;
			current = current -> next;
		}

}
