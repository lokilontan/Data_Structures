//============================================================================
// Name        : Lab6.cpp
// Author      : Vladimir Plagov
// Version     : 1.0
// Copyright   :
// Description : Postfix expression evaluation
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

//Create a node
struct node {
	int token;
	node *next;
};
//function prototypes
int convert(char token);	//convert a char (0...9) to an int
bool isDigit(char token);	//check if a symbol represents a number
double eval(int R, int L, char token);	//evaluate
int peek(node *head);
void push(node *&head, int value);
void pop(node *&head);


fstream in("input.txt");

int main() {
	if(!in) {
		cout<<"Cannot open input file!\n";
		return 1;
	}

	//Declare a head pointer for the Stack
	node *head = NULL;

	//Declare a string for input expression
	string expression = "";

	int right, left = 0;

	//Read an expression from a file
	in >> expression;

	cout << "PostFix: " << expression;


	//Test convert()
	/*
	int j = -404;
	for(int i=0; expression[i] != '\0'; i++)
	if (isDigit(expression[i])) {
		j = convert(expression[i]);
		cout << "\n" << j;
	}
	*/

	//EVALUATION ALGHORITHM
	for (int i=0; expression[i] != '\0'; i++){
			if (isDigit(expression[i])) {
				push(head, convert(expression[i]));
			}
			else {
				right = peek(head);
				pop(head);
				left = peek(head);
				pop(head);
				push(head, eval(right, left, expression[i]));
			}
	}

	cout << "\nResult = " << peek(head);

}

//FUNCTION DEFINITIONS

int convert(char token){	//convert a char (0...9) to an int
	return (token - '0');
}

bool isDigit(char token){	//check if a symbol represents a number
	return ((token!=')') && (token!='(') && (token!='+') && (token!='-') && (token!='=') && (token!='*') && (token!='/'));
}

double eval(int R, int L, char token){	//evaluate

	double Result = 0;
	switch (token){
	case '+': Result = L+R;
	break;
	case '-': Result = L-R;
	break;
	case '*': Result = L*R;
	break;
	case '/': Result = L/R;
	break;
	}
	return Result;
}

int peek(node *head) {
	int out = -1;

	if (head!=NULL) {
		out = head -> token;
	}

	return out;
}

void push(node *& head, int value) {

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
