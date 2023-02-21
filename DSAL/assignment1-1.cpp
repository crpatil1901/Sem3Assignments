#include<iostream>
#include<optional>

using namespace std;

template<typename T>
class BinarySearchTree {

    T data;
    BinarySearchTree<T> *l, *r;
    bool isEmpty;

public:

    BinarySearchTree(T data) {
        this->isEmpty = false;
        this->data = data;
        this->l = NULL;
        this->r = NULL;
    }

    BinarySearchTree() {
        this->isEmpty = true;
        this->l = NULL;
        this->r = NULL;
    }

    void insert(T data) {
        if (this->isEmpty) {
            this->isEmpty = false;
            this->data = data;
        } else {
            if (data < this->data) {
                if (this->l) {
                    this->l->insert(data);
                } else {
                    this->l = new BinarySearchTree(data);
                }
            } else {
                if (this->r) {
                    this->r->insert(data);
                } else {
                    this->r = new BinarySearchTree(data);
                }
            }
        }
    }

    void print() {
        if (!this->isEmpty) {
            if (this->l) {
                this->l->print();
            }
            cout<<this->data<<" ";
            if (this->r) {
                this->r->print();
            }
        } else {
            cout<<"Empty\n";
        }
    }

    void show() {
        if (!this->isEmpty) {
            if (this->l) {
                this->l->show();
            }

            cout<<"Node: "<<this->data<<" Left: ";
            if (this->l) {
                cout<<this->l->data;
            } else {
                cout<<"NULL";
            }
            cout<<" Right: ";
            if (this->r) {
                cout<<this->r->data;
            } else {
                cout<<"NULL";
            }
            cout<<"\n";

            if (this->r) {
                this->r->show();
            }
        } else {
            cout<<"Empty\n";
        }
    }

    int logestPathLength() {
        if (this->isEmpty) {
            return 0;
        } else {
            int ll = 0;
            int rl = 0;

            if (this->l) {
                ll = this->l->logestPathLength();
            }
            if (this->r) {
                rl = this->r->logestPathLength();
            }

            return 1 + (ll > rl ? ll : rl);
        }
    }

    optional<T> getMin() {
        if (this->isEmpty) {
            optional<T> o;
            return o;
        } else {
            BinarySearchTree *itr = this;
            while (itr->l) {
                itr = itr->l;
            }
            return optional(itr->data);
        }
    }

    optional<T> getMax() {
        if (this->isEmpty) {
            optional<T> o;
            return o;
        } else {
            BinarySearchTree *itr = this;
            while (itr->r) {
                itr = itr->r;
            }
            return optional(itr->data);
        }
    }

    void mirror() {
        if (!this->isEmpty) {

            BinarySearchTree *temp = this->l;
            this->l = this->r;
            this->r = temp;

            if (this->r) {
                this->r->mirror();
            }

            if (this->l) {
                this->l->mirror();
            }

        }
    }

    BinarySearchTree* find(T data) {
        if (isEmpty) {
            return NULL;
        } else {
            if (this->data == data) {
                return this;
            } else if (data < this->data) {
                if (this->l) {
                    return this->l->find(data);
                } else {
                    return NULL;
                }
            } else {
                if (this->r) {
                    return this->r->find(data);
                } else {
                    return NULL;
                }
            }
        }
    }
};

int main() {
    BinarySearchTree<int> BST;
    BST.insert(5);
    BST.insert(6);
    BST.insert(8);
    BST.insert(2);
    BST.insert(3);
    BST.insert(1);
    BST.insert(10);
    BST.insert(9);
    BST.show();
    cout<<BST.find(5)<<endl<<BST.find(2)<<endl<<BST.find(19)<<endl;
}
