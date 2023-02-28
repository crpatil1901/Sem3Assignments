#include <iostream>

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
        } else {
            this->frnt = new Node<T>(data);
            this->rear = this->frnt;
        }
    }
    
    void pop() {
        if (this->frnt) {
            if (this->frnt == this->rear) {
                delete this->frnt;
                this->frnt = NULL;
                this->rear = NULL;
            } else {
                Node<T> *temp = this->frnt;
                this->frnt = this->frnt->next;
                delete temp;
            }
        }
    }
    
    T front() {
        if (this->frnt) {
            return this->frnt->data;
        } else {
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
        } else {
            this->tp = new Node<T>(data);
        }
    }
    
    void pop() {
        if (this->tp) {
            Node<T> *temp = this->tp;
            this->tp = this->tp->next;
            delete temp;
        }
    }
    
    T top() {
        if (this->tp) {
            return this->tp->data;
        } else {
            return T();
        }
    }
    
    bool empty() { return this->tp == 0; }
};

template <typename T>
class BinaryTree
{
    T data;
    BinaryTree *l, *r;
    bool isEmpty;
    
public:
    BinaryTree()
    {
        this->l = NULL;
        this->r = NULL;
        this->isEmpty = true;
    }
    
    BinaryTree(T data)
    {
        this->data = data;
        this->l = NULL;
        this->r = NULL;
    }

    BinaryTree copy() {
        cout<<"copying\n";
        BinaryTree copy;

        queue<BinaryTree<T> *> q;
        q.push(this);
        while (!q.empty()) {
            BinaryTree *current = q.front();
            q.pop();
            copy.insert(current->data);
            if (current->l) { q.push(current->l); }
            if (current->r) { q.push(current->r); }
        }
        return copy;
    }
    
    void erase() {
        if (this->l) {
            this->l->erase();
            delete l;
        }
        if (this->r) {
            this->r->erase();
            delete r;
        }
        this->isEmpty = true;
    }
    
    void insert(T data)
    {
        if (this->isEmpty)
        {
            this->data = data;
            this->isEmpty = false;
        }
        else
        {
            queue<BinaryTree *> q;
            q.push(this);
            while (1)
            {
                BinaryTree *current = q.front();
                q.pop();
                if (current->l)
                {
                    q.push(current->l);
                }
                else
                {
                    current->l = new BinaryTree(data);
                    return;
                }
                if (current->r)
                {
                    q.push(current->r);
                }
                else
                {
                    current->r = new BinaryTree(data);
                    return;
                }
            }
        }
    }
    
    void print()
    {
        if (!this->isEmpty)
        {
            if (this->l)
            {
                this->l->print();
            }
            cout << this->data << " ";
            if (this->r)
            {
                this->r->print();
            }
        }
        else
        {
            cout << "Empty\n";
        }
    }
    
    void show()
    {
        if (!this->isEmpty)
        {
            if (this->l)
            {
                this->l->show();
            }
            cout<<this<<" ";
            cout << "Node: " << this->data << " Left: ";
            if (this->l)
            {
                cout << this->l->data;
            }
            else
            {
                cout << "NULL";
            }
            cout << " Right: ";
            if (this->r)
            {
                cout << this->r->data;
            }
            else
            {
                cout << "NULL";
            }
            cout << "\n";
            
            if (this->r)
            {
                this->r->show();
            }
        }
        else
        {
            cout << "Empty\n";
        }
    }
    
    void inOrder()
    {
        BinaryTree *current = this;
        stack<BinaryTree<T> *> s;
        while (current || !s.empty())
        {
            while (current)
            {
                s.push(current);
                current = current->l;
            }
            if (!s.empty())
            {
                cout << s.top()->data << " ";
                current = s.top()->r;
                s.pop();
            }
        }
        cout << endl;
    }
    
    void preOrder()
    {
        stack<BinaryTree<T> *> s;
        s.push(this);
        while (!s.empty())
        {
            BinaryTree *current = s.top();
            s.pop();
            cout << current->data << " ";
            if (current->r)
            {
                s.push(current->r);
            }
            if (current->l)
            {
                s.push(current->l);
            }
        }
        cout << endl;
    }
    
    void postOrder()
    {
        if (this->isEmpty) {
            return;
        }
        stack<BinaryTree *> s, path;
        BinaryTree *current;
        s.push(this);
        while (!s.empty())
        {
            current = s.top();
            s.pop();
            path.push(current);
            
            if (current->l) {
                s.push(current->l);
            }
            
            if (current->r) {
                s.push(current->r);
            }
            
        }
        
        while (!path.empty()) {
            current = path.top();
            path.pop();
            cout<<current->data<<" ";
        }
    }
    
    void swapNodes() {
        if (this->isEmpty) {
            return;
        } else {
            BinaryTree *temp = this->l;
            this->l = this->r;
            this->r = temp;
            
            if (this->l) {
                this->l->swapNodes();
            }
            
            if (this->r) {
                this->r->swapNodes();
            }
        }
    }

    int height() {
        if (this->isEmpty) {
            return 0;
        }
        int lHeight = 0;
        int rHeight = 0;
        if (this->l) {
            lHeight = this->l->height();
        }

        if (this->r) {
            rHeight = this->r->height();
        }

        return 1 + (lHeight > rHeight ? lHeight : rHeight);
    }

    int leafNodeCount() {
        if (this->isEmpty) {
            return 0;
        }
        if (this->l || this->r) {
            int leafNodeCount = 0;
            if (this->l) {
                leafNodeCount += this->l->leafNodeCount();
            }
            if (this->r) {
                leafNodeCount += this->r->leafNodeCount();
            }
            return leafNodeCount;
        } else {
            return 1;
        }
    }
};

int main() {
    BinaryTree<int> bt;
    bt.insert(1);
    bt.insert(2);
    bt.insert(3);
    bt.insert(4);
    bt.insert(5);
    bt.insert(6);
    bt.insert(7);
    bt.insert(8);
    bt.insert(9);
    
    bt.show();
    cout<<endl;
    BinaryTree<int> bt2 = bt.copy();
    bt2.show();
    
    bt.erase();
    bt.show();    
}
