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
    int cost;
    GraphNode<T> *next;

    GraphNode(int id, int cost, T data)
    {
        this->id = id;
        this->cost = cost;
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
            this->adjacencyList[i] = new GraphNode<T>(i, 0, nodes[i]);
        }
    }

    void addConnection(int id1, int id2, int cost)
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
        last->next = new GraphNode<T>(id2, cost, this->adjacencyList[id2]->data);

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
        last->next = new GraphNode<T>(id1, cost, this->adjacencyList[id1]->data);
    }

    void show()
    {
        for (int i = 0; i < this->nodes; i++)
        {
            GraphNode<T> *itr = this->adjacencyList[i];
            while (itr)
            {
                cout << itr->id << ": " << itr->data << " $" << itr->cost << " -> ";
                itr = itr->next;
            }
            cout << "X\n";
        }
    }

    void primsMST()
    {
        int visited[this->nodes];
        int includedPaths[this->nodes - 1];
        int includedPathsCount = 0;
        int includedPathsNodeID1[this->nodes - 1];
        int includedPathsNodeID2[this->nodes - 1];
        for (int i = 0; i < nodes; i++)
        {
            visited[i] = 0;
        }
        int smallestPathLen = 99999, smallestPathNodeID1 = -1, smallestPathNodeID2 = -1;
        for (int i = 0; i < nodes; i++)
        {
            GraphNode<T> *itr = this->adjacencyList[i]->next;
            while (itr)
            {
                if (itr->cost < smallestPathLen)
                {
                    smallestPathLen = itr->cost;
                    smallestPathNodeID1 = i;
                    smallestPathNodeID2 = itr->id;
                }
                itr = itr->next;
            }
        }

        includedPathsNodeID1[includedPathsCount] = smallestPathNodeID1;
        includedPathsNodeID2[includedPathsCount] = smallestPathNodeID2;
        visited[smallestPathNodeID1] = 1;
        visited[smallestPathNodeID2] = 1;
        includedPaths[includedPathsCount++] = smallestPathLen;

        while (includedPathsCount < (this->nodes - 1))
        {
            int nextPathLen = 9999;
            int alreadyConnectedNodeID = -1;
            int nextConnectedNodeID = -1;

            for (int i = 0; i < this->nodes; i++)
            {
                if (visited[i])
                {
                    GraphNode<T> *itr = this->adjacencyList[i]->next;
                    while (itr)
                    {
                        if (itr->cost < nextPathLen && visited[itr->id] == 0)
                        {
                            nextPathLen = itr->cost;
                            alreadyConnectedNodeID = i;
                            nextConnectedNodeID = itr->id;
                        }
                        itr = itr->next;
                    }
                }
            }
            includedPathsNodeID1[includedPathsCount] = alreadyConnectedNodeID;
            includedPathsNodeID2[includedPathsCount] = nextConnectedNodeID;
            visited[nextConnectedNodeID] = 1;
            includedPaths[includedPathsCount++] = nextPathLen;
        }

        int totalCost = 0;

        cout << "MST:\nFrom\tTo\tCost\n";

        for (int i = 0; i < this->nodes - 1; i++)
        {
            int id1 = includedPathsNodeID1[i];
            int id2 = includedPathsNodeID2[i];
            for (int j = 0; j < this->nodes; j++)
            {
                if (adjacencyList[j]->id == id1)
                {
                    cout << adjacencyList[j]->data << "\t";
                }
            }
            for (int j = 0; j < this->nodes; j++)
            {
                if (adjacencyList[j]->id == id2)
                {
                    cout << adjacencyList[j]->data << "\t";
                }
            }
            cout << includedPaths[i] << "\n";
            totalCost += includedPaths[i];
        }
        cout << "Total Cost of MST is " << totalCost << ".\n";
    }
};

int main()
{
    string nodes[] = {"A", "B", "C", "D", "E"};
    Graph<string> g(5, nodes);

    // G
    g.addConnection(0, 1, 4);
    g.addConnection(0, 2, 3);
    g.addConnection(0, 3, 2);
    g.addConnection(1, 2, 3);
    g.addConnection(1, 4, 6);
    g.addConnection(2, 3, 4);
    g.addConnection(2, 4, 5);

    g.show();
    cout << endl;
    g.primsMST();
}