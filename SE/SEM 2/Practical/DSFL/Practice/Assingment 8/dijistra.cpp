#include <iostream>

using namespace std;
class Edge;
class Vertex;
class Graph;

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
    Edge()
    {
        nextE = NULL;
        adjacentV = NULL;
        weight = 0;
    }
    Edge(Vertex *v, int w)
    {
        adjacentV = v;
        weight = w;
    }
};

// AN NODE OR VERTEX
class Vertex
{
  public:
    int id;
    Vertex *downlink;
    Edge *firstE;
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

        while (p != NULL)
        {
            cout << "\n " << p->id;
            e = p->firstE;
            while (e != NULL)
            {
                cout << "  " << e->adjacentV->id;
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
        for (i = 1; i <= vertexCount; i++)
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
  
        if (setLink(src, des, w))
            setLink(des, src, w);
        else
        {
            line();
            cout << "Already Link";
            line();
        }
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
            // graph.kruskal();

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