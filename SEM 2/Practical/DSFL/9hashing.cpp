//============================================================================
// Name        : 9
// Author      : Ayan 23370 H11
// Version     :
// Copyright   : GNU public Libraly
//============================================================================

#include <iostream>
#include <iomanip>
#include <string.h>

#define MAX 30
using namespace std;

inline void line()
{
	cout << "\n=================================================\n";
}
inline void sLine()
{
	cout << "\n------------------------------------------------";
}

inline void errorMsg(const char *msg)
{
	sLine();
	cout << endl
		 << " ERROR : " << msg;
	sLine();
}

int hash(int tel)
{
	return tel%MAX;
}


class Hashrow
{
public:
	char name[30];
	int tel;// Student Data
	int link;
	Hashrow()
	{
		tel = 0;
		link = -1;
		strcpy(name,"EMPTY");

	}


};
class HashTable
{
public:
	Hashrow H[MAX];

	HashTable()
	{

	}

	void display()
	{
		char *name;
		cout<<setw(2)<<"SN"<<setw(20)<<"Name"<<setw(14)<<" Telephone\t\t"<<setw(3)<<"link";
		for(int i = 0;i<30;i++)
		{
			cout<<endl<<setw(2)<<i<<setw(20)<<H[i].name<<setw(10)<<H[i].tel<<"\t"<<setw(3)<<H[i].link;
		}
	}
	// Without Replacement
	void CreaeHashTableNR()
	{
		char name[30];
		int i,tel;
		cout<<"\nEnter The Name : ";
		cin>>name;
		cout<<"\nEnter Telephone No. : ";
		cin>>tel;
		i = hash(tel);
		strcpy(H[i].name,name);
		H[i].tel = tel;

	}

	// With Replacement
	void CreaeHashTableR()
	{
		cout<<"With Replacement";
	}

};



int main() {

	int ch=0;
	bool hChoice;
	HashTable H;
	cout<<hash(45);

	while(ch!=3)
	{
		cout << "\nEnter Your Choice\n"
					"1) Hashing With Replacement \n"
					"2) Hashing Without Replacement \n"
					"3) Exit\n"
					"YOUR CHOICE : ";
		cin>>ch;
		if(ch == 3)
			break;
		hChoice = (ch == 1);
		while(ch != 6)
		{
			line();
			cout<< (hChoice ? "ALGO : With Replacement\n" : " ALGO : Without Replacement");
			cout << "\nEnter Your Choice\n"
					 	"1) Create Hashtable \n"
						"2) Insert \n"
						"3) Create \n"
						"4) Search \n"
						"5) Display \n"
						"6) Exit \n"
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


						break;
					case 3:
						line();

						break;
					case 4:
						line();


						break;
					case 5:
						line();
						H.display();
						break;
					case 9:
						line();
						cout << "\n\t\tGOOD BYE\n";
						line();
						break;
			}

		}

	}


	return 0;
}
