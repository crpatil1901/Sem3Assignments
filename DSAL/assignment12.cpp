#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int hasher(int key)
{
    return key % 7;
}

template <typename k, typename v>
class Node
{
    public:
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
    friend class HashTable;
};

template <typename k, typename v>
class HashTable
{
    public:
    Node<k, v> **hashTable;
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
                    return;
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

class Record {
    public:
    int id;
    string name;
    string experience;
    float salary;

    Record(int id, string name, string experience, float salary) {
        this->id = id;
        this->name = name;
        this->experience = experience;
        this->salary = salary;
    }

    string toString() {
        return to_string(this->id) + "," + this->name + "," + this->experience + "," + to_string(this->salary);
    }

    Record(string record) {
        int i = 0;
        string temp = "";
        while (record[i] != ',') {
            temp += record[i++];
        }
        this->id = stoi(temp);
        temp = "";
        i++;
        while (record[i] != ',') {
            temp += record[i++];
        }
        this->name = temp;
        temp = "";
        i++;
        while (record[i] != ',') {
            temp += record[i++];
        }
        this->experience = temp;
        temp = "";
        i++;
        while (record[i] != 0) {
            temp += record[i++];
        }
        this->salary = stof(temp);
    }

    void print() {
        cout << "ID: " << this->id << endl;
        cout << "Name: " << this->name << endl;
        cout << "Experience: " << this->experience << endl;
        cout << "Salary: " << this->salary << endl << endl;
    }
};

template <typename T>
class DirectAccessFile {
    string fileName;;
    HashTable<int, int> hashTable;

public:
    DirectAccessFile(string fileName) {
        this->fileName = fileName;
        ifstream file(fileName);
        int loc;
        if (file.is_open()) {
            int id;
            loc = file.tellg();
            string line;
            while (getline(file, line)) {
                id = stoi(line.substr(0, line.find(',')));
                hashTable.insert(id, loc);
                loc = file.tellg();
            }
        }
        file.close();
    }

    void insert(T record) {
        ofstream file(this->fileName, ios::app);
        int loc = file.tellp();
        file.write(record.toString().c_str(), record.toString().length());
        file.write("\n", 1);
        file.close();
        hashTable.insert(record.id, loc);
    }

    void find(int id) {
        int loc = hashTable.search(id);
        ifstream file(this->fileName);
        file.seekg(loc);
        string line;
        getline(file, line);
        T record(line);
        record.print();
        file.close();
    }

    void showAll() {
        ifstream file(this->fileName);
        string line;
        for (int i = 0; i < 7; i++) {
            Node<int, int> *itr = hashTable.hashTable[i];
            while (itr) {
                file.seekg(itr->value);
                getline(file, line);
                T record(line);
                record.print();
                itr = itr->next;
            }
            cout << endl;
        }
    }

    void remove(int id) {
        int loc = hashTable.search(id);
        hashTable.remove(id);
        ifstream file(this->fileName);
        file.seekg(loc);
        string line;
        getline(file, line);
        T record(line);
        cout<<"Record to be deleted: \n";
        record.print();
        file.close();
    }
};

int main() {
    DirectAccessFile<Record> file("records.txt");
    file.insert(Record(5315, "Chinmay Patil", "2 years", 100000));
    file.insert(Record(5316, "Shubham Panchal", "3 years", 140000));
    file.insert(Record(5317, "Rahul Patil", "1 year", 80000));
    file.insert(Record(5318, "Ayush Meshram", "4 year", 160000));

    file.find(5315);
    file.find(5316);
    
    file.showAll();

    file.remove(5317);
    file.showAll();
    return 0;
}
