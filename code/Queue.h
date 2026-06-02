#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <stdexcept>

template <typename T>
class MyQueue
{
private:
    Node<T>* frontNode;  // Pointer to the front (dequeue side) of the queue
    Node<T>* rearNode;   // Pointer to the rear (enqueue side) of the queue
    int count;           // Tracks the number of elements in the queue

    // Helper: copies all elements from 'other' into this queue,
    // preserving front-to-rear order
    void copyFrom(const MyQueue& other)
    {
        Node<T>* temp = other.frontNode;
        while (temp != nullptr)
        {
            enqueue(temp->data);
            temp = temp->next;
        }
    }

public:
    // Default constructor: initializes an empty queue
    MyQueue()
    {
        frontNode = nullptr;
        rearNode = nullptr;
        count = 0;
    }

    // Destructor: dequeues all elements to free allocated memory
    ~MyQueue()
    {
        while (!empty())
            dequeue();
    }

    // Copy constructor: creates a deep copy of 'other'
    MyQueue(const MyQueue& other)
    {
        frontNode = rearNode = nullptr;
        count = 0;
        copyFrom(other);
    }

    // Assignment operator: clears current queue, then deep copies 'other'
    MyQueue& operator=(const MyQueue& other)
    {
        if (this != &other)
        {
            while (!empty())
                dequeue();
            copyFrom(other);
        }
        return *this;
    }

    // Adds a new value to the rear of the queue
    void enqueue(T value)
    {
        Node<T>* newNode = new Node<T>(value);

        // If queue is empty, new node is both front and rear
        if (rearNode == nullptr)
        {
            frontNode = rearNode = newNode;
        }
        else
        {
            rearNode->next = newNode;
            rearNode = newNode;
        }

        count++;
    }

    // Removes the front element; throws if the queue is empty
    void dequeue()
    {
        if (empty())
            throw std::out_of_range("Queue underflow");

        Node<T>* temp = frontNode;
        frontNode = frontNode->next;

        // If the queue is now empty, reset rearNode as well
        if (frontNode == nullptr)
            rearNode = nullptr;

        delete temp;
        count--;
    }

    // Returns the front element without removing it; throws if empty
    T front() const
    {
        if (empty())
            throw std::out_of_range("Queue is empty");

        return frontNode->data;
    }

    // Returns the rear element without removing it; throws if empty
    T rear() const
    {
        if (empty())
            throw std::out_of_range("Queue is empty");

        return rearNode->data;
    }

    // Returns true if the queue has no elements
    bool empty() const
    {
        return frontNode == nullptr;
    }

    // Returns the number of elements currently in the queue
    int size() const
    {
        return count;
    }
};

#endif
