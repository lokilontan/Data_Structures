//============================================================================
// Name        : Lab3.cpp
// Author      : Vladimir Plagov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Create a stack to implement decimal-to-binary
//				 and decimal-to-hexadecimal conversion algorithms
//============================================================================

#include <iostream>

using namespace std;

//Create a
struct node {
	int data;
	node *next;
};

int peek(node *head);
void push(node *&head, int value);
void pop(node *&head);
void decToBin(node *&head, int decimal);
void decToHex(node *&head, int decimal);
void displayStack(node *&head);

int main() {

	//Head of the stack
	node *head = NULL;


	int decimal;

	cout << "Hello, welcome to decimal to binary/hexadecimal converter! \n \n"
			"What is the number to convert? Number: ";
	cin >> decimal;

	//Convert to binary
	decToBin(head, decimal);
	displayStack(head);

	cout << endl;

	//Convert to hex
	decToHex(head, decimal);
	displayStack(head);
}

int peek(node *head) {
	int out = -1;

	if (head!=NULL) {
		out = head -> data;
	}

	return out;
}

void push(node *& head, int value) {

	node *temp = new node;
	temp -> data = value;

	if (!head) {
		temp -> next = NULL;
		head = temp;
	}
	else {
		temp -> next = head;
		head = temp;
	}

}

void pop(node *&head) {

	if (head != NULL) {
		node *temp = head;
		head = head -> next;
		delete temp;
	}

}

void decToBin(node *&head, int decimal){

	cout << "Binary - ";
	while (decimal != 0) {
		push (head, decimal%2);
		decimal /= 2;
	}

}

void decToHex(node *&head, int decimal){
	cout << "Hex - ";
		while (decimal != 0) {
			push (head, decimal%16);
			decimal /= 16;
		}
}

void displayStack(node *&head) {

	while (head != NULL) {
		switch (peek(head)){
		case -1: cout << "Stack is empty";
		break;
		case 0 ... 9: cout << peek(head);
		break;
		case 10 : cout << 'A';
		break;
		case 11 : cout << 'B';
		break;
		case 12 : cout << 'C';
		break;
		case 13 : cout << 'D';
		break;
		case 14 : cout << 'E';
		break;
		case 15 : cout << 'F';
		break;
		}
		pop(head);
	}
}
