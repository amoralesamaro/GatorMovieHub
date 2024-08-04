#pragma once

#include <vector>
#include <list>
#include <utility>
#include <algorithm> // For std::move

using namespace std;

template <typename K, typename V>
class HashTable
{
private:
    vector<list<pair<K, V>>> table; // Vector of linked lists to handle collisions
    int size;
    int capacity;
    const float loadFactorThreshold = 0.75;

    // Hash function to calculate the index for a key
    int hashFunction(K key)
    {
        return key % capacity;
    }

    // Resize the hash table when load factor exceeds threshold
    void resize()
    {
        int newCapacity = capacity * 2;
        vector<list<pair<K, V>>> newTable(newCapacity);

        for (auto &bucket : table)
        {
            for (auto &kv : bucket)
            {
                int newIndex = kv.first % newCapacity;
                newTable[newIndex].push_back(kv);
            }
        }

        table = std::move(newTable); // Use std::move to transfer ownership
        capacity = newCapacity;
    }

public:
    // Constructor to initialize the hash table with a given capacity
    HashTable(int cap = 100) : capacity(cap), size(0)
    {
        table.resize(capacity);
    }

    // Insert a key-value pair into the hash table
    void insert(K key, V value)
    {
        int index = hashFunction(key);
        auto &entries = table[index];

        // Check if the key already exists, and update the value if it does
        for (auto &entry : entries)
        {
            if (entry.first == key)
            {
                entry.second = value;
                return;
            }
        }

        // If the key does not exist, insert the new key-value pair
        if ((float)size / capacity >= loadFactorThreshold)
        {
            resize();
            index = hashFunction(key); // Recalculate the index after resizing
        }

        table[index].push_back({key, value});
        size++;
    }

    // Search for a value by its key
    bool search(K key, V &value)
    {
        int index = hashFunction(key);
        for (auto &kv : table[index])
        {
            if (kv.first == key)
            {
                value = kv.second;
                return true;
            }
        }
        return false;
    }

    // Remove a key-value pair from the hash table
    void remove(K key)
    {
        int index = hashFunction(key);
        auto &entries = table[index];
        for (auto it = entries.begin(); it != entries.end(); ++it)
        {
            if (it->first == key)
            {
                entries.erase(it);
                size--;
                return;
            }
        }
    }

    // Get all values from the hash table
    vector<V> getAllElements() const
    {
        vector<V> elements;
        for (const auto &bucket : table)
        {
            for (const auto &kv : bucket)
            {
                elements.push_back(kv.second);
            }
        }
        return elements;
    }

    // Get the current size of the hash table
    int getSize() const
    {
        return size;
    }
};

// Function to load movies from a file and insert them into the hash table
void loadMovies(MovieHashTable &hashTable, const string &filename);
// Function to load ratings from a file and update the hash table
void loadRatings(MovieHashTable &hashTable, const string &filename);
