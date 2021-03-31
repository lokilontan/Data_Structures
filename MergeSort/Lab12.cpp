//============================================================================
// Name        : Lab12.cpp
// Author      : Vladimir Plagov
// Version     : 1.0
// Copyright   :
// Description : Merge sort using linked list
// 			   : NEEDS AN "input.txt" file in the root
//============================================================================

#include <iostream>
#include <fstream>


struct node{
	int value;
	node *next;
};

using namespace std;

//function prototypes
void readFile(node *&head);
void traverse(node *current);
void split(node *current, node *&l1, node *&l2);
node *mergeSort(node *head);
node* merge(node* a, node* b);

ifstream in("input.txt");

int main() {

	if (!in) {
		cout<<"Cannot open input file!\n";
			       return 1;
	}

	node *toSort = NULL;

	readFile(toSort);

	cout << "THE LINKED-LIST FROM FILE: ";
	traverse(toSort);

	cout << "\n";

	cout << "THE SORTED LINKED-LIST: ";
	traverse(mergeSort(toSort));


}

//funtions definitions
void readFile(node *&head){
	node *tail = NULL;
	while (in.good()){
		node *temp = new node;
		in >> temp->value;
		temp -> next = NULL;

		if (head==NULL) {
			head = temp;
			tail = temp;
		}
		else {
			tail -> next = temp;
			tail = temp;
		}
	}
}

void traverse(node *current){
	while (current) {
		cout << current->value << " ";
		current = current -> next;
	}
}

node *mergeSort(node *head) {

	node *a = NULL;
	node *b = NULL;
	node *c = NULL;

	if(head==NULL)
		return NULL;
	if (head->next==NULL)
		return head;

	split(head, a, b);

	a=mergeSort(a);
	b=mergeSort(b);
	c=merge(a,b);
	return (c);

}

void split(node *current, node *&l1, node *&l2){

	int count = 0;
	node *current2 = current;
	l1 = current;
	while (current) {
		current = current -> next;
		count++;
	}

	count = ((count-1)/2) ;

	for (int i = 0; i < count; i++) {
		current2 = current2 -> next;
	}

	l2 = current2->next;
	current2->next = NULL;

}

node* merge(node *l1, node *l2) {

	node *current = NULL;

	node *sortedHead = NULL;


	if ((l1 -> value) < (l2 -> value)) {
		sortedHead = l1;
		l1 = l1 -> next;
	}
	else {
		sortedHead = l2;
		l2 = l2 -> next;
	}
	current = sortedHead;

	while ((l1 != NULL) && (l2 != NULL)) {
		if ((l1 -> value) < (l2 -> value)) {
			current -> next = l1;
			current = l1;
			l1 = l1 -> next;
		}
		else {
			current -> next = l2;
			current = l2;
			l2 = l2 -> next;
		}
	}

	while (l1 != NULL) {
		current -> next = l1;
		current = l1;
		l1 = l1 -> next;
	}

	while (l2 != NULL) {
		current -> next = l2;
		current = l2;
		l2 = l2 -> next;
	}

	return sortedHead;

}
