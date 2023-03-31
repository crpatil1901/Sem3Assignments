#include <iostream>
#include <string.h>

using namespace std;

template <typename T>
class HashTable
{
    int capacity;
    int size;
    T *table;

public:
    HashTable(int size)
    {
        this->capacity = size;
        this->table = new T[size];
        this->size = 0;

        // for (int i = 0; i < capacity; i++) {
        //     cout<<table[i]<<" ";
        // }
    }

    void insert(T data)
    {
        show();
        if (size < capacity)
        {
            T blnk;
            // int hashValue = data.hashValue() % this->capacity;
            int hashValue = 3;
            cout<<hashValue;
            while (!(this->table[hashValue] == blnk))
            {
                hashValue = (hashValue + 1) % capacity;
            }
            this->table[hashValue] = data;
        }
    }

    bool isEmpty(int index)
    {
        T blnk;
        return this->table[index] == blnk;
    }

    void show()
    {
        for (int i = 0; i < capacity; i++)
        {
            cout<<i<<":\t";
            this->table[i].print();
        }
    }
};

class Record
{
public:
    string name;
    string telNo;

    Record()
    {
        this->name = "";
        this->telNo = "";
    }

    Record(string name, string telNo)
    {
        this->name = name;
        this->telNo = telNo;
    }

    Record(const Record &data)
    {
        this->name = data.name;
        this->telNo = data.telNo;
    }

    void print()
    {
        cout << this->name << "\t" << this->telNo << endl;
    }

    int hashValue()
    {
        int hashValue = 0;
        for (int i = 0; this->name[i] != 0; i++)
        {
            hashValue += this->name[i];
        }
        for (int i = 0; this->telNo[i] != 0; i++)
        {
            hashValue += this->telNo[i];
        }
        return hashValue;
    }
};

bool operator==(Record lhs, Record rhs)
{
    int nameMatch = lhs.name.compare(rhs.name);
    int telNoMatch = lhs.telNo.compare(rhs.telNo);
    return nameMatch && telNoMatch;
}

int main()
{
    HashTable<Record> set(10);
    Record a("Chinmay", "1234"), b("Shubham", "2345"), c("Aayush", "4567"), d("Sumeet", "6789");
    // set.insert(a);
    Record x, y;
    cout<<(x==y);
    cout << "Over\n";
}