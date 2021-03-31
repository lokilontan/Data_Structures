//============================================================================
// Name        : Lab16_ExpressionTrees.cpp
// Author      : Vladimir Plagov
// Version     : v 1.0
// Copyright   :
// Description : Expression trees using a stack, evaluation, displaying in infix notation with braces.
//============================================================================

#include <iostream>

using namespace std;

//Create a node for the STACK
struct node {
	struct bTree *ptr = NULL;
	node *next = NULL;
};

//Сreate a BINARY TREE NODE
struct bTree {
	char token;
	bTree *left = NULL;
	bTree *right = NULL;
};


//function prototypes
int convert(char token);	//convert a char (0...9) to an int
bool isDigit(char token);	//check if a symbol represents a number
double eval(int R, int L, char token);	//evaluate
bTree * peek(node *head) ;
void push(node *&head,bTree *value);
void pop(node *&head);
void expressionTree(node *&head, string expression);
void inOrder(struct bTree *leaf);
int postOrderEvaluation(struct bTree *expTree);

int main() {

	string postfixExpr;

	cout << "Hello, enter a statement in PostFix notation: ";

	getline(cin, postfixExpr);			//Get the whole string
	cout << "\n";

	node *stackHead = NULL;

	expressionTree(stackHead, postfixExpr);

	inOrder(stackHead->ptr);
	cout << " = ";
	cout << postOrderEvaluation(stackHead -> ptr);
}

//FUNCTION DEFINITIONS

int postOrderEvaluation(struct bTree *expTree){
	int result;

	if (expTree == NULL) return 0;
	int left = postOrderEvaluation(expTree->left);
	int right = postOrderEvaluation(expTree->right);
	if (!isDigit(expTree->token))						//If it`s an operator...
		return eval(right, left, expTree->token);
	else												//Otherwise, convert it to a number...
		return convert(expTree->token);
}

//Display in In Order format - RECURSIVE
void inOrder(struct bTree *leaf) {
	if (leaf != NULL) {
		cout << '(';
		inOrder(leaf -> left);

		cout << leaf -> token;

		inOrder(leaf -> right);
		cout << ')';

	}
}

void expressionTree(node *&head, string postfix) {

	postfix.erase(remove_if(postfix.begin(), postfix.end(), ::isspace), postfix.end());		//Delete the spaces

		for (int i=0; i < postfix.length(); i++) {

			if (isDigit(postfix[i])) {

				bTree *tokenDigit = new bTree;
				tokenDigit -> token = postfix[i];
				push(head, tokenDigit);

			}
			else {

				bTree * tokenOperand = new bTree;
				tokenOperand -> token = postfix[i];
				tokenOperand -> right = peek(head); pop(head);
				tokenOperand -> left = peek(head); pop(head);
				push(head, tokenOperand);

			}

		}
}

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

bTree * peek(node *head) {
	bTree *out = NULL;

	if (head!=NULL) {
		out = head -> ptr;
	}

	return out;
}

void push(node *& head, bTree *value) {

	node *temp = new node;
	temp -> ptr = value;

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

