#include<iostream>
#include"PriorityQ.cpp"
#include <string.h>
using namespace std;

int prioritySetter();

class Patient
{
    public:
       char name[20],number[14];
       int priority;
       int ID;

    Patient()
    {

    }

    //Operator Overload Here
    friend ostream & operator << (ostream &out, const Patient &c);


};

//To handle the 'cout' in the Priority Queue
ostream & operator << (ostream &out, const Patient &c)
{
	out <<endl<<c.ID;
	out <<"\t"<<c.name;
    out <<"\t" << c.number;

    if(c.priority == 3)
    	out << "\tSerious " ;
    else if(c.priority == 2)
    	out << "\tMedium" ;
    else if(c.priority == 1)
    	out << "\tCommon" ;

    return out;
}

class Hospital
{
    private:
        PriorityQ<Patient> Queue;
        static int ID;
    public:
    Hospital()
    {

    }

    void input()
    {
        Patient person;
         bool f;// for Validation
        cout<<"\nEnter the Name : ";
        cin>>person.name;

        do
        {
        	f = false;
        	cout<<"\nEnter the Contact Number : ";
        	cin>>person.number;
            if(strlen(person.number) < 10 || strlen(person.number) >13)
        	{
        	  	f = true;
            	cout<<"\nInvalid Number ! ";
        	}

        }while(f);

        person.ID = ++ID;

        person.priority = prioritySetter();

        Queue.enqueue(person,person.priority);


    }
    void display()
    {
    	if(!Queue.isEmpty())
    	{
    		cout<<"\nID\tName\tNumber\t\tDisease Type\n";
    		Queue.display();
    	}
    	else
    	{
    		cout<<"\nNO MORE PATIENTS";
    	}


    }
    void serve()
    {
    	Patient P;
    	if(!Queue.isEmpty())
    	{
    		P = Queue.dequeue();
    		cout<< P;
    	}
    	else
    	{
    		cout<<"EMPTY";
    	}

    }



    ~Hospital()
    {

    }
};
int Hospital::ID = 0;

int prioritySetter()
{
    int id;
   while(1)
   {
    cout<<"\nChoose the Disease Patient have from below"
          "\n1) Heart Attack"
          "\n2) Lower Respiratory Infections"
          "\n3) Malaria"
          "\n4) Dengu"
          "\n5) Cold"
          "\n6) Cough"
          "\nYour Choice : ";
    cin>>id;

    switch(id)
    {
        case 1:

            return 3;
        break;

        case 2:

            return 3;
        break;

        case 3:

            return 2;
        break;

        case 4:
           return 2;
        break;

        case 5:

            return 1;
         break;

        case 6:

            return 1;
        break;

        default:
            cout<<"\nWrong Choice , Enter AGAIN\n";

        break;
    }
   }

}



void line()
{
	cout<<"\n====================================\n";

}
int main()
{
    Hospital H;
    int ch;

    while(ch!=4)
    {
    	line();
    	cout<<"\nEnter Your Choice\n"
    					"1) Input \n"
    					"2) Display ALL\n"
    					"3) Serve\n"\
    					"4) EXIT\n"
    					"YOUR CHOICE : ";
    			cin>>ch;
    			switch(ch)
    			{
    			case 1:
    					line();
    					H.input();
    					break;
    			case 2:
    					line();
    					H.display();

    					break;
    			case 3:
    					line();
    					H.serve();


    					break;
    			case 4:
    					line();

    					break;

    			}

    }



    return 0;
}
