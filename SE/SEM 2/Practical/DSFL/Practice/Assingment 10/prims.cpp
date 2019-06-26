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
    char city[30];
    Vertex *downlink;
    Edge *firstE;
};

class priEdge
{
  public:
    int sv, weight, ev;
};

class Graph
{
  public:
    Vertex *root;
    int vertexCount, EdgeCount, *a;
    Graph()
    {
        root = NULL;
        vertexCount = EdgeCount = 0;
    }
    void unionInit()
    {
        a = new int(vertexCount);
        for (int i = 0; i < vertexCount; i++)
            a[i] = i;
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
        for (i = 0; i < vertexCount; i++)
        {
            n->id = i;
            cout << "\nEnter the city : ";
            cin >> n->city;
            pre->downlink = n;
            pre = pre->downlink; // BUG here clear it
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
        for (i = 0; i < vertexCount; i++)
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
        setLink(des, src, w);
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
    bool isConnected(int x, int y)
    {
        return a[x] == a[y];
    }

    void connect(int x,int y)
    {
        for (int i = 0; i < vertexCount;i++)
        {
            if(a[i]==a[y])
                a[i] = a[x];
        }
    }

    void primns()
    {
        priEdge path;
        unionInit();
        int index = 0;
        Vertex *src, *des;
        int cost = 0;
        while (index != vertexCount - 1) // n-1 iteration
        {
            int mincost = 1000000;
            Vertex *v = root;
            while (v != NULL)
            {
                if (isConnected(v->id, 0))
                {
                    Edge *e;
                    e = v->firstE;
                    while (e != NULL)
                    {
                        if (e->weight < mincost && !isConnected(0, e->adjacentV->id))
                        {
                            path.weight = mincost = e->weight;
                            path.sv = v->id;
                            path.ev = e->adjacentV->id;
                        }
                        e = e->nextE;
                    }
                }
                v = v->downlink;
            }
            connect(0, path.ev);
            src = findVertexById(path.sv);
            des = findVertexById(path.ev);
            cout << endl
                 << src->city << "<--(" << path.weight << ")-->" << des->city;
            cost += path.weight;
            index++;
        }
        cout << "\nCost : " << cost;
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
            graph.primns();

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