#ifndef MYSTACK_H
#define MYSTACK_H

#include "Node.h"
#include <stdexcept>

template <typename T>
class MyStack
{
private:
    Node<T>* topNode;
    int count;

    void copyFrom(const MyStack& other)
    {
        Node<T>* temp = other.topNode;
        Node<T>* reversed = nullptr;

        while (temp != nullptr)
        {
            Node<T>* newNode = new Node<T>(temp->data);
            newNode->next = reversed;
            reversed = newNode;
            temp = temp->next;
        }

        while (reversed != nullptr)
        {
            push(reversed->data);
            Node<T>* del = reversed;
            reversed = reversed->next;
            delete del;
        }
    }

public:
    MyStack()
    {
        topNode = nullptr;
        count = 0;
    }

    ~MyStack()
    {
        while (!empty())
            pop();
    }

    MyStack(const MyStack& other)
    {
        topNode = nullptr;
        count = 0;
        copyFrom(other);
    }

    MyStack& operator=(const MyStack& other)
    {
        if (this != &other)
        {
            while (!empty())
                pop();
            copyFrom(other);
        }
        return *this;
    }

    void push(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    void pop()
    {
        if (empty())
            throw std::out_of_range("Stack underflow");

        Node<T>* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
    }

    T top() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

        return topNode->data;
    }

    bool empty() const
    {
        return topNode == nullptr;
    }

    int size() const
    {
        return count;
    }
};

#endif
