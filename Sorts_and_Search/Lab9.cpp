//============================================================================
// Name        : Lab9.cpp
// Author      : Vladimir PLagov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : SORTS: Bubble(1st column, askending)|Selection(2nd column, deskending)|
//						Shell(3rd column, askending)|Insertion(5th row, askending)
//				 Binary SEARCH(5th row)
//				 ARRAY[5][4]
//				 DON`T forget to create a file in root dir with needed numbers but still [5][4]
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

//Function prototypes
void reset();	//just reads the data from file (NO INVARIANTS)
void display();		//just displays the array a[][]
void swapRows(int row1, int row2); //swap two rows
void swapColumns(int column1, int column2); //swap two columns
void bubbleIt();	//perform the bubble sort on the 1st column in ask ord, keep corresponding items on the rows in askending order
void selection(); 	//perform the selection sort on the 2nd column in desk ord, keep items together
void shellIt();		//perform the shell sort on the 3rd column in ask order, keep items together
void insertion();	//perform the insertion sort on the 5th row in ask order, keep items together within a column
void binaryS(); 	//perform the binary search on the 5th row, display the column with this number

//A global array of int`s
int a[5][4];

int main() {

	reset();

	cout << "Original Array:\n";
	display();

	bubbleIt();

	cout << "1st column is BUBBLE-sorted in ascending order:\n";

	display();

	reset();

	selection();

	cout << "2nd column is sorted by SELECTION in descendig order:\n";

	display();

	reset();

	shellIt();

	cout << "3rd column is sorted by SHELL sorting in ascendig order:\n";

	display();

	reset();

	insertion();

	cout << "5th row is sorted by INSERTION sorting in ascendig order:\n";

	display();

	binaryS();
}

//Function deffinitions
void reset(){
	//Will need the file stream to load the array
	ifstream in("input.txt");

	//Check the file
	if (!in) {
		cout << "Cannot open the input.txt file!";
	}

	for (int i=0; i < 5; i++)
		for (int j=0; j < 4; j++)
			in >> a[i][j];
	in.close();
}
void display(){
	for (int i=0; i < 5; i++) {
		for (int j=0; j < 4; j++)
			cout << a[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
}
void swapRows(int row1, int row2){
	int temp[4];

	//insert row1 into the temp
	for (int i = 0; i < 4; i++) {
		temp[i] = a[row1][i];
	}
	//insert row2 into row1
	for (int i = 0; i < 4; i++) {
		a[row1][i] = a[row2][i];
	}
	//insert temp(row1) into row2
	for (int i = 0; i < 4; i++) {
		a[row2][i] = temp[i];
	}
}

void swapColumns(int column1, int column2){
	int temp[5];

	//insert column1 into the temp
	for (int i = 0; i < 5; i++) {
		temp[i] = a[i][column1];
	}
	//insert column2 into column1
	for (int i = 0; i < 5; i++) {
		a[i][column1] = a[i][column2];
	}
	//insert temp(row1) into row2
	for (int i = 0; i < 5; i++) {
		a[i][column2] = temp[i];
	}
}

void bubbleIt(){
	for (int i = 0; i < (5-1); i++)
		for (int j = 0; j < (5-1); j++) {
			if (a[j][0] > a[j+1][0]) {
				swapRows(j,j+1);
			}
		}
}

void selection(){
	int rowMax = 0;
	for (int i = 0; i < (5-1); i++){
		rowMax = i;
		for (int j = i; j < 5; j++){
			if (a[j][1] > a[rowMax][1]) {
				rowMax = j;
			}
		}
		swapRows(i, rowMax);
	}
}

void shellIt(){
	for (int gap = 5/2; gap > 0; gap /= 2) {
		for (int i = gap; i < 5; i++) {
			for(int j = i; (j >> gap) && (a[j][2]<a[j-gap][2]); j-=gap){
				swapRows(j,j-gap);
			}
		}

	}

}

void insertion(){
	for (int i = 1; i < 4; i++)
		for (int j = i; (j > 0) && (a[4][j] < a[4][j-1]); j--)
			swapColumns(j,j-1);
}

void binaryS(){
	int key;
	cout << "What number are you searching for in the 5th row? Number: "; cin >> key;
	cout << "\n";
	int high = 4-1;
	int low = 0;
	int mid;

	bool flag = false;

	while ((low <= high) && (!flag)) {
		mid = (low+high)/2;
		if (a[4][mid] < key)
			low = low + 1;
		else if (a[4][mid] > key)
			high = mid -1;
		else
			flag = true;
	}

	if(flag) {
		cout << "Column with number 9 in the 5th row:\n";
		for (int i = 0; i < 5; i ++)
			cout << a[i][mid] << "\n";
	}
	else
		cout << "No such number in the 5th row!";
}



