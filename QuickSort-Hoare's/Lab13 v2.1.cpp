//============================================================================
// Name        : Lab13.cpp
// Author      : Vladimir Plagov
// Version     : 2.0
// Copyright   :
// Description : Quick Sort using Hoare`s algorithm | JUST ARRAYS
//============================================================================

#include <iostream>
using namespace std;
//global array
int a [] = { 16, 3, 77, 40, 100};

//function definitions
int partition(int iO, int iF);
void swap(int iO, int iF);
void traverse();
void quickSort(int first, int last);

int main() {

	int len = sizeof(a)/sizeof(a[0]);

	cout << len-1;
	cout << "Initial Array: "; traverse();
	quickSort(0, 4);
	cout << "\nQuickSorted Array: "; traverse();
}

int partition(int iO, int iF) {

	int pivot = iO;
	int low = iO + 1;
	int high = iF;

	while (low <= high) {

		while (a[high]>=a[pivot] && low <=high)
			high -= 1;
		if (high < low )
			break;

		swap(high, pivot);
		pivot = high;
		high--;

		while (a[low] <= a[pivot] && low <= high)
			low =+1;
		if (high < low )
			break;

		swap(low, pivot);
		pivot = low;
		low++;
	}

	return pivot;
}

void swap(int iO, int iF){
	int temp = a[iO];
	a[iO] = a[iF];
	a[iF] = temp;
}

void traverse(){
	int len = sizeof(a)/sizeof(a[0]);
	for(int i = 0; i < len; i++)
		cout << a[i] << " ";
}

void quickSort(int first, int last){
	int pivotInd;

	if (first>=last) {
		return;
	}

	pivotInd = partition(first, last);
	quickSort(first, pivotInd-1);
	quickSort(pivotInd+1, last);
}
