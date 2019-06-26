#include <iostream>
#include <queue>
using namespace std;
class Vertex;
class Network;
class Edge;

class Edge
{
  public:
    Edge *nextEdge;
    Vertex *adjacentV;
    Edge()
    {
        nextEdge = NULL;
        adjacentV = NULL;
    }
    Edge(Vertex *v)
    {
        adjacentV = v;
        nextEdge = NULL;
    }
};
class Vertex
{
  public:
    //User Data
    int id;

    // Vertex Data
    Vertex *downlink;
    Edge *firstEdge;
    bool visited;
    Vertex()
    {
        id = 0;
        downlink = NULL;
        firstEdge = NULL;
        visited = false;
    }
    Vertex(int id)
    {
        this->id = id;
        downlink = NULL;
        firstEdge = NULL;
        visited = false;
    }
};

class Network
{
  public:
    int count;
    Vertex *root;
    Network()
    {
        count = 0;
        root = NULL;
    }
    bool isEmpty()
    {
        return root == NULL;
    }

    void insert(int id)
    {
        Vertex *v = new Vertex(id), *temp = root;
        if (isEmpty())
            root = v;
        else
        {
            while (temp->downlink != NULL)
                temp = temp->downlink;
            temp->downlink = v;
        }
        count++;
    }
    void init()
    {
        Vertex *v = root;
        while (v != NULL)
        {
            v->visited = false;
            v = v->downlink;
        }
    }
    void display()
    {
        int i;
        Vertex *v = root;
        Edge *e;
        for (i = 0; i < count; i++)
        {
            cout << "\n"
                 << v->id;
            e = v->firstEdge;
            while (e != NULL)
            {
                cout << " " << e->adjacentV->id;
                e = e->nextEdge;
            }

            v = v->downlink;
        }
    }

    Vertex *findVertexById(int id)
    {
        Vertex *v = root;
        for (int i = 0; i < id - 1; i++)
            v = v->downlink;
        return v;
    }

    void setConnection()
    {
        /* make two user friend */

        // Display users
        display();
        int srcID, desID;
        Vertex *src, *des;

        // Input
        cout << "\nSource : ";
        cin >> srcID;
        cout << "\nDestination : ";
        cin >> desID;

        // finding user vertex via their id
        src = findVertexById(srcID);
        des = findVertexById(desID);

        // Establishing Link
        if (setLink(src, des))
            setLink(des, src);
    }

    bool setLink(Vertex *src, Vertex *des)
    {
        Edge *d = new Edge(des), *e;
        e = src->firstEdge;
        if (e == NULL)
            src->firstEdge = d;
        else
        {
            if (e->adjacentV == des)
            {
                cout << "\n Already Friend !";
                return false;
            }
            while (e->nextEdge != NULL)
                e = e->nextEdge;
            e->nextEdge = d;
        }
        return true;
    }

    void DFS()
    {
        init();
        DFS(root);
    }
    void DFS(Vertex *v)
    {
        v->visited = true;
        cout << " " << v->id;
        Edge *g = v->firstEdge;

        while (g != NULL)
        {
            if (g->adjacentV->visited != true)
                DFS(g->adjacentV);
            g = g->nextEdge;
        }
    }
    void BFS()
    {
        queue<Vertex *> q;
        Vertex *t;
        t = root;
        t->visited = true;
        q.push(t);

        while (!q.empty())
        {
            t = q.front();
            cout << " " << t->id;
            q.pop();
            Edge *e = t->firstEdge;
            while (e != NULL)
            {
                if (!e->adjacentV->visited)
                {
                    q.push(e->adjacentV);
                    e->adjacentV->visited = true;
                }
                e = e->nextEdge;
            }
        }
    }
};

int main()
{
    Network F;
    int n, ch;
    while (1)
    {
        cout << "\nEnter the Choice"
                "\n1) Create Network"
                "\n2) Display Network"
                "\n3) Make Friend"
                "\n4) DFS"
                "\n5) BFS"
                "\nYour Choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\nEnter the No. of Vertex :";
            cin >> n;
            for (int i = 1; i <= n; i++)
            {
                F.insert(i);
            }
            break;

        case 2:
            F.display();
            break;

        case 3:
            F.setConnection();
            break;
        case 4:
            F.DFS();
            break;
        case 5:
            F.BFS();
            break;

        default:
            break;
        }
    }

    return 0;
}