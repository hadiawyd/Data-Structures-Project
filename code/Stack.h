#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <stdexcept>

template <typename T>
class Stack
{
private:
    Node<T>* topNode;   // Pointer to the top of the stack
    int count;          // Tracks the number of elements in the stack

    // Helper: copies all elements from 'other' into this stack,
    // preserving the original top-to-bottom order
    void copyFrom(const Stack& other)
    {
        // Traverse 'other' and build a reversed linked list
        // so that when we push, the original order is restored
        Node<T>* temp = other.topNode;
        Node<T>* reversed = nullptr;

        while (temp != nullptr)
        {
            Node<T>* newNode = new Node<T>(temp->data);
            newNode->next = reversed;
            reversed = newNode;
            temp = temp->next;
        }

        // Push nodes from the reversed list so they end up
        // in the same order as the original stack
        while (reversed != nullptr)
        {
            push(reversed->data);
            Node<T>* del = reversed;
            reversed = reversed->next;
            delete del;
        }
    }

public:
    // Default constructor: initializes an empty stack
    Stack()
    {
        topNode = nullptr;
        count = 0;
    }

    // Destructor: pops all elements to free allocated memory
    ~Stack()
    {
        while (!empty())
            pop();
    }

    // Copy constructor: creates a deep copy of 'other'
    Stack(const Stack& other)
    {
        topNode = nullptr;
        count = 0;
        copyFrom(other);
    }

    // Assignment operator: clears current stack, then deep copies 'other'
    Stack& operator=(const Stack& other)
    {
        if (this != &other)
        {
            while (!empty())
                pop();
            copyFrom(other);
        }
        return *this;
    }

    // Pushes a new value onto the top of the stack
    void push(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    // Removes the top element; throws if the stack is empty
    void pop()
    {
        if (empty())
            throw std::out_of_range("Stack underflow");

        Node<T>* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
    }

    // Returns the top element without removing it; throws if empty
    T top() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

        return topNode->data;
    }

    // Returns true if the stack has no elements
    bool empty() const
    {
        return topNode == nullptr;
    }

    // Returns the number of elements currently in the stack
    int size() const
    {
        return count;
    }
};

#endif
