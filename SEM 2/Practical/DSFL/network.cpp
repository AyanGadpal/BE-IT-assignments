//============================================================================
// Name         : Assingment No. 6 Social Network
// Author       : Ayan Gadpal / 23370 / Batch H11
// Last Updated : 20 / march / 2019
// Description  :    Consider a friends network on facebook social web site.
//				 	 Model it as a graph to represent each node as a user and
//					 a link to represent the friend relationship between them.
//				 	 Store data such as date of birth, number of comments for
//				 	 each user
//				 	 1.Find who is having maximum friends
//					 2.Find who has post maximum and minimum comments
//					 3.Find users having birthday in this month.
// Solution	    :
//============================================================================

#include <iostream>
#include <iomanip>

using namespace std;

// For Graph
class Vertex;
class Edge;

// For Managing User Information
class UserInfo;
class Date;

inline void line()
{
	cout << "\n============================================\n";
}
inline void Sline()
{
	cout << "\n--------------------------------------------";
}

class Date
{
  public:
	int dd, mm, yy;
	Date()
	{
		dd = mm = yy = 0;
	}
	Date(int dd, int mm, int yy)
	{
		this->dd = dd;
		this->mm = mm;
		this->yy = yy;
	}

	bool thisMonth(Date date)
	{
		return (mm == date.mm);
	}
};

// class UserInfo
// {
//   public:
// };

class Edge
{
  public:
	bool present;
	Vertex *nextV;
	Edge *nextE;
	Edge()
	{
		nextV = NULL;
		nextE = NULL;
		present = false;
	}
	Edge(Vertex *next)
	{
		nextV = next;
		nextE = NULL;
	}
};

class Vertex
{
  public:
	int id;
	char name[20];
	bool visited;
	int post, comment;
	Date DOB;
	Vertex *nextV;
	Edge *firstE;

	// Initialization
	Vertex()
	{
		nextV = NULL;
		firstE = NULL;
		visited = false;
		id = comment = post = 0;
	}
};

class Network
{
  public:
	Vertex *root;
	int count;

	// Network();

	// //General Function
	// bool isEmpty();
	// Vertex *findVertexById(int);

	//User (Vertex) Operations
	// void addUser();
	// void newUser(Vertex *);
	// void accessUser();

	// //Network Related (Graph)
	// void createNetworkNodes(); // Define a new Network's Node in LL format
	// void setNetwork(); // Accept the source and Destination id's and do validation
	// void setFriend(int , int , Vertex *, Vertex *); // Set the link b/w source and Destination
	// void displayNetwork(); // Display User List With Friends
	// void displayUser(); // Display User List with Details (Without Friends)
	// void checkBD();

	Network()
	{
		count = 0;
		root = NULL;
	}

	bool isEmpty()
	{
		if (root == NULL)
			return true;
		return false;
	}

	Vertex *findVertexById(int id)
	{
		Vertex *vertex;
		vertex = root;
		for (int i = 1; i < count; i++)
		{
			if (id == i)
				break;
			vertex = vertex->nextV;
		}
		return vertex;
	}

	void addUser()
	{
		Vertex *v, *p;
		v = new Vertex();
		cout << "\nEnter The Info for the New User\n";
		newUser(v);
		v->id = ++count;
		p = root;
		while (p->nextV != NULL)
			p = p->nextV;
		p->nextV = v;
	}

	void newUser(Vertex *n)
	{
		cout << "\nName : ";
		cin >> n->name;
		cout << "\nData Of Birth (dd MM yy) :";
		cin >> n->DOB.dd;
		cin >> n->DOB.mm;
		cin >> n->DOB.yy;
		cout << "\nPost : ";
		cin >> n->post;
		cout << "\nComments : ";
		cin >> n->comment;
	}

	void checkBD(Date current)
	{
		Vertex *v;
		v = root;

		cout << "\nBirthday In This Month\n";
		while (v != NULL)
		{

			if (v->DOB.thisMonth(current))
			{
				cout << v->name;
			}
			v = v->nextV;
		}
	}

	void accessUser()
	{
		int id = 0;
		Vertex *vertex;
		bool flag;
		do
		{
			cout << "\nPlease Select the id of user you want to access\n";
			displayUser();
			cout << "\nID : ";
			cin >> id;
			flag = false;
			if (id > count || id < 0)
			{
				flag = true;
				cout << "\nERROR : Wrong Id ,please Re-Enter\n";
			}
		} while (flag);
		vertex = findVertexById(id);
		cout << "User Details\n"
			 << vertex->name;
		cout << "\nEnter The new Name \n";
		cin >> vertex->name;
	}

	void createNetworkNodes()
	{
		int i = 0;

		cout << "\nHow Many User This Network Consist of ? : ";
		cin >> count;

		Vertex *n, *pre;
		n = new Vertex();
		pre = root = n;

		for (i = 1; i <= count; i++)
		{

			cout << "\nEnter The Detail for " << i << " User ";
			newUser(n);
			// Setting ID
			n->id = i;
			pre->nextV = n;
			pre = pre->nextV;
			n = new Vertex();
		}
	}

	void setNetwork()
	{
		bool flag;
		int scrID, desID;
		Vertex *srcVertex, *desVertex;

		//Validation
		if (isEmpty())
		{
			char ch;
			cout << "NO User FOUND!!\nDo You Want To Add Users Now??(y/n)";
			cin >> ch;
			if (ch == 'y')
				createNetworkNodes();
			else
				return;
		}

		cout << "Enter The source and Destination ID \nof friends (src,des) \n";
		displayUser();

		//Validation
		do
		{
			flag = false;
			cout << "\nSOURCE : ";
			cin >> scrID;
			cout << "\nDestination : ";
			cin >> desID;
			//Validation
			if (scrID > count || desID > count || scrID == desID)
			{
				flag = true;
				cout << "ERROR Wrong IDs!";
				return; 
			}
		} while (flag);

		srcVertex = findVertexById(scrID);
		desVertex = findVertexById(desID);

		if (setFriend(srcVertex, desVertex))
			setFriend(desVertex, srcVertex);
		else
			cout << "\nERROR : ALREADY FRIENDS";
	}

	bool setFriend(Vertex *srcVertex, Vertex *desVertex)
	{
		Edge *temp, *edge;
		edge = srcVertex->firstE;
		temp = new Edge(desVertex);
		if (edge == NULL)
			srcVertex->firstE = temp;
		else
		{
			if (edge->nextV == desVertex)
				return false;
			while (edge->nextE != NULL)
				edge = edge->nextE;
			edge->nextE = temp;
		}
		return true;
	}

	void displayUser()
	{
		if (isEmpty())
		{
			cout << "EMPTY!";
			return;
		}
		else
		{
			int i = 0;
			Vertex *v;
			v = root;
			cout << "\n"
				 << setw(3) << "ID" << setw(15) << "USER" << setw(12) << "Birthday" << setw(5) << "Post" << setw(9) << "Comments";
			for (i = 1; i <= count; i++)
			{
				cout << "\n"
					 << setw(3) << v->id
					 << setw(15) << v->name
					 << setw(4) << v->DOB.dd << "/" << setw(2) << v->DOB.mm << "/"<< setw(2) << v->DOB.yy
					 << setw(5) << v->post << setw(9) << v->comment;

				v = v->nextV;
			}
		}
	}

	void displayNetwork()
	{
		Vertex *vertex;
		Edge *edge;
		vertex = root;
		//Table HEADING columb
		cout << "\n"
			 << setw(3) << "ID" << setw(11) << " USER" << setw(14) << "FRIENDSS";

		for (int i = 0; i < count; i++)
		{
			Sline();
			cout << endl
				 << setw(4) << vertex->id
				 << setw(10) << vertex->name
				 << "\t\t";
			edge = vertex->firstE;
			while (edge != NULL)
			{
				cout << edge->nextV->name << ",";
				edge = edge->nextE;
			}
			vertex = vertex->nextV;
		}
	}

	void stats()
	{
		Vertex *maxFiend = maxFriend();
		Vertex *minFiend = minFriend();
		Vertex *maxPost = maxPosts();
		Vertex *maxComments = minComments();
	}

	Vertex *maxFriend()
	{
		Vertex *v = root, *maxV = root;
		Edge *e;
		int max = 0, fcount;
		while (v != NULL)
		{
			fcount = 0;
			e = v->firstE;
			while (e != NULL)
			{
				fcount++;
				e = e->nextE;
			}
			if (fcount > max)
			{
				max = fcount;
				maxV = v;
			}
			v = v->nextV;
		}

		cout << "\nGot Max Friends : " << maxV->name;
		return maxV;
	}

	Vertex *minFriend()
	{
		Vertex *v = root, *minV = root;
		Edge *e;
		int min = 10000, fcount;
		while (v != NULL)
		{
			fcount = 0;
			e = v->firstE;
			while (e != NULL)
			{
				fcount++;
				e = e->nextE;
			}
			if (fcount < min)
			{
				min = fcount;
				minV = v;
			}
			v = v->nextV;
		}

		cout << "\nGot Min Friends : " << minV->name;
		return minV;
	}

	Vertex* maxPosts()
	{
		Vertex *v = root, *maxP = root;

		int max = 0;
		;
		while (v != NULL)
		{			
			if (v->post > max)
			{
				max = v->post;
				maxP = v;
			}
			v = v->nextV;
		}

		cout << "\nGot Max Post : " << maxP->name;
		return maxP;
	}

	Vertex* minComments()
	{
		Vertex *v = root, *maxC = root;

		int min = 10000;
		;
		while (v != NULL)
		{			
			if (v->comment < min)
			{
				min = v->comment;
				maxC = v;
			}
			v = v->nextV;
		}

		cout << "\nGot min Commetns : " << maxC->name;
		return maxC;

	}
};

int main()
{
	int ch = 0;
	Network facebook;		   // Considering facebook using Network to manage there users
	Date current(21, 3, 2019); // FUTURE scope => Take System Date
	while (ch != 8)
	{
		line();
		cout << "\nEnter Your Choice\n"
				"1) Create A new Network \n"
				"2) Make Network (Make Connections) \n"
				"3) Access User\n"
				"4) Display User\n"
				"5) Display Network And its Stats\n"
				"6) Add a New User To Network\n"
				"7) Upcoming Birthday\n"
				"8) EXIT\n"
				"YOUR CHOICE : ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			line();
			facebook.createNetworkNodes();
			break;
		case 2:
			line();
			facebook.setNetwork();

			break;
		case 3:
			line();
			facebook.accessUser();
			break;
		case 4:
			line();
			facebook.displayUser();

			break;
		case 5:
			line();
			facebook.displayNetwork();
			facebook.stats();
			break;
		case 6:
			line();
			facebook.addUser();
			line();
			break;
		case 7:
			line();
			facebook.checkBD(current);
			line();
			break;

		case 8:
			line();
			cout << "\n\t\tGOOD BYE\n";
			line();
			break;
		}
	}
	return 0;
}
