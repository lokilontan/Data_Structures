//============================================================================
// Name        : CS13_Lab1.cpp
// Author      : Vladimir Plagov
// Version     :
// Copyright   :
// Description : Operations with strings.
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

//Function Prototypes
void stringCopy(char *A, char *B);
bool stringCompare(char *A, char *B);
void stringConcatenation (char *A, char *B);
int stringPosition(char *A, char B);
int stringLength(char *A);
void displayArray(char *A);
void displayChar(char A);

//Assign the input.txt to the input file stream
ifstream in("input.txt");

//Constants for the array sizes
const int MAX_SIZE = 100;

int main() {

	//Declare char arrays
	char a[MAX_SIZE], b[MAX_SIZE];

	//Check if input file stream is ok
	if(!in)
	{
		cout<<"Cannot open input file\n";
	       return 1;
	}

		//TEST stringCopy(char *A, char *B)
		in >> a >> b ;
		stringCopy(a, b);
		cout << "stringCopy: \n Array A: "; displayArray(a); cout << " Array B: "; displayArray(b); cout << "\n";

		//TEST stringCompare(char *A, char *B)
		in >> a >> b;
		cout << "stringCompare: \n Array A: "; displayArray(a); cout << " Array B: "; displayArray(b);
		if (stringCompare(a, b)) {cout << " Strings are exactly the same (TRUE)\n\n";}
				else {cout << " Strings are not the same (FALSE)\n\n";}

		//TEST stringConcatenation(char *A, char *B)
		in >> a >> b;
		stringConcatenation(a, b);
		cout << "stringConcatenation: \n Array A: "; displayArray(a); cout << " Array B: "; displayArray(b); cout << "\n";

		//TEST stringPosition(char *A, char B)
		char c;
		in >> a >> c;
		cout << "stringPosition: \n Array A: "; displayArray(a); cout << " Char B: "; displayChar(c);
		cout << " m`s position in the array A: " << stringPosition(a, c) << "\n";

		//TEST stringLength(char *A)
		in >> a;
		cout << "\nstringLength: \n Array A: "; displayArray(a);
		cout << " Length of A: " << stringLength(a) << "\n A affter call: "; displayArray(a);



	in.close();

}

//The function will take two strings, A and B, as parameters.
//It will replace the contents of string A with the contents of string B.
void stringCopy(char *A, char *B) {
	int counter = 0;
	for (int i = 0; B[i] != '\0'; i++) {
		A[i] = B[i];
		counter++;
	}
	A[counter] = '\0';
}

//This function will take two strings, A and B, as parameters and return a bool.
//It will return true if the strings are exactly the same, character by character,
//and false otherwise. The function will be case sensitive, that is, ‘A’ !=’a’.
bool stringCompare(char *A, char *B){
	int counter = 0;
	bool flag = true;
	while ( (A[counter] != '\0') || (B[counter] != '\0') ) {
		if (A[counter] != B[counter]) {
			flag = false;
			break;
		}
		counter++;
	}
	return flag;
}

//This function will take two strings, A and B, as parameters. It will combine
//them such that B is appended to the end of A. For example, given A=”abcd” and
//B=”efgh”, the function will change A so that it now contains “abcdefgh”. String
//B will be unchanged by the function.
void stringConcatenation(char *A, char *B){
	int counterA = 0;
	while ( A[counterA] != '\0' ) {
		counterA++;
	}
	int counterB = 0;
	while ( B[counterB] != '\0' ) {
		A[counterA] = B[counterB];
		counterB++;
		counterA++;
	}
}

//This function will take a string and a character as parameters. It will return
//the position in the string of the first occurrence of the character. The first
//character in the string is in position 0. If the string does not contain the
//character, it returns -1.
int stringPosition(char *A, char B){
	int counter = 0;
	int out = -1;
	while ( A[counter] != '\0' ) {
		if ( A[counter] == B) {
			out = counter;
			break;
		}
		counter++;
	}
	return out;
}

//This function will take a char array as a parameter. It will shift all the characters
//of the string to the right by one and store the length of the string in position zero.
//The length of the string does not include the null character. The function will return
//the length which is stored in position zero.
int stringLength(char *A) {
	int counter = 0;
	while ( A[counter] != '\0' ) {
		counter++;
	}

	for (int i = counter; i > 0; i--){
		A[i] = A[i-1];
	}
	A[0] = (char)(counter + '0');

	return counter;
}

void displayArray(char *A) {
	cout << A << "\n";
}

void displayChar(char A) {
	cout << A << "\n";
}
