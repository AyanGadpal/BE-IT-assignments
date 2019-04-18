#include <iostream>
#include <iomanip>
#include <string.h>
#define MAX 10
using namespace std;

int hashF(int i)
{
    return i % MAX;
}

class Student
{
  public:
    char name[30];
    int tel;
    Student()
    {
        strcpy(name, "Empty");
        tel = 0000;
    }
    Student(char name[], int tel)
    {
        strcpy(this->name, name);
        this->tel = tel;
    }
};

class Hashrow
{
  public:
    Student S;
    int link;
    Hashrow()
    {
        link = -1;
    }
};

class Hashtable
{
  public:
    Hashrow H[MAX];
    int count;
    Hashtable()
    {
        count = 0;
    }
    void display()
    {
        cout << endl
             << setw(2) << "SN"
             << setw(10) << "Name" << setw(7) << "Tele" << setw(5) << "Link";
        for (int i = 0; i < MAX; i++)
            cout << endl
                 << setw(2) << i
                 << setw(10) << H[i].S.name << setw(7) << H[i].S.tel << setw(5) << H[i].link;
    }

    // With Replacement

    void insert()
    {
        Student S;
        cout << "\nEnter the Name : ";
        cin >> S.name;
        cout << "\nEnter the Telephone : ";
        cin >> S.tel;
        int i = hashF(S.tel), k = 0;
        if (count <= MAX)
        {
            if (H[i].S.tel == 0)
                H[i].S = S;
            else if (H[i].S.tel % MAX == i)
            {
                /* Linear Probing */

                // Next Empty Location
                k = i + 1 % MAX;
                while (H[k].S.tel != 0)
                {
                    k = k + 1 % MAX;
                }
                H[k].S = S;

                // End of the Link
                while (H[i].link != -1)
                    i = H[i].link;

                // Linking
                H[i].link = k;
            }
            else //Replacement
            {
                // Next Empty Location
                k = i + 1 % MAX;
                while (H[k].S.tel != 0)
                {
                    k = k + 1 % MAX;
                }

                int preI = H[i].S.tel % MAX;
                while (H[preI].link != i)
                    preI = H[preI].link;

                H[preI].link = H[i].link;

                while (H[preI].link != -1)
                    preI = H[preI].link;

                H[k] = H[i];
                H[k].link = -1;
                H[preI].link = k;

                H[i].S = S;
                H[i].link = -1;
            }
            count++;
        }
        else
        {
            cout << "\n FULL!";
        }
    }
};

int main()
{
    Hashtable H;
    int ch;
    while (1)
    {
        cout << "\nEnter the Choice"
                "\n1) Insert Record"
                "\n2) Display Record"
                "\n3) Search Record"
                "\nYour Choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            H.insert();
            break;

        case 2:
            H.display();
            break;

        case 3:
            H.insert();
            break;

        default:
            break;
        }
    }
    return 0;
}