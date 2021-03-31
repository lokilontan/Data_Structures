//============================================================================
// Name        : Lab10.cpp
// Author      : Vladimir Plagiv
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Radix Sort
//============================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>

struct node {
	int value;
	node *next;
};

struct Queue{
	node *front = NULL;
	node *rear = NULL;
};

int a[10];

//function prototypes
void fillA();
void showA();
int findMax();
void enqueue(Queue &Q, int data);	//adds to the back
int dequeue(Queue &Q);	//removes from the front

using namespace std;


int main() {

	fillA();

	cout << "Original array: "; showA(); cout << "\n";

	int n = 1; //Will divide by n every time to get the needed digit
	int max = findMax();
	Queue Q[10];


	while (n <= max) {
		int j = 0;
		for (int i = 0; i < 10; i++) {
			enqueue(Q[(a[i]/n)%10], a[i]);
		}
		for (int i=0; i < 10; i++) {
			while (Q[i].front != NULL) {
				a[j] = dequeue(Q[i]);
				j++;
			}
		}
		n *= 10;
	}

	cout << "\nSorted array: "; showA(); cout << "\n\nTry AGAIN!!!!";

	/*
	 * Enqueue/Dequeue TEST
	for (int i=0; i < 10; i++) {
		enqueue(Q[i],a[i]);
	}
	cout << "\n" << "Check if every queue accepts a value from array: ";
	for (int i=0; i < 10; i++) {
		cout << dequeue(Q[i]) << " ";
	}

	cout << "\n" << "Check if queue`s are empty (should print -404): ";
	for (int i=0; i < 10; i++) {
		cout << dequeue(Q[i]) << " ";
	}
	*/
}

//function definitions
void fillA() {
	srand (time(NULL));
	for (int i = 0; i < 10; i++) {
		a[i] = rand() % 1001;
	}
}
void showA(){
	for (int i = 0; i < 10; i++) {
		cout << a[i] << " ";
	}
}
int findMax() {
	int max = a[0];

	for (int i = 1; i < 10; i++){
		if (a[i] > max) max = a[i];
	}

	return max;
}
void enqueue(Queue &Q, int data){


	node *nn = new node;
	nn -> value = data;
	nn -> next = NULL;

	if (Q.front == NULL) {
		Q.front = nn;
		Q.rear = nn;
	}
	else {
		Q.rear -> next = nn;
		Q.rear = nn;
	}

}
int dequeue(Queue &Q){

	int tempVal = -404;
	if (Q.front != NULL) {
		node *temp = Q.front;
		tempVal = Q.front -> value;
		Q.front = Q.front -> next;
		delete temp;
		if (Q.front == NULL) {
			Q.rear = NULL;
		}
	}
	return tempVal;

}
