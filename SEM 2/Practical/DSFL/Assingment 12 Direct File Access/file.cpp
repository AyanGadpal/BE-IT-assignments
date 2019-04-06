// Name        : 11 File
// Author      : Ayan Gadpal 23370 H11
// Version     : 1
// Copyright   : GNU public Libraly

#include <bits/stdc++.h>
#include <fstream>
#define MAX 10
using namespace std;

inline void sLine()
{
    cout << "\n-------------------------";
}
inline void line()
{
    cout << "\n======================================\n";
}

struct Student
{
    int id;
    char name[25];
    int roll;
};

class Hashrow
{
  public:
    Student s;
    int link;
    Hashrow()
    {

        link = -1;
    }
};

class HashTable
{
    int hash;
    char filename[25];
    fstream f;

  public:
    HashTable(int h, const char *fname)
    {
        strcpy(filename, fname);
        hash = h;
        f.open(filename, ios::in);
        if (f.fail())
        {
            f.close();
            f.open(filename, ios::out | ios::binary);
            Hashrow temp;
            temp.s.id = temp.s.roll = -1;
            strcpy(temp.s.name, "EMPTY");
            for (int i = 0; i < hash; i++)
                f.write((char *)&temp, sizeof(Hashrow));
        }
        f.close();
    }
    void insert(int key)
    {
        int i = key % hash;
        f.open(filename, ios::in | ios::out | ios::binary);
        f.seekg(i * sizeof(Hashrow), ios::beg);
       
        Hashrow t;
        f.read((char *)&t, sizeof(HT));
        if (t.s.roll == -1) 
        {
            f.seekp(i * sizeof(HT), ios::beg);
            t.s = data;
            t.link = -1;
            f.write((char *)&t, sizeof(t));
            f.close();
            return 0;
        }
        else
        {
            /* Linear Probing */
            int empty = i + 1;
            f.seekp(empty * sizeof(HT), ios::beg);
            while ( t.s.roll != -1)
			{
				empty = (empty + 1) % MAX;
			}
            

        }
        

        f.close();
    }
    void display()
    {
        f.open(filename, ios::in);
        Hashrow temp;

        while (!f.eof())
        {
            f.read((char *)&temp, sizeof(Hashrow));
            cout << temp.s.id << temp.s.name << temp.s.roll << endl;
        }
    }
};

int main()
{
    int choice = 0, i = 0;
    char name[30];
    cout << "\nEnter File Name : ";
    cin >> name;
    HashTable H(20, "YO.dat");
    H.display();

    while (choice != 6)
    {
        line();
        cout << "\n\nStudent Data Base\n";
        cout << "1) Insert\n";
        cout << "2) Display all records\n";
        cout << "3) Search for a record\n";
        cout << "4) Modify a record\n";
        cout << "5) Delete a record\n";
        cout << "6) Exit\nYour Choice : ";
        cin >> choice;
        line();
        switch (choice)
        {
        case 1:

            break;

        case 2:
            // Student.display();
            break;

        case 3:
            // cout << "Enter Roll Number you want to search:";
            // cin >> i;
            // if (Student.search(i) == -1)
            //     cout << "\nERROR : RECORD NOT FOUND !\n";

            break;

        case 4:
            // cout << "Enter Roll Number you want to search:";
            // cin >> i;
            // i = Student.search(i);
            // if (i != -1)
            //     Student.modify(i);
            // else
            // {
            //     cout << "\nError : Not FOUND! s\n";
            // }

            break;

        case 5:
            // cout << "Enter Roll Number you want to Delete:";
            // cin >> i;
            // i = Student.search(i);
            // if (i != -1)
            //     Student.Delete(i);
            // else
            // {
            //     cout << "\nError : Not FOUND! s\n";
            // }
            break;

        case 6:
            break;

        default:
            break;
        }
    }

    return 0;
}
