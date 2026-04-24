#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "Node.h"
#include <stdexcept>

template <typename T>
class MyQueue
{
private:
    Node<T>* frontNode;
    Node<T>* rearNode;
    int count;

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
    MyQueue()
    {
        frontNode = nullptr;
        rearNode = nullptr;
        count = 0;
    }

    ~MyQueue()
    {
        while (!empty())
            dequeue();
    }

    MyQueue(const MyQueue& other)
    {
        frontNode = rearNode = nullptr;
        count = 0;
        copyFrom(other);
    }

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

    void enqueue(T value)
    {
        Node<T>* newNode = new Node<T>(value);

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

    void dequeue()
    {
        if (empty())
            throw std::out_of_range("Queue underflow");

        Node<T>* temp = frontNode;
        frontNode = frontNode->next;

        if (frontNode == nullptr)
            rearNode = nullptr;

        delete temp;
        count--;
    }

    T front() const
    {
        if (empty())
            throw std::out_of_range("Queue is empty");

        return frontNode->data;
    }

    T rear() const
    {
        if (empty())
            throw std::out_of_range("Queue is empty");

        return rearNode->data;
    }

    bool empty() const
    {
        return frontNode == nullptr;
    }

    int size() const
    {
        return count;
    }
};

#endif
