//============================================================================
// Name        : Kruskal
// Author      : Ayan 23370 H11
// Version     : 4
// Copyright   : GNU public Libraly
//============================================================================

#include <iostream>
#include <iomanip>

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

class Vertex;
class Edge;
class Edge
{
  public:
    bool visited;
    int weight;
    Vertex *adjacentV;
    Edge *nextE;
    bool krus;
    Edge()
    {
        adjacentV = NULL;
        nextE = NULL;
       
        visited = false;
        weight = 0;
        krus = false;
    }
    Edge(Vertex *next, int eWeight)
    {
        adjacentV = next;
        visited = false;
    
        
        nextE = NULL;
        weight = eWeight;
        
    }
};

class Vertex
{
  public:
    int id;
    Vertex *downV; // Next vertex since SLL is used
    Edge *firstE;  // First Connection
    bool visited;
    
    // Initialization
    Vertex()
    {
        visited = false;
        downV = NULL;
        firstE = NULL;
        
    }
};

class Graph
{
  public:
    int vertexCount,edgeCount;
    Vertex *root;

    Graph()
    {
        root = NULL;
        vertexCount = edgeCount = 0;
    }
    bool isEmpty()
    {
        return (root == NULL);
    }

    void defineNodes()
    {
        int i = 0;
        cout << "\nNumber of Graph Nodes : ";
        cin >> vertexCount;

        // 'n' for travelsing , 'pre' for keeping track of the previous node
        Vertex *n, *pre;
        n = new Vertex();
        pre = root = n;

        for (i = 1; i <= vertexCount; i++)
        {
            // Setting ID
            n->id = i;
            pre->downV = n;
            pre = pre->downV;
            n = new Vertex();
        }
    }

    Vertex *findVertexById(int id)
    {
        Vertex *vertex;
        vertex = root;
        for (int i = 1; i < vertexCount; i++)
        {
            if (id == i)
                break;
            vertex = vertex->downV;
        }
        return vertex;
    }

    void setConnection()
    {
        int scrID, desID, w;
        Vertex *srcVertex, *desVertex;
        display();
        cout << "\n Source : ";
        cin >> scrID;
        cout << "\nDestination : ";
        cin >> desID;
        cout << "\nWeight : ";
        cin >> w;

        // Getting Source and Destination Vertex by the ID
        srcVertex = findVertexById(scrID);
        desVertex = findVertexById(desID);

        // Validation 

        if (setLink(srcVertex, desVertex, w))
        {
            setLink(desVertex, srcVertex, w);
            edgeCount++;
        }
        else
            errorMsg("ALREADY LINK !");

    }

    bool setLink(Vertex *srcVertex, Vertex *desVertex, int w)
    {
        Edge *temp, *edge;
        edge = srcVertex->firstE;
        temp = new Edge(desVertex, w);
        if (edge == NULL)
            srcVertex->firstE = temp;
        else
        {
            if (edge->adjacentV == desVertex)
                return false; // Return Flase if Already Friend / Link exist
            while (edge->nextE != NULL)
                edge = edge->nextE; // End of the edge link
            edge->nextE = temp;     // Assinging Edge
        }
        return true;
    }

    void display()
    {
        if (isEmpty())
        {
            errorMsg("The Graph is Empty!");
            return;
        }
        else
        {
            Vertex *vertex;
            Edge *edge;
            vertex = root;
            //Table HEADING columb
            cout << "\n"
                 << setw(3) << "ID\t"
                 << "Adjacent Nodes";

            for (int i = 0; i < vertexCount; i++)
            {
                sLine();
                cout << endl
                     << setw(4) << vertex->id
                     << "\t\t";
                edge = vertex->firstE;
                while (edge != NULL)
                {
                    cout << "(" << edge->adjacentV->id << " ," << edge->weight << ")";
                    edge = edge->nextE;
                }
                vertex = vertex->downV;
            }
        }
    }
    void initkrus()
    {
       
        Vertex *tempv = root;
        
        while(tempv != NULL)
        {
            Edge *tempe = tempv->firstE;
            while(tempe != NULL)
            {
                tempe->krus = false;
                tempe = tempe->nextE;
            }	
            tempv = tempv->downV;
        }
    }
    void DFS(Vertex* temp)
    {
        temp->visited = true;
        cout << temp->id << " ";
        Edge *g = temp->firstE;
        while(g!=NULL)
        {
            if(g->nextE->visited != true)
                DFS(g->adjacentV);
            g = g->nextE;
        }
    }

// Kruskal traversal
void krustraverse(Vertex* tempv)
{
	while(tempv != NULL)
	{
		Edge *tempe = tempv->firstE;
		while(tempe != NULL)
		{
			if(tempe->krus == true)
				cout<<"\n "<<tempv->id<<" - "<<tempe->adjacentV->id;
			tempe = tempe->nextE;
		}	
		tempv = tempv->downV;
	}
}

// Detect Cycle
bool checkcycle(Vertex* curr)
{
	curr->visited = true;
	Vertex *next = NULL;

	Edge* g = curr->firstE;
	Edge* tempe;

	while(g!=NULL)
	{
		if(g->adjacentV->visited == false && g->visited == false && g->krus == true)
		{	
			g->visited = true;
			next = g->adjacentV;
			tempe = next->firstE;

			while(tempe != NULL)
			{
				if(tempe->adjacentV->id == curr->id)
				{
					tempe->visited = true;
					break;
				}
				tempe = tempe->nextE; 	
			}

			return checkcycle(g->adjacentV);
		}
		else if(g->visited == false && g->adjacentV->visited == true && g->krus == true)
			return true;

		g = g->nextE;
	}
    return false;
}
void swap(Edge *xp, Edge *yp) 
{ 
    Edge temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void initvisit()
{
	Vertex *temp = root;
	while(temp != NULL)
	{
		temp->visited = false;
		temp= temp->downV;
	}
}

// Initialize visited flag for all edges
void initedges()
{
	
	Vertex *tempv = root;
	
	while(tempv != NULL)
	{
		Edge *tempe = tempv->firstE;
		while(tempe != NULL)
		{
			tempe->visited = false;
			tempe = tempe->nextE;
		}	
		tempv = tempv->downV;
	}
}


    void kruskal()
    {
        
        Vertex *v = root;
        Vertex *temp = NULL;
        Edge *tempe;

        Edge *gearr[30];
        int index = 0, n=0;

        initvisit();
        initedges();

        while(v!=NULL)
        {
            Edge *ge = v->firstE;
            
            while(ge != NULL && ge->visited == false)
            {
                gearr[index] = ge;
                index++;
                temp = ge->adjacentV;
                tempe = temp->firstE;
                
                while(tempe != NULL)
                {
                    if(tempe->adjacentV->id == v->id)
                    {
                        tempe->visited = true;
                        break;
                    }
                    tempe = tempe->nextE; 	
                }
                ge = ge->nextE; 
            }
            v = v->downV;
        }

        // bubble sort
        int i, j;
        n = index; 
        for (i = 0; i < n; i++)       
        // Last i elements are already in place    
        for (j = 0; j < n-i-1; j++)  
            if (gearr[j]->weight > gearr[j+1]->weight) 
                swap(gearr[j], gearr[j+1]); 

        for(int i = 0; i<n; i++)
        {
            cout<<" "<<gearr[i]->weight;
        }

        int cost = 0;

        initkrus();

        for(int i = 0; i<n; i++)
        {
            Vertex *tempv = root;
            
            while(tempv != NULL)
            {
                Edge *tempe = tempv->firstE;
                while(tempe != NULL)
                {
                    if(gearr[i]->weight == tempe->weight && gearr[i]->adjacentV->id == tempe->adjacentV->id)
                    {
                        tempe->krus = true;
                        cost+=tempe->weight;

                        initvisit();
                        initedges();
                        if(checkcycle(root))
                        {	
                            cout<<"\n in - "<<i;
                            tempe->krus = false;
                            cost-=tempe->weight;
                        }	

                        break;
                    }

                    tempe = tempe->nextE;
                }	
                tempv = tempv->downV;
            }
        }

        krustraverse(root);
        cout<<"\n Minimal Spanning Tree cost - "<<cost;
    }
};


int main()
{
    int ch;
    Graph graph;
    graph.defineNodes();
    graph.setConnection();
    graph.display();

    while (ch != 9)
    {
        line();
        cout << "\nEnter Your Choice\n"
                "1) Define Nodes \n"
                "2) Make Network (Make Connections) \n"
                "3) Diplay\n"
                "4) Kruskal\n"
                "5) Exit\nCHOICE : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            line();
            graph.defineNodes();
            break;
        case 2:
            line();
            graph.setConnection();

            break;
        case 3:
            line();
            graph.display();
            break;
        case 4:
            line();
            graph.kruskal();

            break;
        case 5:
            line();
            cout << "\n\t\tGOOD BYE\n";
            line();
            break;
        }
    }

    return 0;
}