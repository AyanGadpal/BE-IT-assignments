
//=================================================================================
// Name        : 1 SL-V
// Author      : Ayan Gadpal 33308
// Version     : 1.0
// Copyright   : GNU Public License
// Date 	   : 18 Dec 2019
// Description : Merge Sort
//=================================================================================

#include <iostream>
#include <fstream>
using namespace std;

int count = 0;

void merge(int arr[], int l, int m, int r)
{
	// Length of both side
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	int i, j, k;

	// Copy Left
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];

	// Copy Right
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = j = 0;
	k = l;

	// Copy Data from left and right in Ascending order in Original
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
			arr[k] = L[i], i++;
		else
			arr[k] = R[j], j++;

		k++;
	}

	// Copy Rest from Left
	while (i < n1)
		arr[k] = L[i], k++, i++;

	// Copy Rest from Right
	while (j < n2)
		arr[k] = R[j], k++, j++;
}

// Array ,left , right
void mergeSort(int A[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2; // Middle

		// Left , Right
		mergeSort(A, l, m), mergeSort(A, m + 1, r);

		// Merging
		merge(A, l, m, r);
	}
}

void inputArray(int A[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		cout << "\nEnter the " << i << "th number :", cin >> A[i];
}

void displayArray(int A[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		cout << endl
			 << i << "th :" << A[i];
}

void writeFile(int A[], int n)
{
	ofstream file;
	file.open("Result.txt");
	int i;
	if (file)
	{
		for (i = 0; i < n; i++)
			file << "\n"
				 << i << ") " << A[i];
		file.close();
	}
	else
		cout << "\nERROR : File not opened !\n";
}

int main()
{
	int A[10], n = 10;

	// Taking Input and Displaying afterwards
	inputArray(A, n);
	displayArray(A, n);

	// Applying Merge Sort
	mergeSort(A, 0, n);

	// Display Sorted Array
	cout << "\nAfter Sorting count = " << count << "\n";
	displayArray(A, n);

	// Write to the file
	writeFile(A,n);

	return 0;
}
