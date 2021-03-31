//============================================================================
// Name        : Lab20_Hashing.cpp
// Author      : Vladimir Plagov
// Version     : 1.0
// Copyright   :
// Description : 10-elements array(I`ll use 11, cause lecture says prime number must be used)
//				 Add items using next order of hashing mechanisms and if colide move forward
//				 Modulo-division->Double hashing->3xQuadratic probing->Linear probing
//				 Ask the user for the number to find. If not found, display: "Not in the list!"
//				 0 in the array is a NULL (not an element)
//============================================================================

#include <iostream>
#include <array>
#include <fstream>

using namespace std;

//function prototypes
int lFactor(); 			//Function that determines the Load Factor of the array. We don`t want to fill it more than 70%
int mod(int token); 	//Returns the modulus or in this case the index of the item where it is supposed to be located using modulo-division
int nextLPrime(int prime); 		//Returns the next lower prime; Be careful with being out of bounds of the primes array!
int dHash(int token, int prime);		//Retrurns the index where an item must be placed(First check mod function, then apply second hashing function)
int quadP(int token);  			//Returns the index where an item should be placed using Quadratic probing 3 times
int linearP(int token);		//Returns the index after running a modulo-division method then bruteforcing the next free position
int getToken();				//Returns a number from the file;
int hashIt(int token);		//Returns the index for a number running through the hashing algorightms in the given sequence . Updates the COLLISIONS
void add(int token); 		//Adds one number at a time into the table array; Displays the collisions; Zero collisions!
void readFile();			//Adds the right amount(loading factor) of numbers
int searchToken(int token);	//Searches for a number. Returns its index.

int table[11];
int primes[5] = {2, 3, 5, 7, 11};
int collisions=0;

fstream in("input.txt");

int main() {
	if (!in) {
				cout << "Cannot open the input.txt file!";
				return 1;
			}
	cout << "This program handles the Load Factor! You have " << lFactor() << " items to insert. If you need more, then increase the table array!\n\n";

	readFile();

	char n = 'y';
	int number=0;
	while (n=='y') {
		cout << "\nEnter the number you are looking for: ";
		cin >> number;
		if (searchToken(number)==0) {cout << "\nNot in the list!";}
		else cout << "Index: " << searchToken(number);
		cout << "\nAgain?(y/n): ";
		cin >> n;

	}
}

void readFile() {
	for (int i = 0; i < lFactor(); i++) {
		add(getToken());
	}
}

void add(int token) {
	table[hashIt(token)] = token;
	cout << "Added " <<  token << ": " << collisions << " collision(s)\n";
	collisions = 0;
}

int hashIt(int token) {

	int ind = mod(token);//1

	if (table[ind]!=0){
		collisions++;
		ind = dHash(token, sizeof(table)/sizeof(*table));
		if (table[ind]!=0) {
			collisions++;
			ind = quadP(token);
			if (table[ind]!=0) {
				ind = linearP(token);
			}
		}
	}
	return ind;
}

int lFactor() {
	return (70*(sizeof(table)/sizeof(*table))/100);
}

int mod(int token) {
	return (token % (sizeof(table)/sizeof(*table)));
}

int nextLPrime(int prime){
	int ind;
	for (int i=0; i < sizeof(primes)/sizeof(*primes); i++) {
		if (primes[i] == prime) {
			ind = i;
		}
	}

	return(primes[ind-1]);
}

int dHash(int token, int prime) {
	if (table[mod(token)] == 0) {
		return (mod(token));
	}
	else {
		return (nextLPrime(prime)-(token % nextLPrime(prime)));
	}

}

int quadP(int token){

	if (table[mod(token)] == 0) {
		return (mod(token));
	}
	else {
		int index;
		for (int i = 1; i <=3; i++){ 		//We go 3 times only by requirements
			index = mod(token+(i*i));

			if(table[index] == 0) {
				break;
			}
			collisions++;
		}
		return index;
	}

}

int linearP(int token) {
	int ind = mod(token);
	if (table[ind] == 0) {
		return (ind);
	}
	else {
		ind++;
		collisions++;
		while(table[ind]!=0){
			ind++;
			collisions++;
		}
		return ind;
	}
}

int getToken(){
	int token;
	in >> token;
	return token;
}

int searchToken(int token){
	int ind =0;
	for (int i=0; i < sizeof(table)/sizeof(*table); i++ ) {
		if (table[i]==token) ind = i;
	}
	return ind;
}
