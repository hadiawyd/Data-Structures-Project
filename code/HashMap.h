#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>
using namespace std;

//a hash map stores key-value pairs and lets us
// find things really fast (like O(1) on average). The trick is
// using a "hash function" to decide where to put each item.

// Each bucket holds a linked chain of these nodes
// (called "separate chaining" -- handles collisions by just linking them)
struct HashNode {
    string key;
    int value;
    HashNode* next;  // points to the next node if two keys land in the same bucket

    HashNode(string k, int v) {
        key   = k;
        value = v;
        next  = nullptr;
    }
};

class HashMap {
private:
    // 10 buckets is small but easy to visualize while learning
    static const int TABLE_SIZE = 10;
    HashNode* table[TABLE_SIZE];

    // Hash function -- adds up ASCII values of each character, then mod by table size
    // Simple, but it works fine for small examples
    int hashFunction(string key) {
        int sum = 0;
        for (int i = 0; i < (int)key.length(); i++) {
            sum += key[i];
        }
        return sum % TABLE_SIZE;
    }

public:
    // Set every bucket to nullptr so we start with a clean slate
    HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // Insert a key-value pair. If the key is already in there, just update the value.
    void insert(string key, int value) {
        int index = hashFunction(key);
        HashNode* current = table[index];

        // Walk the chain -- maybe the key is already here
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;  // just update and leave
                return;
            }
            current = current->next;
        }

        // Key wasn't there, so add a new node at the front of the chain
        // (front insertion is O(1) which is nice)
        HashNode* newNode = new HashNode(key, value);
        newNode->next = table[index];
        table[index]  = newNode;

        cout << "Inserted: [" << key << " -> " << value << "] at bucket " << index << "\n";
    }

    // Get a value by key. Returns -1 if the key doesn't exist.
    int get(string key) {
        int index = hashFunction(key);
        HashNode* current = table[index];

        while (current != nullptr) {
            if (current->key == key)
                return current->value;
            current = current->next;
        }

        return -1;  // key not found
    }

    // Remove a key-value pair from the map
    void remove(string key) {
        int index = hashFunction(key);
        HashNode* current = table[index];
        HashNode* prev    = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr)
                    table[index] = current->next;  // removing the first node in chain
                else
                    prev->next = current->next;    // skip over the node

                delete current;
                cout << "Removed key: \"" << key << "\"\n";
                return;
            }
            prev    = current;
            current = current->next;
        }

        cout << "Key \"" << key << "\" not found -- nothing removed.\n";
    }

    // Print every bucket so we can see exactly what's inside
    void display() {
        cout << "\n--- HashMap Contents ---\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Bucket [" << i << "]: ";
            HashNode* current = table[i];
            if (current == nullptr) {
                cout << "empty";
            }
            while (current != nullptr) {
                cout << "(" << current->key << ", " << current->value << ")";
                if (current->next != nullptr) cout << " -> ";
                current = current->next;
            }
            cout << "\n";
        }
        cout << "------------------------\n\n";
    }

    // Destructor -- free every node we allocated, bucket by bucket
    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

#endif