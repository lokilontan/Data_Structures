//============================================================================
// Name        : Lab14_BinarySearchTree_.cpp
// Author      : Vladimir Plagov
// Version     : v1.0
// Copyright   :
// Description : Implementation of a Binary Search Tree. Then Insertion and Sort algorithm
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

struct node {
	char name[30];
	struct node *next = NULL;
};
struct BinaryTree {
	char name[30];
	node *names = NULL;
	BinaryTree *left = NULL;
	BinaryTree *right = NULL;
};

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

//function prororypes
void readFile(struct BinaryTree *&leaf);
void insert(struct BinaryTree *&leaf, char name[]);
void traverseLList(node *current);
void search(BinaryTree *leaf, char name[]);


int main() {

	if (!in) {
		cout << "Cannot open the input.txt file!";
		return 1;
	}

	if (!out) {
		cout << "Cannot open the output.txt file!";
		return 1;
	}


	BinaryTree *leaf = NULL;

	readFile(leaf);

	out << "hi";

			search(leaf, "Troy");


}

void readFile(struct BinaryTree *&leaf){
	char input[30];
	while (in.good()){
		in >> input;
		insert(leaf, input);
	}
}

/*
 * using recursion - tail insertion algorithm
 * NOTE: We insert greater string to the right and lesser to the left
 * NOTE_2: We create a linked list of duplicates under the original leaf
 */

void insert(struct BinaryTree *&leaf, char name[]) {

	//if empty tree
	if (leaf == NULL) {
		leaf = new BinaryTree;
		leaf -> right = NULL;
		leaf -> left = NULL;
		strcpy(leaf->name, name);
	}
	//if new name is greater than leaf, then we send it to the left
	else if (strcmp(name,leaf->name) > 0) {
		insert(leaf->left, name);
	}
	//if new name is lesser than leaf, then we send it to the right
	else if (strcmp(name, leaf->name) < 0) {
		insert(leaf->right, name);
	}
	//if new name is equal to the leaf, then we send to a linked list below the leaf
	else if (strcmp(name, leaf->name) == 0) {
		node *nn = new node;
		strcpy(nn -> name , name);

		if (leaf->names == NULL) {
			leaf->names = nn;
			leaf->names -> next = NULL;
		}
		else {
			nn -> next = leaf -> names;
			leaf -> names = nn;
		}

	}

}

/*
 * Non-recursive search algorithm
 * Prints out its search path
 * Prints out the duplicates of the target if any
 */
void search(BinaryTree *leaf, char name[]){
	bool flag = false;
	while ((leaf!=NULL) && !flag) {
		//if found, print the name of the found leaf and if any duplicates in the linked list than display them all
		if (strcmp(name, leaf->name) == 0) {
			flag = true;
			cout << leaf -> name << " ";
			traverseLList(leaf->names);
		}
		//if name is greater than leaf, we display the leaf what we are located on
		//start looking on the left
		else if (strcmp(name, leaf->name) > 0) {
			cout << leaf -> name << " ";
			leaf = leaf -> left;
		}
		//Otherwise, we display the leaf what we are located on
		//start looking on the right
		else {
			cout << leaf -> name << " ";
			leaf = leaf -> right;
		}
	}
}

void traverseLList(node *current){
	while (current) {
		cout << current->name << " ";
		current = current -> next;
	}
}
