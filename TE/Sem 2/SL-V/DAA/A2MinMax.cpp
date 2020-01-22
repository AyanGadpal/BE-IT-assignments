//=================================================================================
// Name        : A2 SL-V DAA MinMax
// Author      : Ayan Gadpal 33308
// Version     : 1.0
// Copyright   : GNU Public License
// Date        : 22 Jan 2020
// Description : Use Divied and conqure to reduce the comparition in MinMax by 2/3 n
//=================================================================================

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

class Array
{
private:
	int *array;
	int n;
	int min, max;
	int count;

public:
	Array()
	{
		n = 0;
		count = 0;
	}
	// int getMin()
	// {
	// 	return()
	// }
	void findMinMax()
	{
		cout << "Got in 1st";
		if (n == 1)
		{
			min = max = 0;
		}
		else if (n == 2)
		{
			if (array[0] > array[1])
			{
				min = 1;
				max = 0;
			}
			else
			{
				min = 0;
				max = 1;
			}
			
		}
		else
			findMinMax(0, n - 1, &min, &max);
		cout << "\n\nMIN " << array[min];
		cout << "\n\nMAX " << array[max] << endl;
	}
	void findMinMax(int i, int j, int *min, int *max)
	{
		int Rmin, Rmax, Lmin, Lmax;
		count++;
		cout << endl
			 << "\n\nPASS " << count << " " << i << " <---> " << j;
		showPass(i, j);
		if (i + 1 == j)
		{

			if (array[i] > array[j])
			{
				*min = j;
				*max = i;
			}
			else
			{
				*min = i;
				*max = j;
			}
			cout << "\nLeaf Compare MIN: " << array[*min] << " MAX: " << array[*max];
		}
		else
		{
			int m = (i + j) / 2;
			cout << "\nDIVIDING " << i << " to " << m << " AND " << m + 1 << " to " << j;
			findMinMax(i, m, &Rmin, &Rmax);
			findMinMax(m + 1, j, &Lmin, &Lmax);
			*min = array[Rmin] < array[Lmin] ? Rmin : Lmin;
			*max = array[Rmax] < array[Lmax] ? Lmax : Rmax;
		}
		cout << "\nMerging : MIN: " << array[*min] << " MAX: " << array[*max];
	}
	void takeInput()
	{
		while (1)
		{
			cout << "Enter the size of array in power of 2 : ";
			cin >> n;
			if (ceil(log2(n)) == floor(log2(n)))
				break;
			cout << "Input size must be power of 2!\n";
			// TODO VALIDIATION OF INPUT SIZE == 2^k
		}
		array = new int[n];
		for (int i = 0; i < n; i++)
		{
			cout << "Enter " << i + 1 << " Element : ";
			cin >> array[i];
		}
	}
	void showPass(int i, int j)
	{
		cout << "[";
		cout << array[i];
		for (i += 1; i <= j; i++)
			cout << ", " << array[i];
		cout << " ]";
	}
	void Display()
	{
		for (int i = 0; i < n; i++)
			cout << endl
				 << i + 1 << " Element : " << array[i];
	}
};

int main()
{
	Array Arr;
	Arr.takeInput();
	Arr.Display();
	Arr.findMinMax();

	return 0;
}
