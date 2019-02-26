//============================================================================
// Name        : socialNetwork.cpp
// Author      : Ayan 23370 H11
// Version     :
// Copyright   : Social Network
// Description :    Consider a friends’ network on face book social web site.
//					Model it as a graph to represent each node as a user and
//					a link to represent the friend relationship between them.
//					Store data such as date of birth, number of comments for
//					each user
//					1.Find who is having maximum friends
//					2.Find who has post maximum and minimum comments
//					3.Find users having birthday in this month.
//============================================================================

#include <iostream>
using namespace std;

class DOB;
class Vertex;
class Edge;

inline void line()
{
	cout<<"\n=======================================\n";
}

class DOB
{
	public:

	int dd,mm,yy;

	DOB()
	{
		dd=mm=yy=0;
	}
	DOB(int dd,int mm,int yy)
	{
		this->dd = dd;
		this->mm = mm;
		this->yy = yy;
	}

};

class Edge
{
	public:
		int weight;
		Vertex *nextV;
		Edge *nextE;
	Edge()
	{

	}


};

class Vertex
{
	public:
		int id;
		char name[20];
		bool visited;
		int post,comment;
		DOB dob;
		Vertex *nextV;
		Edge firstE;
	Vertex()
	{
		nextV = NULL;
	}

};



class Network
{
	public:
		Vertex *root;
		int count;

	Network()
	{
		count = 0;
		root=NULL;
	}

	void addNode()
	{

	}

	void createNetwork()
	{
		int i=0,d,m,y;

		cout<<"\nHow Many User This Network Conist of ? : ";
		cin>>count;

		Vertex *n,*pre;
		n = new Vertex();
		root = n;
		pre = root;


		for(i=1;i<=count;i++)
		{

			cout<<"\nEnter The Detail for "<<i<<" User \nName : ";
			cin>>n->name;
			n->id = i;
			pre->nextV = n;
			pre = pre->nextV;
			n = new Vertex();
			/*cout<<"\nDate Of Birth ";
			cout<<"\nDate :";
			cin>>d;
			cout<<"\nMonth :";
			cin>>m;
			cout<<"\nYear :";
			cin>>y;*/
		}

		n = root;
		int src,des;
		char ch=y;
		while(ch!='n')
		{
			cout<<"\nSet Friendship (Press n to exit) \nSOURCE ID : ";
			cin>>src;
			cout<<"\nDestination ID : ";
			cin>>des;




		}
	}

	void setFriend()
	{

	}

	void display()
	{
		int i=0;
		Vertex *n;
		n = root;
		for(i=1;i<=count;i++)
		{
			cout<<"\n"<<n->id<<") NAME : "<<n->name;
			n = n->nextV;
		}
	}

};

int main()
{
	int ch = 0;
	Network facebook;

	while(ch!=8)
	{
	       	line();
	       	cout<<"\nEnter Your Choice\n"
	       					"1) Create a New Network \n"
	       					"2) Add User To Network\n"
	       			        "3) Access User\n"
	       					"4) Display Network\n"
	       					"5) Set/Reset Users Friendship Strength\n"
	       					"8) EXIT\n"
	       					"YOUR CHOICE : ";
	       			cin>>ch;
	       			switch(ch)
	       			{
						case 1:
								line();
								facebook.createNetwork();
								break;
						case 2:
								line();


								break;
						case 3:
								line();


								break;
						case 4:
								line();
								facebook.display();

								break;
						case 5:
								line();



								break;
						case 6:
								line();

								line();
								break;
						case 7:
								line();

								line();
								break;



						case 8:
								line();
								cout<<"\n\tGOOD BYE\n";
								line();
								break;

	       			}
	}


	return 0;
}

