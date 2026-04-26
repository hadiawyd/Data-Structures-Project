#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H

#include "Node.h"
#include <stdexcept>
#include <initializer_list>

template <typename T>
struct DNode
{
    T      data;
    DNode* next;
    DNode* prev;

    explicit DNode(const T& val)
        : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class MyLinkedList
{
private:
    DNode<T>* head_;
    DNode<T>* tail_;
    int       size_;

    void copyFrom(const MyLinkedList& other)
    {
        DNode<T>* curr = other.head_;
        while (curr != nullptr)
        {
            push_back(curr->data);
            curr = curr->next;
        }
    }

    void destroyAll()
    {
        while (head_ != nullptr)
        {
            DNode<T>* tmp = head_;
            head_         = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0;
    }

public:
    MyLinkedList()
        : head_(nullptr), tail_(nullptr), size_(0) {}

    MyLinkedList(std::initializer_list<T> il)
        : head_(nullptr), tail_(nullptr), size_(0)
    {
        for (const T& v : il) push_back(v);
    }

    MyLinkedList(const MyLinkedList& other)
        : head_(nullptr), tail_(nullptr), size_(0)
    {
        copyFrom(other);
    }

    MyLinkedList& operator=(const MyLinkedList& other)
    {
        if (this != &other)
        {
            destroyAll();
            copyFrom(other);
        }
        return *this;
    }

    ~MyLinkedList()
    {
        destroyAll();
    }

    int  size()  const { return size_;      }
    bool empty() const { return size_ == 0; }

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

    T& at(int index)
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyLinkedList::at - index out of range");
        DNode<T>* curr = head_;
        for (int i = 0; i < index; ++i) curr = curr->next;
        return curr->data;
    }

    const T& at(int index) const
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyLinkedList::at - index out of range");
        DNode<T>* curr = head_;
        for (int i = 0; i < index; ++i) curr = curr->next;
        return curr->data;
    }

    T&       operator[](int index)       { return at(index); }
    const T& operator[](int index) const { return at(index); }

    void push_back(const T& val)
    {
        DNode<T>* node = new DNode<T>(val);
        if (tail_ == nullptr)
        {
            head_ = tail_ = node;
        }
        else
        {
            node->prev  = tail_;
            tail_->next = node;
            tail_       = node;
        }
        ++size_;
    }

    void push_front(const T& val)
    {
        DNode<T>* node = new DNode<T>(val);
        if (head_ == nullptr)
        {
            head_ = tail_ = node;
        }
        else
        {
            node->next  = head_;
            head_->prev = node;
            head_       = node;
        }
        ++size_;
    }

    void pop_back()
    {
        if (empty())
            throw std::out_of_range("MyLinkedList::pop_back - list is empty");
        DNode<T>* tmp = tail_;
        tail_         = tail_->prev;
        if (tail_) tail_->next = nullptr;
        else       head_       = nullptr;
        delete tmp;
        --size_;
    }

    void pop_front()
    {
        if (empty())
            throw std::out_of_range("MyLinkedList::pop_front - list is empty");
        DNode<T>* tmp = head_;
        head_         = head_->next;
        if (head_) head_->prev = nullptr;
        else       tail_       = nullptr;
        delete tmp;
        --size_;
    }

    void insert(int index, const T& val)
    {
        if (index < 0 || index > size_)
            throw std::out_of_range("MyLinkedList::insert - index out of range");
        if (index == 0)     { push_front(val); return; }
        if (index == size_) { push_back(val);  return; }

        DNode<T>* curr = head_;
        for (int i = 0; i < index; ++i) curr = curr->next;

        DNode<T>* node   = new DNode<T>(val);
        node->prev       = curr->prev;
        node->next       = curr;
        curr->prev->next = node;
        curr->prev       = node;
        ++size_;
    }

    void erase(int index)
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyLinkedList::erase - index out of range");
        if (index == 0)          { pop_front(); return; }
        if (index == size_ - 1)  { pop_back();  return; }

        DNode<T>* curr   = head_;
        for (int i = 0; i < index; ++i) curr = curr->next;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        --size_;
    }

    void clear() { destroyAll(); }

    int find(const T& val) const
    {
        DNode<T>* curr = head_;
        for (int i = 0; curr != nullptr; ++i, curr = curr->next)
            if (curr->data == val) return i;
        return -1;
    }

    bool contains(const T& val) const { return find(val) != -1; }

    bool remove(const T& val)
    {
        int idx = find(val);
        if (idx == -1) return false;
        erase(idx);
        return true;
    }

    void reverse()
    {
        DNode<T>* curr = head_;
        while (curr != nullptr)
        {
            DNode<T>* tmp = curr->next;
            curr->next    = curr->prev;
            curr->prev    = tmp;
            curr          = tmp;
        }
        DNode<T>* tmp = head_;
        head_         = tail_;
        tail_         = tmp;
    }

    void sort()
    {
        if (size_ <= 1) return;
        bool swapped = true;
        while (swapped)
        {
            swapped     = false;
            DNode<T>* c = head_;
            while (c->next != nullptr)
            {
                if (c->data > c->next->data)
                {
                    T tmp         = c->data;
                    c->data       = c->next->data;
                    c->next->data = tmp;
                    swapped       = true;
                }
                c = c->next;
            }
        }
    }

    class Iterator
    {
    public:
        explicit Iterator(DNode<T>* node) : curr_(node) {}
        T&        operator*()             { return curr_->data;  }
        T*        operator->()            { return &curr_->data; }
        Iterator& operator++()            { curr_ = curr_->next; return *this; }
        Iterator  operator++(int)         { Iterator tmp(*this); ++(*this); return tmp; }
        bool      operator==(const Iterator& o) const { return curr_ == o.curr_; }
        bool      operator!=(const Iterator& o) const { return curr_ != o.curr_; }
    private:
        DNode<T>* curr_;
    };

    Iterator begin() { return Iterator(head_);    }
    Iterator end()   { return Iterator(nullptr);  }
};

#endif
