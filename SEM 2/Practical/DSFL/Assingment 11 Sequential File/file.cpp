// Name        : 11 File
// Author      : Ayan Gadpal 23370 H11
// Version     : 1
// Copyright   : GNU public Libraly

#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>

using namespace std;

inline void sLine()
{
	cout << "\n-------------------------";
}
inline void line()
{
	cout << "\n======================================\n";
}

class File
{
    fstream file;
    char filename[30];

  public:
    File()
    {
    }
    File(const char *filename)
    {
        strcpy(this->filename, filename);
        cout << this->filename << " Is Selected !\n";
    }


    void add()
    {
        file.open(filename, ios::app);
        char name[30];
        int roll;

        cout << "\nEnter the name : ";
        cin >> name;
        cout << "\nEnter the Roll No. : ";
        cin >> roll;

        file << name << " " << roll << "\n";
        file >> name >> roll;
        file.close();
    }
    void display()
    {
        file.open(filename, ios::in);
        char name[30];
        int roll;
      
        file >> name >> roll;
        cout << setw(10) << "NAME"
             << " |" << setw(3) << " ROLL NO.";
        sLine();

        while (!file.eof())
        {
            cout << endl
                 << setw(10) << name << " |" << setw(3) << roll;
            file >> name >> roll;
        }
        file.close();
    }

    int search(int key)
    {
        char name[30];
        int roll;
        int i = 0;
        file.open(filename, ios::in);
        file >> name >> roll;
        if (!file.eof())
            while (!file.eof())
                if (roll == key)
                {
                    cout << "\n Name : " << name << " at " << i;
                    file.close();
                    return i;
                }
                else
                {
                    file >> name >> roll;
                    i++;
                }

        file.close();
        return -1;
    }
    void modify(int position)
    {
        fstream temp;
        char name[30];
        int roll;
        temp.open("temp.txt", ios::out);
        file.open(filename, ios::in);
        int counter = 0;
        while (counter != position)
        {
            file >> name >> roll;
            counter++;
            temp << name << " " << roll << "\n";
        }
        cout << "\nEnter New Record \nName: ";
        cin >> name;
        cout << "\nRoll No. : ";
        cin >> roll;
        temp << name << " " << roll <<"\n";
        file >> name >> roll;
        while (!file.eof())
        {
            file >> name >> roll;
            temp << name << " " << roll << "\n";
        }
        file.close();
        temp.close();
        remove(filename);
        rename("temp.txt", filename);
    }
    void Delete(int position)
    {
        fstream temp;
        char name[30];
        int roll;
        temp.open("temp.txt", ios::out);
        file.open(filename, ios::in);
        int counter = 0;
        
        while (!file.eof())
        {
            if (counter == position)
            {
                file >> name >> roll;
                file >> name >> roll;
            }
            file >> name >> roll;
            counter++;
            temp << name << " " << roll << "\n";
        }
        file.close();
        temp.close();
        remove(filename);
        rename("temp.txt", filename);
    }
};

int main()
{
    int choice = 0, i = 0;
    char name[30];
    cout << "\nEnter File Name : ";
    cin >> name;
    File Student(name);

    while (choice != 6)
    {
        line();
        cout << "\n\nStudent Data Base\n";
        cout << "1) Add Data\n";
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
            cout << "\nNumber of Students :  ";
            cin >> i;
            while (i > 0)
            {
                sLine();
                Student.add();
                i--;
            }

            break;

        case 2:
            Student.display();
            break;

        case 3:
            cout << "Enter Roll Number you want to search:";
            cin >> i;
            if (Student.search(i) == -1)
                cout << "\nERROR : RECORD NOT FOUND !\n";

            break;

        case 4:
            cout << "Enter Roll Number you want to search:";
            cin >> i;
            i = Student.search(i);
            if (i != -1)
                Student.modify(i);
            else
            {
                cout << "\nError : Not FOUND! s\n";
            }

            break;

        case 5:
            cout << "Enter Roll Number you want to Delete:";
            cin >> i;
            i = Student.search(i);
            if (i != -1)
                Student.Delete(i);
            else
            {
                cout << "\nError : Not FOUND! s\n";
            }
            break;

        case 6:
            break;

        default:
            break;
        }
    }

    return 0;
}