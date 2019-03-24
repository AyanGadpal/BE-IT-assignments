//============================================================================
// Name         : Assingment No. 6 Social Network
// Author       : Ayan Gadpal / 23370 / Batch H11
// Last Updated : 25 / march / 2019
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
#include <stack> 

using namespace std;

// For Graph
class Vertex;
class Edge;

// For Date
class Date;

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

//Vertex of the Graph
class Vertex
{
  public:
	int id;			   // To uniquely Identify every User OR primary key
	char name[20];	 // Name of User
	int comment; // To Account the number of post and comments
	Date DOB;		   // Birth date of user
	Vertex *nextV;	 // Next vertex since SLL is used
	Edge *firstE;	  // First Connection
	bool visited; 
	// Initialization
	Vertex()
	{
		visited = false;
		nextV = NULL;
		firstE = NULL;
		id = comment = 0;
	}
};

class Network
{
  public:
	Vertex *root; // The First User
	int count;	// Total User in Networks

	// Intialization
	Network()
	{
		count = 0;
		root = NULL;
	}

	// Determine Whether the Network Consist of Any user or not
	bool isEmpty()
	{
		if (root == NULL)
			return true;
		return false;
	}

	// Return the address of the Vertex for the specified ID
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

	// Add a Signal User to Existing Network
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

	// Create a new User and take information for it as a input
	void newUser(Vertex *n)
	{
		cout << "\nName : ";
		cin >> n->name;

		// cout << "\nData Of Birth (dd MM yy) :";
		// cin >> n->DOB.dd;
		// cin >> n->DOB.mm;
		// cin >> n->DOB.yy;

		// cout << "\nComments : ";
		// cin >> n->comment;
		sLine();
	}

	// Display the names of user whoes birthday falls in current month
	void checkBD(Date current)
	{
		Vertex *v;
		v = root;

		cout << "\nBirthday In This Month\n";
		while (v != NULL)
		{

			if (v->DOB.thisMonth(current))
				cout << v->name;
			v = v->nextV;
		}
	}

	// To Alter the information for the user already present in the Network
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
			cin >> id; // Taking ID of User whose information is to be altered
			flag = false;

			//Validateing ID
			if (id > count || id < 0)
			{
				flag = true;
				errorMsg("WRONG IDs ENTERED , PLEASE RE-ENTER!");
			}

		} while (flag);

		// Getting the user vertex by id
		vertex = findVertexById(id);

		// Accepting New Name
		cout << "User Details\n"
			 << vertex->name;
		cout << "\nEnter The new Name \n";
		cin >> vertex->name;
	}

	// To Create list of User for network
	void createNetworkNodes()
	{
		int i = 0;
		cout << "\nHow Many User This Network Consist of ? : ";
		cin >> count;

		// 'n' for travelsing , 'pre' for keeping track of the previous node
		Vertex *n, *pre;
		n = new Vertex();
		pre = root = n;

		for (i = 1; i <= count; i++)
		{
			//Creating new User
			cout << "\nEnter The Detail for " << i << " User ";
			newUser(n);

			// Setting ID
			n->id = i;
			pre->nextV = n;
			pre = pre->nextV;
			n = new Vertex();
		}
	}

	// Set Links b/w different users
	void setNetwork()
	{
		bool flag;
		int scrID, desID;
		Vertex *srcVertex, *desVertex;

		//Validation
		if (isEmpty())
		{
			char ch;

			cout << "NO USER FOUND!!\nDo You Want To Add Users Now??(y/n)";
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
			if (scrID > count || desID > count || scrID == desID || scrID <= 0 || desID <= 0)
			{
				flag = true;
				errorMsg("WRONG IDs ENTERED , PLEASE RE-ENTER!");
			}
		} while (flag);

		// Getting Source and Destination Vertex by the ID
		srcVertex = findVertexById(scrID);
		desVertex = findVertexById(desID);

		// Setting the Link B/w them, and also checking Wheather they are aleady friends
		if (setFriend(srcVertex, desVertex))
			setFriend(desVertex, srcVertex);
		else
			errorMsg("ALREADY FRIENDS !");
	}

	// Set The Link / Edge b/w two Users
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
				return false; // Return Flase if Already Friend / Link exist
			while (edge->nextE != NULL)
				edge = edge->nextE; // End of the edge link
			edge->nextE = temp;		// Assinging Edge
		}
		return true;
	}

	// Display The User List with Detail Without Friends
	void displayUser()
	{
		if (isEmpty())
		{
			errorMsg("The Network is Empty!");
			return;
		}
		else
		{
			int i = 0;
			Vertex *v;
			v = root;
			cout << "\n"
				 << setw(3) << "ID" << setw(15) << "USER" << setw(12) << "Birthday"  << setw(9) << "Comments";
			for (i = 1; i <= count; i++)
			{
				sLine();
				cout << "\n"
					 << setw(3) << v->id
					 << setw(15) << v->name
					 << setw(4) << v->DOB.dd << "/" << setw(2) << v->DOB.mm << "/" << setw(2) << v->DOB.yy
					 << setw(9) << v->comment;

				v = v->nextV;
			}
		}
	}

	// Display the Network with Users with Friends without details
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
			sLine();
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

	//Display the Stats such as user with maximum friend
	void stats()
	{
		// Getting Different Stats
		Vertex *maxF = maxFriend();
		Vertex *minF= minFriend();
		Vertex *maxC = maxComments();
		Vertex *minC = minComments();
		//Displaying Them
		sLine();
		cout << "\nMaximum Friend : " << maxF->name 
			 << "\nMinimum Friend : " << minF->name
			 << "\nMaximum Comments : " << maxC->name
			 << "\nMinimum Comments : " << minC->name;
		sLine();
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

		return minV;
	}

	Vertex *maxComments()
	{
		Vertex *v = root, *maxC = root;

		int max = 0;
		;
		while (v != NULL)
		{
			if (v->comment > max)
			{
				max = v->comment;
				maxC = v;
			}
			v = v->nextV;
		}

		return maxC;
	}

	Vertex *minComments()
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
		return maxC;
	}

	void initDFS()
	{
		Vertex *v = root;
		while(v != NULL)
		{
			v->visited = false;
			v = v->nextV;
		}
		DFS(root);
	}

	void DFS(Vertex* temp)
	{
		temp->visited = true;
		cout << " ,"<<temp->name;
		Edge *g = temp->firstE;
		while(g!=NULL)
		{
			if(g->nextV->visited != true)
				DFS(g->nextV);
			g = g->nextE;
		}
	}
};

int main()
{
	int ch = 0;
	Network facebook;		   // Considering facebook using Network to manage there users
	Date current(21, 3, 2019); // FUTURE scope => Take System Date
	while (ch != 9)
	{
		line();
		cout << "\nEnter Your Choice\n"
				"1) Create A new Network \n"
				"2) Make Network (Make Connections/ Friends) \n"
				"3) Access User\n"
				"4) Display User\n"
				"5) Display Network And its Stats\n"
				"6) Add a New User To Network\n"
				"7) Upcoming Birthday\n" 
				"8) DSF"
				"9) EXIT\n"
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
			facebook.initDFS();
			line();
			break;
		case 9:
			line();
			cout << "\n\t\tGOOD BYE\n";
			line();
			break;
		}
	}
	return 0;
}
