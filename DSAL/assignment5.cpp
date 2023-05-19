#include <iostream>
#include <string.h>

using namespace std;

template <typename k, typename v>
class Node
{
    k key;
    v value;
    Node<k, v> *next;

    Node(k key, v value)
    {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }

    template <typename x, typename y>
    friend class Dictionary;
};

int hasher(string key)
{
    int hash = 0;
    int i = 0;
    while (key[i] != 0)
    {
        hash += key[i++];
    }
    return hash % 7;
}

template <typename k, typename v>
class HashTable
{
    Node<k, v> **hashTable;

public:
    HashTable()
    {
        this->hashTable = new Node<k, v> *[7];
    }
    void show()
    {
        for (int i = 0; i < 7; i++)
        {
            cout << i << ": ";
            Node<k, v> *itr = hashTable[i];
            while (itr)
            {
                cout << itr->key << ": " << itr->value << " -> ";
                itr = itr->next;
            }
            cout << "X\n";
        }
    }

    void insert(k key, v value)
    {
        int hash = hasher(key);
        if (this->hashTable[hash] == NULL)
        {
            this->hashTable[hash] = new Node<k, v>(key, value);
        }
        else
        {
            Node<k, v> *itr = this->hashTable[hash];
            while (itr->next)
            {
                if (itr->key == key)
                {
                    throw -1;
                }
                itr = itr->next;
            }
            itr->next = new Node<k, v>(key, value);
        }
    }

    v search(k key)
    {
        int hash = hasher(key);
        Node<k, v> *itr = this->hashTable[hash];
        while (itr)
        {
            if (itr->key == key)
            {
                return itr->value;
            }
            itr = itr->next;
        }
        throw -1;
    }

    void remove(k key)
    {
        int hash = hasher(key);
        if (this->hashTable[hash])
        {
            if (this->hashTable[hash]->key == key)
            {
                this->hashTable[hash] = this->hashTable[hash]->next;
            }
            else
            {
                Node<k, v> *itr = this->hashTable[hash];
                while (itr->next)
                {
                    if (itr->next->key == key)
                    {
                        Node<k, v> *temp = itr->next;
                        itr->next = itr->next->next;
                        delete temp;
                        return;
                    }
                    itr = itr->next;
                }
                throw -1;
            }
        }
    }
};

int main()
{
    HashTable<string, string> dict;
    int c;
    string k, v;
    string menu = "1. Insert Key-Value Pair\n2. Delete Key-Value Pair\n3. Find Key\n4. Show Hash Table\nPress anything else to exit.\nEnter your choice: ";
    while (1)
    {
        cout << menu;
        cin >> c;
        cout << endl;
        switch (c)
        {
        case 1:
            cout << "Enter key: ";
            getchar();
            getline(cin, k);
            cout << "Enter value: ";
            getline(cin, v);
            try
            {
                dict.insert(k, v);
            }
            catch (int e)
            {
                cout << "Key already exists\n";
            }
            break;
        case 2:
            cout << "Enter key: ";
            getchar();
            getline(cin, k);
            try
            {
                dict.remove(k);
            }
            catch (int e)
            {
                cout << "Key doesn't exists\n";
            }
            break;
        case 3:
            cout << "Enter key: ";
            getchar();
            getline(cin, k);
            try
            {
                cout << "Value for the key " << k << " is " << dict.search(k) << endl;
            }
            catch (int e)
            {
                cout << "Key doesn't exists\n";
            }
            break;
        case 4:
            cout << endl;
            dict.show();
            cout << endl;
            break;
        default:
            return 0;
        }
    }
}