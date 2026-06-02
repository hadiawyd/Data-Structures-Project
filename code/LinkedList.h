#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
//different from a vector, linked list donot store elements in a continous memory
#include <stdexcept>
#include <initializer_list>
#include <utility>   // std::move, std::swap

//simple doubly-linked list implementation
template <typename T>
struct DNode //doubly linked node 
{
    T      data;
    DNode* next;
    DNode* prev;

    explicit DNode(const T& val)
        : data(val), next(nullptr), prev(nullptr) {
    }

    // move constructor for DNode so we avoid copying when building from rvalue
    explicit DNode(T&& val)
        : data(std::move(val)), next(nullptr), prev(nullptr) {
    }
};

template <typename T>
class MyLinkedList
{
private:
    DNode<T>* head_; //points to the first node
    DNode<T>* tail_; //points to the last node
    int       size_; //no. of nodes

    // deep copy helper 
    // copies another linked list; O(n) because every node is copied,
    // same as STL list
    void copyFrom(const MyLinkedList& other) //walks the other list node by node and calls push_back for each value
    {
        DNode<T>* curr = other.head_;
        while (curr != nullptr)
        {
            push_back(curr->data);
            curr = curr->next;
        }
    }

    //  free all nodes and reset state to avoid memory leaks 
    // O(n) — same as STL list
    void destroyAll()
    {
        while (head_ != nullptr)
        {
            DNode<T>* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0;
    }

   
    // Starts from head or tail depending on which end is closer, giving
    // Still O(n), but about twice as fast in practice because traversal starts from the nearest end.
    DNode<T>* nodeAt(int index) const
    {
        if (index < size_ / 2)           // closer to head then walk forward
        {
            DNode<T>* curr = head_;
            for (int i = 0; i < index; ++i) curr = curr->next;
            return curr;
        }
        else                             // closer to tail then walk backward
        {
            DNode<T>* curr = tail_;
            for (int i = size_ - 1; i > index; --i) curr = curr->prev;
            return curr;
        }
    }

    // merge sort internals
    // Split the raw-node chain starting at 'head' into two halves;
    // returns the head of the second half.
    DNode<T>* splitHalf(DNode<T>* head)
    {
        DNode<T>* slow = head;
        DNode<T>* fast = head->next;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next; //slow moves 1 step
            fast = fast->next->next; // fast moves 2 steps so when fast finishes slow is at the middle
        }
        DNode<T>* second = slow->next;
        slow->next = nullptr;            // cut the chain
        if (second) second->prev = nullptr; // to make sure that the second half's back pointer doesnt point back into the first half
        return second;
    }

    // Merge two sorted raw-node chains; returns the merged head.
    DNode<T>* mergeSorted(DNode<T>* a, DNode<T>* b)
    {
        if (!a) return b;
        if (!b) return a;

        DNode<T>* result = nullptr;
        if (a->data <= b->data)
        {
            result = a; // if a is smaller then recursivley merge the rest of b with it 
            result->next = mergeSorted(a->next, b);
        }
        else
        {
            result = b;
            result->next = mergeSorted(a, b->next);
        }
        if (result->next) result->next->prev = result; // the node that we just attached needs to know who is behind it
        result->prev = nullptr;
        return result;
    }

    //Recursive merge-sort on raw node chain; returns sorted head.
    DNode<T>* mergeSort(DNode<T>* head)
    {
        if (!head || !head->next) return head;

        DNode<T>* second = splitHalf(head); // cut the chain in half

        head = mergeSort(head); // recursively sort both halves
        second = mergeSort(second);

        return mergeSorted(head, second); //then call the mergeSorted function to get the fully sorted chain
    }

public:

    //default: empty list
    MyLinkedList()
        : head_(nullptr), tail_(nullptr), size_(0) {
    }

    //construct from initializer list
    MyLinkedList(std::initializer_list<T> il)
        : head_(nullptr), tail_(nullptr), size_(0)
    {
        for (const T& v : il) push_back(v); // loops through the list calling pushback for each value
    }

    //  copy constructor — deep copy, O(n)
    MyLinkedList(const MyLinkedList& other)
        : head_(nullptr), tail_(nullptr), size_(0)
    {
        copyFrom(other);
    }

    // copy assignment — destroy + deep copy, O(n)
    MyLinkedList& operator=(const MyLinkedList& other)
    {
        if (this != &other)
        {
            destroyAll(); // first destroys all current nodes and then copies 
            copyFrom(other);
        }
        return *this;
    }

    // move constructor — steal other's nodes, O(1)
    MyLinkedList(MyLinkedList&& other) noexcept // this is helpful for when u want to create a temp list u can just "steal
        //the temp pointers meaning u get the data without doing any long work
        : head_(other.head_), tail_(other.tail_), size_(other.size_) // steals head, tail, size from other. 
        // Sets other's to null,no new nodes made
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    // move assignment — swap then let 'other' destroy our old data, O(1)
    MyLinkedList& operator=(MyLinkedList&& other) noexcept // overwriting your list with another's data.
    {
        if (this != &other)
        {
            destroyAll();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // destructor
    ~MyLinkedList()
    {
        destroyAll();
    }

    // size / empty
    int  size()  const { return size_; }
    bool empty() const { return size_ == 0; }



    //access first element
    T& front()
    {
        if (empty()) throw std::out_of_range("MyLinkedList::front - list is empty");
        return head_->data;
    }

    const T& front() const
    {
        if (empty()) throw std::out_of_range("MyLinkedList::front - list is empty");
        return head_->data;
    }

    //access last element 
    T& back()
    {
        if (empty()) throw std::out_of_range("MyLinkedList::back - list is empty");
        return tail_->data;
    }

    const T& back() const
    {
        if (empty()) throw std::out_of_range("MyLinkedList::back - list is empty");
        return tail_->data;
    }

    // at() uses the optimised nodeAt().
    // Complexity is still O(n), but traversal starts from the nearest end,
    // making it faster in practice than always starting from the head.
    T& at(int index)
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyLinkedList::at - index out of range");
        return nodeAt(index)->data; // nodeAt does the head/tail optimised walk and returns the node pointer ,we just grab its data
    }

    const T& at(int index) const
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyLinkedList::at - index out of range");
        return nodeAt(index)->data;
    }

    // operator[] delegates to at() 
    T& operator[](int index) { return at(index); } //this u can change
    const T& operator[](int index) const { return at(index); } //this is read only

    // push / pop 

    //append to tail
    void push_back(const T& val)
    {
        DNode<T>* node = new DNode<T>(val);
        if (tail_ == nullptr)
        {
            head_ = tail_ = node;
        }
        else
        {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    //insert at head
    void push_front(const T& val)
    {
        DNode<T>* node = new DNode<T>(val);
        if (head_ == nullptr)
        {
            head_ = tail_ = node;
        }
        else
        {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }

    //remove from tail
    void pop_back()
    {
        if (empty())
            throw std::out_of_range("MyLinkedList::pop_back - list is empty");
        DNode<T>* tmp = tail_;
        tail_ = tail_->prev;
        if (tail_) tail_->next = nullptr;
        else       head_ = nullptr;
        delete tmp;
        --size_;
    }

    //remove from head
    void pop_front()
    {
        if (empty())
            throw std::out_of_range("MyLinkedList::pop_front - list is empty");
        DNode<T>* tmp = head_;
        head_ = head_->next;
        if (head_) head_->prev = nullptr;
        else       tail_ = nullptr;
        delete tmp;
        --size_;
    }

    // Insert at integer index ,uses optimised nodeAt() (head/tail walk) so
    // the traversal is O(n/2) on average. Head/tail shortcuts remain O(1).
    void insert(int index, const T& val)
    {
        if (index < 0 || index > size_)
            throw std::out_of_range("MyLinkedList::insert - index out of range");
        if (index == 0) { push_front(val); return; }
        if (index == size_) { push_back(val);  return; }

        DNode<T>* curr = nodeAt(index);   // O(n/2) 

        DNode<T>* node = new DNode<T>(val);
        node->prev = curr->prev;
        node->next = curr;
        curr->prev->next = node;
        curr->prev = node;
        ++size_;
    }

    // Iterator-based insert — O(1) at the splice point, same as std::list.
    // Inserts 'val' before the position pointed to by 'it'.
    // Returns an iterator pointing to the newly inserted node.
    class Iterator; // forward declaration
    Iterator insert(Iterator it, const T& val)
    {
        if (it == end()) { push_back(val);  return Iterator(tail_); }
        if (it == begin()) { push_front(val); return Iterator(head_); }

        DNode<T>* curr = it.node();       // O(1) — no traversal needed
        DNode<T>* node = new DNode<T>(val);
        node->prev = curr->prev;
        node->next = curr;
        curr->prev->next = node;
        curr->prev = node;
        ++size_;
        return Iterator(node);
    }

    // Erase at integer index — uses optimised nodeAt(), O(n/2) average.
    // Head/tail shortcuts remain O(1).
    void erase(int index)
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyLinkedList::erase - index out of range");
        if (index == 0) { pop_front(); return; }
        if (index == size_ - 1) { pop_back();  return; }

        DNode<T>* curr = nodeAt(index);   // O(n/2)
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        --size_;
    }

    // Iterator-based erase — O(1) at the splice point, same as std::list.
    // Returns an iterator to the element after the erased one.
    Iterator erase(Iterator it)
    {
        DNode<T>* curr = it.node();
        if (it == end())
            return end();
        if (curr == head_) { pop_front(); return begin(); }
        if (curr == tail_) { pop_back();  return end(); }

        Iterator next(curr->next);
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        --size_;
        return next;
    }

    //clear all nodes, keep container valid
    void clear() { destroyAll(); }

    //linear search, returns index or -1, O(n)
    int find(const T& val) const
    {
        DNode<T>* curr = head_;
        for (int i = 0; curr != nullptr; ++i, curr = curr->next)
            if (curr->data == val) return i;
        return -1;
    }
    bool contains(const T& val) const { return find(val) != -1; }

    //remove first occurrence of val, return success
    bool remove(const T& val)
    {
        int idx = find(val);
        if (idx == -1) return false;
        erase(idx);
        return true;
    }

    //reverse list in-place by swapping next/prev links
    void reverse()
    {
        DNode<T>* curr = head_;
        while (curr != nullptr)
        {
            DNode<T>* tmp = curr->next; // save the next node before we overwrite it 
            curr->next = curr->prev; // next becomes prev
            curr->prev = tmp; // prev becomes next
            curr = tmp; // move forward
        }
        DNode<T>* tmp = head_;
        head_ = tail_;
        tail_ = tmp;
    }

    void sort()
    {
        if (size_ <= 1) return;

        head_->prev = nullptr;  // ensure clean entry for mergeSort
        head_ = mergeSort(head_);

        // repair tail_ pointer and all prev links after the sort
        DNode<T>* curr = head_;
        while (curr->next != nullptr)
        {
            curr->next->prev = curr;
            curr = curr->next;
        }
        tail_ = curr;
    }

    // forward iterator — bidirectional, exposes node() for O(1) insert/erase
    class Iterator
    {
    public:
        explicit Iterator(DNode<T>* node) : curr_(node) {}

        T& operator*() { return curr_->data; } // deference
        T* operator->() { return &curr_->data; } // arrow operator for struct

        Iterator& operator++() { curr_ = curr_->next; return *this; }
        Iterator  operator++(int) { Iterator tmp(*this); ++(*this); return tmp; }

        // backward traversal 
        Iterator& operator--() { curr_ = curr_->prev; return *this; }
        Iterator  operator--(int) { Iterator tmp(*this); --(*this); return tmp; }

        bool operator==(const Iterator& o) const { return curr_ == o.curr_; }
        bool operator!=(const Iterator& o) const { return curr_ != o.curr_; }

        // expose raw node pointer so iterator-based insert/erase stay O(1)
        DNode<T>* node() const { return curr_; }

    private:
        DNode<T>* curr_;
    };

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }
};

#endif
