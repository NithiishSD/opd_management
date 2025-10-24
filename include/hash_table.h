#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <iostream>

template <typename T>
struct HashNode
{
    int key;
    T value;
    bool isDeleted;

    HashNode() : key(-1), isDeleted(false) {}
    HashNode(int k, const T &v) : key(k), value(v), isDeleted(false) {}
};

template <typename T>
class HashTable
{
private:
    std::vector<HashNode<T>> table;
    int capacity;
    int count;

    int hashFunction(int key) const { return key % capacity; }

public:
    HashTable(int cap = 100) : capacity(cap), count(0)
    {
        table.resize(capacity);
    }

    bool insert(int key, const T &value)
    {
        if (count >= capacity)
            return false;

        int idx = hashFunction(key);
        int startIdx = idx;

        while (table[idx].key != -1 && !table[idx].isDeleted && table[idx].key != key)
        {
            idx = (idx + 1) % capacity;
            if (idx == startIdx)
                return false;
        }

        table[idx] = HashNode<T>(key, value);
        count++;
        return true;
    }

    bool remove(int key)
    {
        int idx = hashFunction(key);
        int startIdx = idx;

        while (table[idx].key != -1)
        {
            if (table[idx].key == key && !table[idx].isDeleted)
            {
                table[idx].isDeleted = true;
                count--;
                return true;
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx)
                break;
        }
        return false;
    }

    bool exists(int key) const
    {
        int idx = hashFunction(key);
        int startIdx = idx;

        while (table[idx].key != -1)
        {
            if (table[idx].key == key && !table[idx].isDeleted)
                return true;
            idx = (idx + 1) % capacity;
            if (idx == startIdx)
                break;
        }
        return false;
    }

    T *get(int key)
    {
        int idx = hashFunction(key);
        int startIdx = idx;

        while (table[idx].key != -1)
        {
            if (table[idx].key == key && !table[idx].isDeleted)
                return &table[idx].value;
            idx = (idx + 1) % capacity;
            if (idx == startIdx)
                break;
        }
        return nullptr;
    }

    int size() const { return count; }
};

// Explicit template instantiation
#include "patients.h"
template class HashTable<Patient>;
template class HashTable<Patient *>;

#endif
