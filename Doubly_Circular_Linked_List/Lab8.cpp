//============================================================================
// Name        : Lab8.cpp
// Author      : Vladimir Plagov
// Version     : 1.0
// Copyright   :
// Description : Doubly Circular Linked List (DCLL)
//============================================================================

#include <iostream>
#include  <fstream>

using namespace std;

fstream in("input.txt");

//Create a node of the DCLL
struct node {
	string name;
	node *next;
	node *prev;
};

//Function prototypes
void insert(node *&head, string nameIn);
void remove(node *&head, int nDel);
int size(node *head);
void traverse(node *head);

int main() {

	//Check the input file stream
	if(!in) {
		cout<<"Cannot open input file!\n";
		return 1;
	}

	//Head for DCLL
	node *head  =  NULL;

	//A string for  input
	string input  = "";

	int nDel = 0;

	while (!in.eof()) {
		in >> input;
		if (input != "\0") {
			insert(head, input);
		}
	}

	cout << "DCLL: "; traverse(head);
	cout << "\nSize of DCLL: " << size(head);

	cout << "\nEnter the number of items to delete: ";
	cin >> nDel;

	remove(head, nDel);

	cout << "Updated DCLL: "; traverse(head);
	cout << "\nSize of DCLL: " << size(head);

	in.close();
}

void insert(node *&head, string nameIn) {

	//Create a new node with "name"
	node *nn = new node;
	nn -> name =  nameIn;

	//if DCLL is empty just insert a new node and let nn`s next and prev point to nn
	if (head == NULL) {
		nn -> next = nn;
		nn -> prev = nn;
		head = nn;
	}
	else {
		nn -> prev = head;
		nn -> next = head -> next;
		head -> next -> prev = nn;
		head -> next = nn;
		head = nn;
	}

}

//remove first n items
void remove(node *&head, int nDel){
	if (size(head) < nDel) {
		cout << "Wrong number! I have only " << size(head) <<  " items\n";
	}
	else {

		for (int i = 0; i < nDel; i++) {
			node *curr = head;
			if (head -> next == head) {
				head = NULL;
				delete curr;
			}
			else {

				head -> prev -> next = head -> next;
				head -> next -> prev = head -> prev;
				head = head -> next;
				delete curr;
			}
		}
	}

}

//return the size of the linked list
int size(node *head) {

	int counter = 0;
	node *temp = head;

	while (temp != NULL) {
			if (temp -> next == head) {
				temp = NULL;
			}
			else {
				temp = temp -> next;
			}
			counter++;
		}
	return counter;
}

//traverse function from *head
void traverse(node *head) {

	node *temp = head;
	while (temp != NULL) {
		cout << temp -> name << " ";
		if (temp -> next == head) {
			temp = NULL;
		}
		else {
			temp = temp -> next;
		}
	}

}
