//============================================================================
// Name        : Lab5.cpp
// Author      : Vladimir Plagov
// Version     : 1.0
// Copyright   :
// Description : Infix expression to postfix notation
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

struct node{
	char token;
	node *next;
};

//function prototypes
//---STACK---
char peek(node *head);
void push(node *&head, char value);
void pop(node *&head);

//---QUEUE---
void enqueue(node *&front, node *&rear, char value);	//adds to the back
char dequeue(node *&front, node *&rear);	//removes from the front
void traverse(node *current);

//---OTHER_STUFF---
bool isDigit(char token);	//check if a symbol represents a number
int precedence(char token);  //check what`s operator`s precedence
void infToPostf(string expression, node *&qFront, node *&qRear, node *&sHead);		//convert an infix to postfix, result in the queue

fstream in("input.txt");

int main() {

	if(!in) {
		cout<<"Cannot open input file!\n";
		return 1;
	}

	//Declare a head pointer for the Stack
	node *sHead = NULL;

	//Declare a front and rear for the Queue
	node *qFront = NULL;
	node *qRear = NULL;

	//Declare a string for input expression
	string expression = "";

	//Read an expression from a file
	in >> expression;


	cout << "Infix: " << expression << "\n";

	infToPostf(expression, qFront, qRear, sHead);

	/*
	TEST_isDigit()
	cout << "\n";
	for (int i = 0; i < expression.length(); i++){
		if (isDigit(expression[i])) cout << "Is digit? " << expression[i] << ": Yes\n";
		else cout << "Is digit? " << expression[i] << ": No\n";
	}
	*/

	/*
	Test_precedence();
	cout << "\n";
	for (int i = 0; i < expression.length(); i++){
		cout << "Precedence of " << expression[i] << ": " << precedence(expression[i])<< "\n";
	}
	*/

	cout << "Postfix: "; traverse(qFront);



	in.close();
}
//---STACK---
//TODO: Check data types
void push(node *& head, char value) {

	node *temp = new node;
	temp -> token = value;

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

char peek(node *head) {
	char out = '!';

	if (head!=NULL) {
		out = head -> token;
	}

	return out;
}

//---QUEUE---
//TODO: Check data types
void enqueue(node *&front, node *&rear, char value){

	node *nn = new node;
	nn -> token = value;
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
char dequeue(node *&front, node *&rear){

	char tempVal = '!';
	if (front != NULL) {
		node *temp = front;
		tempVal = front -> token;
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
			cout << current->token;
			current = current -> next;
		}

}


//---OTHER_STUFF---
bool isDigit(char token){	//check if a symbol represents a number
	return ((precedence(token) == -1) && (token!=')'));
}
int precedence(char token){  //check what`s operator`s precedence if number or ')', return -1
	int precedence = -1;
	switch(token){
	case '=': precedence = 0;
	break;
	case '(': precedence = 1;
	break;
	case '+': case '-': precedence = 2;
	break;
	case '*': case '/': precedence = 3;
	break;
	}
	return precedence;
}
void infToPostf(string exp, node *&qFront, node *&qRear, node *&sHead){		//convert an infix to postfix, result in the queue
	for (int i = 0; exp[i] != '\0'; i++){
		if (isDigit(exp[i])) {
			enqueue(qFront, qRear, exp[i]);
		}
		else if (exp[i]=='(') {
			push(sHead, exp[i]);
		}
		else if (exp[i]==')') {
			while ( peek(sHead) != '('){
				enqueue(qFront, qRear, peek(sHead));
				pop(sHead);
			}
			pop(sHead);
		}
		else {
			while ((sHead != NULL) && (precedence(exp[i]) <= precedence(peek(sHead)))) {
				enqueue(qFront, qRear, peek(sHead));
				pop(sHead);
			}
			push(sHead, exp[i]);
		}
	}
	while (sHead != NULL) {

		enqueue(qFront, qRear, peek(sHead));
		pop(sHead);
	}
}

