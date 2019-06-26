#include <iostream>
#include <iomanip>
using namespace std;
class Edge;
class Vertex;
class Graph;

int *a, size;

inline void line()
{
    cout << "\n==================================\n";
}

// BASIC EDGE
class Edge
{
  public:
    Edge *nextE;
    Vertex *adjacentV;
    int weight;
    bool visited;
    Edge()
    {
        nextE = NULL;
        adjacentV = NULL;
        weight = 0;
        visited = false;
    }
    Edge(Vertex *v, int w)
    {
        nextE = NULL;
        adjacentV = v;
        weight = w;
        visited = false;
    }
};

// AN NODE OR VERTEX
class Vertex
{
  public:
    int id;
    Vertex *downlink;
    Edge *firstE;
    bool visited;
    Vertex()
    {
        downlink = NULL;
        firstE = NULL;
        id = 0;
        visited = false;
    }
};

class kruEdge
{
  public:
    int sv, ev;
    int weight;
    kruEdge()
    {
        sv = ev = 0;
        weight = 0;
    }
};

class Graph
{
  public:
    Vertex *root;
    int vertexCount, EdgeCount;
    Graph()
    {
        root = NULL;
        vertexCount = EdgeCount = 0;
    }
    bool isEmpty()
    {
        return root == NULL;
    }
    void defineNodes()
    {
        Vertex *pre, *n;
        int i;
        cout << "\nNumber of graph nodes : ";
        cin >> vertexCount;
        n = new Vertex();
        pre = root = n;
        for (i = 1; i <= vertexCount; i++)
        {
            n->id = i;
            pre->downlink = n;
            pre = pre->downlink;
            n = new Vertex();
        }
    }
    void display()
    {
        Vertex *p;
        Edge *e;
        if (isEmpty())
        {
            cout << "\nITS EMPTY !";
            return;
        }
        p = root;
        cout << setw(3) << "ID" << setw(10) << "link";
        while (p != NULL)
        {
            cout << "\n"
                 << setw(3) << p->id;
            e = p->firstE;
            while (e != NULL)
            {
                cout << setw(6) << "(" << e->adjacentV->id << "," << e->weight << "),";
                e = e->nextE;
            }
            p = p->downlink;
        }
    }

    Vertex *findVertexById(int id)
    {
        int i;
        Vertex *v;
        v = root;
        for (i = 1; i
         <= vertexCount; i++)
        {
            if (i == id)
                break;
            v = v->downlink;
        }
        return v;
    }
    void setConnection()
    {
        int scrID, desID, w, i;
        Vertex *src, *des;
        cout << "\nEnter Source : ";
        cin >> scrID;
        cout << "\nEnter Destination : ";
        cin >> desID;
        cout << "\nEnter the Weight : ";
        cin >> w;
        src = findVertexById(scrID);
        des = findVertexById(desID);
        setLink(src, des, w);
    }

    bool setLink(Vertex *s, Vertex *d, int w)
    {
        Edge *edge, *temp;
        temp = new Edge(d, w);
        edge = s->firstE;
        if (edge == NULL)
            s->firstE = temp;
        else
        {
            if (edge->adjacentV == d)
                return false;
            while (edge->nextE != NULL)
            {

                edge = edge->nextE;
                if (edge->adjacentV == d)
                    return false;
            }

            edge->nextE = temp;
        }
        return true;
    }

    void initV()
    {
        Vertex *p;
        Edge *e;
        p = root;
        while (p != NULL)
        {
            p->visited = false;
            e = p->firstE;
            while (e != NULL)
            {
                e->visited = false;
                e = e->nextE;
            }
            p = p->downlink;
        }
    }

    void unionInit(int n)
    {
        a = new int(n);
        size = n;
        for (int i = 0; i < n; i++)
            a[i] = i;
    }

    bool isConnected(int x, int y)
    {
        return (a[x] == a[y]);
    }
    void connect(int x, int y)
    {
        int p = a[x];
        int q = a[y];
        for (int i = 0; i <size; i++)
            if (a[i] == p)
                a[i] = q;
    }

    void kruskal()
    {
        kruEdge k[30];
        Vertex *v;
        Edge *e;
        int index = 0;
        initV();
        v = root;

        while (v != NULL) // Putting all the edges in our array
        {
            e = v->firstE;
            while (e != NULL && e->visited == false)
            {
                k[index].sv = v->id;
                k[index].weight = e->weight;
                k[index].ev = e->adjacentV->id;
                e = e->nextE;
                index++;
            }
            v = v->downlink;
        }

        //bubble sort
        int i, j, n = index;
        kruEdge temp;
        for (i = 0; i < n; i++)
            for (j = 0; j < n - i - 1; j++)
                if (k[j].weight > k[j + 1].weight)
                {
                    //Swapping
                    temp = k[j];
                    k[j] = k[j + 1];
                    k[j + 1] = temp;
                }

        cout << "\nSorted Edges Are : ";
        cout << "\n"
             << "SV"
             << " | "
             << "W"
             << " | "
             << "EV";
        for (i = 0; i < n; i++)
        {
            cout << "\n"
                 << k[i].sv << " | " << k[i].weight << " | " << k[i].ev;
        }

        //Cycle Detection
        int cost = 0;
        unionInit(n);
        kruEdge ke;
        for (int i = 0; i < n -1; i++)
        {
            ke = k[i];
            if (!isConnected(ke.sv, ke.ev))
            {
                connect(ke.sv,ke.ev);
                cout << "\nEdge " << i << " = " << ke.sv << "-----<" << ke.weight << ">------" << ke.ev;
                cost += ke.weight;
            }
        }
        cout << "\nCost : "<<cost;
    }
};

int main()
{

    int ch;
    Graph graph;

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
            exit(0);
            cout << "\n\t\tEXITING\n";
            line();
            break;
        }
    }

    return 0;
}