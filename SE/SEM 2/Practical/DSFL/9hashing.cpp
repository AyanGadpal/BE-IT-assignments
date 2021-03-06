//============================================================================
// Name        : 9
// Author      : Ayan 23370 H11
// Version     : 2
// Copyright   : GNU public Libraly
//============================================================================

#include <iostream>
#include <iomanip>
#include <string.h>

#define MAX 10
using namespace std;

inline void line()
{
	cout << "\n======================================\n";
}
inline void sLine()
{
	cout << "\n--------------------------------------";
}

inline void errorMsg(const char *msg)
{
	sLine();
	cout << endl
		 << " ERROR : " << msg;
	sLine();
}
inline void title(const char *msg)
{
	line();
	cout << msg;
	line();
}

int HashFuct(int tel)
{
	return tel % MAX;
}

class Hashrow
{
  public:
	char name[30];
	int tel; // Student Data
	int link;
	Hashrow()
	{
		tel = 0;
		link = -1;
		strcpy(name, "EMPTY");
	}
};
class HashTable
{
  public:
	Hashrow H[MAX];
	int count;
	HashTable()
	{
		count = 0;
	}
	bool isFull()
	{
		return count == MAX;
	}
	void display()
	{
		cout << setw(2) << "SN" << setw(15) << "Name" << setw(14) << " Telephone	" << setw(4) << "link";
		for (int i = 0; i < MAX; i++)
		{
			cout << endl
				 << setw(2) << i << setw(15) << H[i].name << setw(10) << H[i].tel << "\t" << setw(3) << H[i].link;
		}
	}
	// Without Replacement
	void CreaeHashTableNR()
	{
		int n;
		sLine();
		cout << "\nNumber of Records : ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			InsertNR();
		}
	}

	void InsertNR()
	{
		char name[30];
		Hashrow temp;
		int i, tel, n;
		cout << "\nEnter The Name : ";
		cin >> name;
		cout << "\nEnter Telephone No. : ";
		cin >> tel;
		i = HashFuct(tel);
		n = i;
		if (!isFull())
		{
			while (1)
			{
				if (H[i].tel == 0) // Found Empty
				{
					strcpy(H[i].name, name);
					H[i].tel = tel;
					count++;
					return;
				}
				if (H[i].tel % MAX == n)
				{
					temp = H[i];
					strcpy(H[i].name, name);
					H[i].tel = tel;
				}
				else
				{
					i = (i + 1) % MAX;
					H[n].link = i;
				}
			}
		}
		else
			errorMsg("Hash Table Is Full!");
	}

	void Search()
	{
		int ph, i;
		cout << "\nEnter the Phone Number Of Person you want to Search\n";
		cin >> ph;
		i = HashFuct(ph);

		if (H[i].tel == 0)
		{
			cout << "\nRecord Not Present\n";
			return;
		}

		do
		{
			if (H[i].tel == ph)
			{
				cout << "Record found !! \n Name is : " << H[i].name;
				return;
			}
			i = H[i].link;
		} while (i != -1);

		cout << "\nRecord Is not Present !";
	}
	// With Replacement
	void CreaeHashTableR()
	{
		int n;
		sLine();
		cout << "\nNumber of Records : ";
		cin >> n;
		for (int i = 0; i < n; i++)
			InsertR();
	}
	void InsertR()
	{
		char name[30];
		int i, tel, link;
		cout << "\nEnter The Name : ";
		cin >> name;
		cout << "\nEnter Telephone No. : ";
		cin >> tel;
		i = HashFuct(tel);
		if (!isFull())
		{
			//Find next Empty location
			int empty = i;
			while (H[empty].tel != 0)
			{
				empty = (empty + 1) % MAX;
			}
			if (H[i].tel != 0)
			{
				if (HashFuct(H[i].tel) == i) // Chaining
				{

					for (link = i; H[link].link != -1; link = H[link].link)
						;
					H[link].link = empty;
					H[empty].tel = tel;
					strcpy(H[empty].name, name);
				}
				else // Replacement
				{
					// Replace
					H[empty].tel = H[i].tel;
					strcpy(H[empty].name, H[i].name);
					link = 0;

					//Finding Previous Link
					for (link = 0; H[link].link != i; link++)
						;

					if (H[i].link == -1)
						H[link].link = empty; //reLinking
					else
						H[link].link = H[i].link;

					// Finding Ending Link
					for (link = i; H[link].link != -1; link = H[link].link)
						;

					//ReLinking
					H[link].link = empty;

					// Entering Record
					H[i].tel = tel;
					H[i].link = -1;
					strcpy(H[i].name, name);
				}
			}
			else
			{
				H[i].tel = tel;
				strcpy(H[empty].name, name);
			}
		}

		else
			errorMsg("Hash Table Is Full!");
	}
};

int main()
{

	int ch = 0;
	bool hChoice;
	HashTable H;

	while (ch != 3)
	{
		cout << "\nEnter Your Choice\n"
				"1) Hashing With Replacement \n"
				"2) Hashing Without Replacement \n"
				"3) Exit\n"
				"YOUR CHOICE : ";
		cin >> ch;
		if (ch == 3)
			break;
		hChoice = (ch == 1);
		while (ch != 6)
		{
			line();
			title(hChoice ? "ALGO : With Replacement Menu\n" : " ALGO : Without Replacement Menu");
			cout << "\nEnter Your Choice\n"
					"1) Insert Record/s \n"
					"2) Search \n"
					"3) Display \n"
					"4) Exit \n"
					"YOUR CHOICE : ";
			cin >> ch;
			line();
			switch (ch)
			{
			case 1:
				line();
				hChoice ? H.CreaeHashTableR() : H.CreaeHashTableNR();
				break;

			case 2:
				line();
				H.Search();
				break;

			case 3:
				line();
				H.display();
				break;
			}
		}
	}
	return 0;
}
