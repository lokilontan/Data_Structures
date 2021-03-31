//============================================================================
// Name        : Lab7.cpp
// Author      : Vladimir Plagov
// Version     : 1.0
// Copyright   :
// Description : Doubly Linked List (DLL) in C++
//============================================================================

#include <iostream>
#include  <fstream>

using namespace std;

//Create a node of the DLL
struct node {
	string name;
	node *next;
	node *prev;
};

fstream in("input.txt");
fstream out("output.txt");

//Function prototypes
void insert(node *&head, node *&tail,  string nameIn);
void remove(node *&head, node *&tail, string nameIn);
void traverse(node *start, fstream& out);

int main() {

	//Check the input file stream
	if(!in) {
		cout<<"Cannot open input file!\n";
		return 1;
	}

	//Check the output file stream
	if(!out) {
		cout<<"Cannot open output file!\n";
		return 1;
	}

	//Head and Tail for DLL
	node *head  =  NULL;
	node *tail = NULL;

	//A string for  input
	string input  = "";


	//Read  the file and insert/delete to/from DLL
	while  (!in.eof()) {
		in >> input;
		if (input == "delete") {
			in >> input;
			remove(head, tail, input);
		}
		else {
			insert(head, tail, input);
		}
	}

	traverse (head, out);

	out << "=========\n";

	traverse(tail, out);

	in.close();
	out.close();
}

void insert(node *&head, node *&tail,  string nameIn) {

	//Create a new node with "name"
	node *nn = new node;
	nn -> name =  nameIn;

	//if DLL is empty just insert a new node
	if (head ==  NULL) {
		nn -> next = NULL;
		nn -> prev = NULL;
		head = nn;
		tail =  nn;
	}
	//if input string is less than first item in DLL then insert it to the front
	else if  (nameIn < head -> name) {
		nn -> next = head;
		nn -> prev = NULL;
		head -> prev = nn;
		head = nn;
	}
	//if input string is greater than last item in DLL then insert it to the back
	else if (nameIn > tail -> name) {
		nn -> next = NULL;
		nn -> prev = tail;
		tail -> next = nn;
		tail = nn;
	}
	//search the item which is greater than input string and insert it before this item
	else {
		node *curr = head;
		while (nameIn > curr -> name) {
			curr = curr -> next;
		}
		nn -> prev  = curr ->  prev;
		nn -> next = curr;
		curr -> prev -> next = nn;
		curr -> prev = nn;

	}
}

//remove the item with string nameIn
void remove(node *&head, node *&tail, string nameIn){
	node *curr = head;
	while (curr != NULL) {
		if (curr -> name == nameIn) {

			if (curr -> prev != NULL) {
				curr -> prev -> next = curr -> next;
			}
			else {
				head = curr -> next;
				head -> prev = NULL;
			}
			if (curr -> next != NULL) {
				curr -> next -> prev = curr -> prev;
			}
			else {
				tail = curr -> prev;
				tail -> next = NULL;
			}

			curr -> prev = NULL;
			curr -> next = NULL;

			delete curr;

			break;
		}
		curr = curr -> next;
	}
}

//traverse function from *start. Accepts only extreme points of DLL such as head or tail.
//Insert *head to traverse in ascending order and *tail for descending order.
void traverse(node *start, fstream& out) {

	if (start -> prev == NULL) {
		while (start) {
			out << start -> name << "\n";
			start = start -> next;
		}
	}
	else {
		while (start) {
			out << start -> name << "\n";
			start = start -> prev;
		}

	}
}
