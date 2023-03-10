#include <iostream>

using namespace std;

template <typename T>
class ThreadedBinarySearchTree
{
public:
    T data;
    ThreadedBinarySearchTree *l, *r;
    bool rThrd, isEmpty;

    ThreadedBinarySearchTree()
    {
        this->isEmpty = true;
        this->rThrd = false;
        this->r = NULL;
        this->l = NULL;
    }

    ThreadedBinarySearchTree(T data)
    {
        this->isEmpty = false;
        this->data = data;
        this->rThrd = false;
        this->r = NULL;
        this->l = NULL;
    }

    void insert(T data)
    {
        if (this->isEmpty)
        {
            this->isEmpty = false;
            this->data = data;
        }
        else
        {
            if (data < this->data)
            {
                if (this->l)
                {
                    this->l->insert(data);
                }
                else
                {
                    this->l = new ThreadedBinarySearchTree(data);
                    this->l->r = this;
                    this->l->rThrd = true;
                }
            }
            else
            {
                if (this->r && !(this->rThrd))
                {
                    this->r->insert(data);
                }
                else
                {
                    if (this->rThrd)
                    {
                        this->rThrd = false;
                        ThreadedBinarySearchTree *temp = new ThreadedBinarySearchTree(data);
                        temp->rThrd = true;
                        temp->r = this->r;
                        this->r = temp;
                    }
                    else
                    {
                        this->r = new ThreadedBinarySearchTree(data);
                    }
                }
            }
        }
    }

    void show()
    {
        ThreadedBinarySearchTree *current = this;
        while (current->l)
        {
            current = current->l;
        }

        while (current)
        {

            cout << "Node: " << current->data << " Left: ";
            if (current->l)
            {
                cout << current->l->data;
            }
            else
            {
                cout << "NULL";
            }
            cout << " Right: ";
            if (current->r)
            {
                cout << current->r->data;
            }
            else
            {
                cout << "NULL";
            }
            if (current->rThrd)
            {
                cout << " Threaded";
            }
            else
            {
                cout << " Not Threaded";
            }
            cout << "\n";

            if (!(current->l) && !(current->r))
            {
                return;
            }

            if (current->rThrd)
            {
                current = current->r;
            }
            else if (current->r)
            {
                current = current->r;
                while (current->l)
                {
                    current = current->l;
                }
            }
        }
    }

    void preOrder()
    {
        if (this->isEmpty)
        {
            cout << "Empty\n";
        }
        ThreadedBinarySearchTree<T> *current = this;
        while (1)
        {
            cout << current->data << " ";
            if (current->l)
            {
                current = current->l;
            }
            else if (current->r)
            {
                while (current->rThrd)
                {
                    current = current->r;
                }
                if (current->r)
                {
                    current = current->r;
                }
                else
                {
                    return;
                }
            }
            else
            {
                cout << "\n";
                return;
            }
        }
    }

    void remove(T key)
    {
        if (this->isEmpty)
        {
            return;
        }

        ThreadedBinarySearchTree<T> *current = this;
        ThreadedBinarySearchTree<T> *prev = NULL;
        while (1)
        {
            if (current->data == key)
            {
                if (!current->l && (current->rThrd || !current->r))
                {
                    if (current == prev->l)
                    {
                        delete prev->l;
                        prev->l = NULL;
                    }
                    else
                    {
                        ThreadedBinarySearchTree<T> *temp = current->r;
                        delete prev->r;
                        prev->r = temp;
                        if (temp)
                        {
                            prev->rThrd = true;
                        }
                    }
                    return;
                }
                else if (current->l && !current->rThrd && current->r)
                {
                    ThreadedBinarySearchTree<T> *successor = current->r;
                    while (successor->l)
                    {
                        successor = successor->l;
                    }
                    current->data = successor->data;
                    key = successor->data;
                    current = current->r;
                }
                else
                {
                    if (current->l)
                    {
                        current->data = current->l->data;
                        key = current->l->data;
                        current = current->l;
                    }
                    else
                    {
                        current->data = current->r->data;
                        key = current->r->data;
                        current = current->r;
                    }
                }
            }
            else if (current->data < key)
            {
                if (current->r)
                {
                    prev = current;
                    current = current->r;
                }
                else
                {
                    return;
                }
            }
            else
            {
                if (current->l)
                {
                    prev = current;
                    current = current->l;
                }
                else
                {
                    return;
                }
            }
        }
    }
};

int main()
{
    ThreadedBinarySearchTree<int> tbst;

    tbst.insert(5);
    tbst.insert(3);
    tbst.insert(7);
    tbst.insert(2);
    tbst.insert(1);
    tbst.insert(4);
    tbst.insert(9);
    tbst.insert(8);
    tbst.insert(6);
    tbst.insert(10);
    tbst.show();

    tbst.remove(2);
    tbst.show();
    tbst.preOrder();
}
