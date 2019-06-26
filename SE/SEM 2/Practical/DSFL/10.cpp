#pragma endregion//============================================================================
// Name        : Prims
// Author      : Ayan 23370 H11
// Version     : 3
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
    bool prim;
    bool visited;
    int weight;
    Vertex *adjacentV;
    Edge *nextE;
    Edge()
    {
        adjacentV = NULL;
        nextE = NULL;

        weight = 0;
        prim = false;
    }
    Edge(Vertex *next, int eWeight)
    {
        adjacentV = next;
        nextE = NULL;
        weight = eWeight;

        prim = false;
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
    int count;
    Vertex *root;

    Graph()
    {
        root = NULL;
        count = 0;
    }
    bool isEmpty()
    {
        return (root == NULL);
    }

    void defineNodes()
    {
        int i = 0;
        cout << "\nNumber of Graph Nodes : ";
        cin >> count;

        // 'n' for travelsing , 'pre' for keeping track of the previous node
        Vertex *n, *pre;
        n = new Vertex();
        pre = root = n;

        for (i = 1; i <= count; i++)
        {
            // Setting ID
            n->id = i;
            pre->downV = n;
            pre = pre->downV;
            n = new Vertex();
        }
        cout << "DIDI"; 
    }

    Vertex *findVertexById(int id)
    {
        Vertex *vertex;
        vertex = root;
        for (int i = 1; i < count; i++)
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

        if (setLink(srcVertex, desVertex, w))
            setLink(desVertex, srcVertex, w);
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

            for (int i = 0; i < count; i++)
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
    void initvisit()
    {
        Vertex *temp = root;
        while (temp != NULL)
        {
            temp->visited = false;
            temp = temp->downV;
        }
    }

    // Initialize visited flag for all edges
    void initedges()
    {

        Vertex *tempv = root;

        while (tempv != NULL)
        {
            Edge *tempe = tempv->firstE;
            while (tempe != NULL)
            {
                tempe->visited = false;
                tempe = tempe->nextE;
            }
            tempv = tempv->downV;
        }
    }

    int primtraverse()
    {

        Vertex *v = root;

        int cost = 0;

        while (v != NULL)
        {
            Edge *ge = v->firstE;

            while (ge != NULL)
            {
                if (ge->visited == true)
                {
                    cout << "\n"
                         << v->id << " to " << ge->adjacentV->id;
                    cost += ge->weight;
                }
                ge = ge->nextE;
            }
            v = v->downV;
        }
        return cost;
    }
    void prims()
    {
        Vertex *v = root;
        Edge *min = new Edge;

        initvisit();
        initedges();

        int n = 0;

        while (v != NULL)
        {
            v = v->downV;
            n++;
        }

        v = root;
        v->visited = true;

        for (int i = 0; i < n - 1; i++)
        {
            min->weight = 9999; // Some High Value
            v = root;

            while (v != NULL)
            {
                cout << "\n -- 1";

                Edge *ge = v->firstE;

                while (v->visited == true && ge != NULL && ge->visited == false && ge->adjacentV->visited == false)
                {
                    cout << "\n -- 2";
                    if (ge->weight < min->weight)
                    {
                        min = ge;
                        cout << " \n " << min->weight;
                    }
                    ge = ge->nextE;
                }

                min->adjacentV->visited = true;
                min->visited = true;

                v = v->downV;
            }
        }

        int cost = primtraverse();
        cout << "\n Minimal Spanning Tree cost - " << cost;
    }
};
int main()
{
    int ch = 0;
    Graph graph;

    while (ch != 5)
    {
        line();
        cout << "\nEnter Your Choice\n"
                "1) Define Nodes \n"
                "2) Make Network (Make Connections) \n"
                "3) Prims\n"
                "4) Display User\n"
                "5) Exit"
                "\nCHOICE : ";
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
                graph.prims();
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