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
    bool present,visited;
    int weight;
    Vertex *adjacentV;
    Edge *nextE;
    Edge()
    {
        adjacentV = NULL;
        nextE = NULL;
        present = false;
        visited = false;
        weight = 0;
    }
    Edge(Vertex *next, int eWeight)
    {
        adjacentV = next;
        visited = false;
        .0
        
        nextE = NULL;
        weight = eWeight;
        present = false;
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

    void kruskal()
    {
        Edge **sortedEdge;
        sortedEdge = new Edge*[edgeCount];
        Vertex *v = root;
        int i=0;
        Edge *e = v->firstE;
        while (v != NULL)
        {
            while(e != NULL)
            {
                sortedEdge[i] = e;
                i++;
                e = e->nextE;
                cout << "\n Edge ADDED ! ";
            }
            v = v->downV;
            e = v->firstE;
        }
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
                "3) Krushkal User\n"
                "4) Display User\n"
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