//============================================================================
// Name        : Lab11.cpp
// Author      : Vadimir Plagov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Using recursion: Given a number that could be up to 10 digits long, place the commas in the appropriate places
//				 1,087,045

//============================================================================

#include <iostream>
using namespace std;

//prototype
void commas(int n);

int main() {

	long num;
	cout << "Enter a LongInt: "; cin >> num;
	cout << "Fixed: "; commas(num);

}

//definition
void commas(int n){
	if (n/1000 != 0) {
		commas(n/1000);
		cout << ",";
		if (n % 1000 < 100) cout << 0;
		if (n % 1000 < 10) cout << 00;
	}
	cout << n%1000;
}
