#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct Bed
{
    int bedID;
    bool isOccupied;
    bool isDeleted;

    Bed();
};

class HashTable
{
private:
    Bed *table;
    int capacity;
    int size;

    int hashFunc(int key) const;

public:
    HashTable(int capacity = 20);
    ~HashTable();

    bool isFull() const;

    void allocateBed(int bedID);
    void freeBed(int bedID);
    bool isAvailable(int bedID) const;
    void displayBeds() const;
};

#endif
