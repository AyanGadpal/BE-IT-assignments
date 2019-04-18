#include <iostream>
#include <fstream>
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
    char name[20];
    int roll;
    Student()
    {
        strcpy(name, "Empty");
        roll = 0;
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

class Filehash
{
  public:
    char filename[25];
    int count;
    fstream file;
    Filehash(const char filename[])
    {
        strcpy(this->filename, filename);
        file.open(filename, ios::in);
        if (file.fail())
        {
            file.close();
            file.open(filename, ios::out | ios::binary);
            Hashrow r;
            int i;
            for (i = 0; i < MAX; i++)
                file.write((char *)&r, sizeof(Hashrow));
            cout << "\nFile Created !";
        }
        file.close();
    }

    void display()
    {
        file.open(filename, ios::in | ios::binary);
        Hashrow r;
        cout << endl
             << setw(2) << "SN"
             << setw(10) << "Name" << setw(7) << "Roll" << setw(5) << "Link";
        for (int i = 0; i < MAX; i++)
        {
            file.read((char *)&r, sizeof(Hashrow));
            cout << endl
                 << setw(2) << i
                 << setw(10) << r.S.name << setw(7) << r.S.roll << setw(5) << r.link;
        }

        file.close();
    }
    void moveP(int i)
    {
        file.seekp(i * sizeof(Hashrow), ios::beg);
    }
    void moveG(int i)
    {
        file.seekg(i * sizeof(Hashrow), ios::beg);
    }
    void insert()
    {
        Hashrow temp, r;
        cout << "\nEnter the Name : ";
        cin >> temp.S.name;
        cout << "\nEnter the Roll No. : ";
        cin >> temp.S.roll;
        int i = hashF(temp.S.roll), k = 0, p = 0;
        if (count <= MAX)
        {
            file.open(filename, ios::in | ios::out | ios::binary);

            moveG(i);
            file.read((char *)&r, sizeof(Hashrow));
            if (r.S.roll == 0)
            {
                file.seekp(i * sizeof(Hashrow), ios::beg);
                file.write((char *)&temp, sizeof(Hashrow));
            }
            else
            {
                /* Linear Probing */

                // Next Empty Location
                k = i % MAX;
                while (r.S.roll != 0)
                {
                    file.read((char *)&r, sizeof(Hashrow));
                    k = k + 1 % MAX;
                }

                // Writing to Empty Location
                moveP(k);
                file.write((char *)&temp, sizeof(Hashrow));

                // Finding End of the Link
                moveG(i);
                file.read((char *)&r, sizeof(Hashrow));
                p = i;
                while (r.link != -1)
                {
                    p = r.link;
                    moveG(p);
                    file.read((char *)&r, sizeof(Hashrow));
                }

                // Linking
                r.link = k;
                moveP(p);
                file.write((char *)&r, sizeof(Hashrow));
            }
            count++;
            file.close();
        }
        else
        {
            cout << "\n FULL!";
        }
    }
};
main()
{
    Filehash F("new.dat");
    int ch;
    while (1)
    {
        cout << "\nEnter the Choice"
                "\n1) Insert Record"
                "\n2) Display Record"
                "\n3) Search Record"
                "\n4) Modify Record"
                "\n5) Exit"
                "\nYour Choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            F.insert();
            break;

        case 2:
            F.display();
            break;

        case 3:
            F.insert();
            break;
        case 4:
            //F.Modify();
            break;
        case 5:
            exit(0);
            break;

        default:
            break;
        }
    }
    return 0;
}
