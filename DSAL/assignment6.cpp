#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node
{
    T data;
    Node *next;
    Node(T data)
    {
        this->data = data;
        this->next = NULL;
    }

    template <typename U>
    friend class queue;

    template <typename U>
    friend class stack;
};

template <typename T>
class queue
{
    Node<T> *frnt, *rear;

public:
    queue()
    {
        this->frnt = NULL;
        this->rear = NULL;
    }

    void push(T data)
    {
        if (this->frnt)
        {
            this->rear->next = new Node<T>(data);
            this->rear = this->rear->next;
        }
        else
        {
            this->frnt = new Node<T>(data);
            this->rear = this->frnt;
        }
    }

    void pop()
    {
        if (this->frnt)
        {
            if (this->frnt == this->rear)
            {
                delete this->frnt;
                this->frnt = NULL;
                this->rear = NULL;
            }
            else
            {
                Node<T> *temp = this->frnt;
                this->frnt = this->frnt->next;
                delete temp;
            }
        }
    }

    T front()
    {
        if (this->frnt)
        {
            return this->frnt->data;
        }
        else
        {
            return T();
        }
    }

    bool empty() { return this->frnt == 0; }
};

template <typename T>
class stack
{
    Node<T> *tp;

public:
    stack()
    {
        this->tp = NULL;
    }

    void push(T data)
    {
        if (this->tp)
        {
            Node<T> *newNode = new Node<T>(data);
            newNode->next = this->tp;
            this->tp = newNode;
        }
        else
        {
            this->tp = new Node<T>(data);
        }
    }

    void pop()
    {
        if (this->tp)
        {
            Node<T> *temp = this->tp;
            this->tp = this->tp->next;
            delete temp;
        }
    }

    T top()
    {
        if (this->tp)
        {
            return this->tp->data;
        }
        else
        {
            return T();
        }
    }

    bool empty() { return this->tp == 0; }
};

template <typename T>
class GraphNode
{
    T data;
    int id;
    GraphNode<T> *next;

    GraphNode(int id, T data)
    {
        this->id = id;
        this->data = data;
        this->next = NULL;
    }

    template <typename U>
    friend class Graph;
};

template <typename T>
class Graph
{
    GraphNode<T> **adjacencyList;
    int nodes;

public:
    Graph(int cap, T nodes[])
    {
        this->nodes = cap;
        this->adjacencyList = new GraphNode<T> *[cap];
        for (int i = 0; i < cap; i++)
        {
            this->adjacencyList[i] = new GraphNode<T>(i, nodes[i]);
        }
    }

    void addConnection(int id1, int id2)
    {
        GraphNode<T> *last = this->adjacencyList[id1];
        while (last->next)
        {
            if (last->id == id2)
            {
                return;
            }
            last = last->next;
        }
        if (last->id == id2)
        {
            return;
        }
        last->next = new GraphNode<T>(id2, this->adjacencyList[id2]->data);

        last = this->adjacencyList[id2];
        while (last->next)
        {
            if (last->id == id1)
            {
                return;
            }
            last = last->next;
        }
        if (last->id == id1)
        {
            return;
        }
        last->next = new GraphNode<T>(id1, this->adjacencyList[id1]->data);
    }

    void show()
    {
        for (int i = 0; i < this->nodes; i++)
        {
            GraphNode<T> *itr = this->adjacencyList[i];
            while (itr)
            {
                cout << itr->id << ": " << itr->data << " -> ";
                itr = itr->next;
            }
            cout << "X\n";
        }
    }

    void showDegrees()
    {
        int inDegrees[this->nodes];
        int outDegrees[this->nodes];

        for (int i = 0; i < this->nodes; i++)
        {
            inDegrees[i] = 0;
            outDegrees[i] = 0;
        }

        for (int i = 0; i < this->nodes; i++)
        {
            GraphNode<T> *itr = this->adjacencyList[i]->next;
            while (itr)
            {
                outDegrees[i]++;
                inDegrees[itr->id]++;
                itr = itr->next;
            }
        }

        cout << "In Degrees:\n";
        for (int i = 0; i < this->nodes; i++)
        {
            cout << i << ": " << inDegrees[i] << endl;
        }
        cout << "\nOut Degrees:\n";
        for (int i = 0; i < this->nodes; i++)
        {
            cout << i << ": " << outDegrees[i] << endl;
        }
    }

    void searchBFS(int id = 0)
    {
        int visited[this->nodes];
        for (int i = 0; i < nodes; i++)
        {
            visited[i] = 0;
        }
        queue<int> q;
        q.push(id);
        while (1)
        {
            int nodeLeftToVisit = 0;
            for (int i = 0; i < nodes; i++)
            {
                if (visited[i] == 0)
                {
                    nodeLeftToVisit = 1;
                }
            }
            if (nodeLeftToVisit == 0)
            {
                return;
            }

            if (q.empty())
            {
                return;
            }
            int currentNode = q.front();
            visited[currentNode] = 1;
            cout << this->adjacencyList[currentNode]->data << " ";
            q.pop();

            GraphNode<T> *itr = this->adjacencyList[currentNode]->next;
            while (itr)
            {
                if (visited[itr->id] == 0)
                {
                    q.push(itr->id);
                }
                itr = itr->next;
            }
        }
    }

    void searchDFS(int id = 0)
    {
        int visited[this->nodes];
        for (int i = 0; i < nodes; i++)
        {
            visited[i] = 0;
        }
        stack<int> s;
        s.push(id);
        while (1)
        {
            int nodeLeftToVisit = 0;
            for (int i = 0; i < nodes; i++)
            {
                if (visited[i] == 0)
                {
                    nodeLeftToVisit = 1;
                }
            }
            if (nodeLeftToVisit == 0)
            {
                return;
            }

            if (s.empty())
            {
                return;
            }
            int currentNode = s.top();
            visited[currentNode] = 1;
            cout << this->adjacencyList[currentNode]->data << " ";
            s.pop();

            GraphNode<T> *itr = this->adjacencyList[currentNode]->next;
            while (itr)
            {
                if (visited[itr->id] == 0)
                {
                    s.push(itr->id);
                }
                itr = itr->next;
            }
        }
    }

    bool isConnected()
    {
        int visited[this->nodes];
        for (int i = 0; i < nodes; i++)
        {
            visited[i] = 0;
        }
        stack<int> s;
        s.push(0);
        while (1)
        {
            int nodeLeftToVisit = 0;
            for (int i = 0; i < nodes; i++)
            {
                if (visited[i] == 0)
                {
                    nodeLeftToVisit = 1;
                }
            }
            if (nodeLeftToVisit == 0)
            {
                return true;
            }

            if (s.empty())
            {
                return false;
            }
            int currentNode = s.top();
            visited[currentNode] = 1;
            s.pop();

            GraphNode<T> *itr = this->adjacencyList[currentNode]->next;
            while (itr)
            {
                if (visited[itr->id] == 0)
                {
                    s.push(itr->id);
                }
                itr = itr->next;
            }
        }
    }
};

int main()
{
    string nodes[] = {"PICT", "BVP", "Katraj-Dairy", "Lake", "Trimurti"};
    Graph<string> g(5, nodes);

    // G1

    // G2
    g.addConnection(0, 1);
    g.addConnection(1, 2);
    g.addConnection(0, 4);
    g.addConnection(3, 4);

    cout << endl;
    g.show();
    g.showDegrees();

    g.searchBFS();
    cout << endl;
    g.searchDFS();
    cout << endl;

    bool isConnected = g.isConnected();
    cout << (isConnected ? "Connected\n" : "Disjoint\n");
}
