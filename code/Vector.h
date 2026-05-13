#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <stdexcept>
#include <initializer_list> //to write Or initialize lists for vectors

template <typename T> //store any kind of datatype (generic class)
class MyVector
{
private:
    T* data_; //pointer to the dynamic array
    int size_; //number of elements stored in a vector
    int capacity_; //allocated memory slots (some maybe empty or not)

    //increase capacity when needed (amortized growth)
    void grow()
    {
        int newCap = (capacity_ == 0) ? 1 : capacity_ * 2; //basically increases the capacity by factors of 2, this is used when 
        //vectors become full 
        reallocate(newCap); //create a new array with new capacity
    }

    //allocate new buffer and copy existing elements into it
    void reallocate(int newCap)
    {
        T* newData = new T[newCap]; //first allocate new memory
        for (int i = 0; i < size_; ++i)
            newData[i] = data_[i]; //copy all the old elements
        delete[] data_; //DELETE ALL THE OLD DATA TO AVOID MEMORY LEAKS
        data_ = newData;
        capacity_ = newCap;
    }

    //deep copy helper used by copy ctor and operator=
    void copyFrom(const MyVector& other) //copy from is used in copy constructor and assignment operator
    {
        data_ = new T[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (int i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

public:
    //default: empty vector
    MyVector()
        : data_(nullptr), size_(0), capacity_(0) {
    }

    //create vector with n copies of val
    explicit MyVector(int n, const T& val = T()) //creates a vector with n elements
        : data_(new T[n]), size_(n), capacity_(n)
    {
        for (int i = 0; i < n; ++i)
            data_[i] = val;
    }

    //construct from initializer list: MyVector<int> v = {1,2,3}
    MyVector(std::initializer_list<T> il) //initilaizes the list
        : data_(new T[il.size()]), size_(0), capacity_((int)il.size())
    {
        for (const T& v : il)
            data_[size_++] = v;
    }

    //copy constructor=deep copy
    MyVector(const MyVector& other) //copy constructor
    {
        copyFrom(other);
    }

    //assignment operator=free existing and copy
    MyVector& operator=(const MyVector& other) //assignment operator
    {
        if (this != &other)
        {
            delete[] data_;
            copyFrom(other);
        }
        return *this;
    }
    ~MyVector()
    {
        delete[] data_;
    }

    //unchecked access (no bounds checking),faster
    T& operator[](int index)
    {
        return data_[index];
    }

    const T& operator[](int index) const
    {
        return data_[index];
    }

    //bounds-checked access, throws if out of range
    T& at(int index)
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyVector::at - index out of range"); //
        return data_[index];
    }

    const T& at(int index) const
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyVector::at - index out of range");
        return data_[index];
    }

    //first element access,throws if empty
    T& front()
    {
        if (size_ == 0) throw std::out_of_range("MyVector::front - vector is empty");
        return data_[0];// return the first element
    }

    const T& front() const
    {
        if (size_ == 0) throw std::out_of_range("MyVector::front - vector is empty");
        return data_[0];
    }

    //last element access - throws if empty
    T& back()
    {
        if (size_ == 0) throw std::out_of_range("MyVector::back - vector is empty");
        return data_[size_ - 1]; //return the last element
    }

    const T& back() const
    {
        if (size_ == 0) throw std::out_of_range("MyVector::back - vector is empty");
        return data_[size_ - 1];
    }
    //following are the basic functions 

    //pointer to raw data (may be nullptr)
    T* data() { return data_; }
    const T* data() const { return data_; }

    //capacity 
    int  size()     const { return size_; }
    int  capacity() const { return capacity_; }
    bool empty()    const { return size_ == 0; }

    //ensure at least newCap capacity (no shrink)
    void reserve(int newCap) //avoids repeated allocations
    {
        if (newCap > capacity_)
            reallocate(newCap);
    }

    //reduce capacity to fit current size (may reallocate)
    void shrink_to_fit()
    {
        if (size_ < capacity_)
            reallocate(size_); //shrinks the capacity to match size
    }

    //append element (grows if needed)
    void push_back(const T& val)
    {
        if (size_ == capacity_) grow();
        data_[size_++] = val; //adds element at the end
    }

    //remove last element (logical remove)
    void pop_back() //removes last element
    {
        if (size_ == 0)
            throw std::out_of_range("MyVector::pop_back - vector is empty");
        --size_;
    }

    //insert at index, shift elements right
    void insert(int index, const T& val)
    {
        if (index < 0 || index > size_)
            throw std::out_of_range("MyVector::insert - index out of range");
        if (size_ == capacity_) grow();
        for (int i = size_; i > index; --i)
            data_[i] = data_[i - 1];
        data_[index] = val;
        ++size_;
    }

    //erase element at index, shift elements left
    void erase(int index)
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyVector::erase - index out of range");
        for (int i = index; i < size_ - 1; ++i)
            data_[i] = data_[i + 1];
        --size_;
    }

    //clear contents, keep capacity
    void clear()
    {
        size_ = 0;
    }

    //resize to n, filling new elements with val
    void resize(int n, const T& val = T())
    {
        if (n > capacity_) reallocate(n);
        for (int i = size_; i < n; ++i)
            data_[i] = val;
        size_ = n;
    }

    //linear search, returns index or -1
    int find(const T& val) const
    {
        for (int i = 0; i < size_; ++i)
            if (data_[i] == val) return i;
        return -1;
    }

    //simple bubble sort
    void sort()
    {
        for (int i = 0; i < size_ - 1; ++i)
            for (int j = 0; j < size_ - i - 1; ++j)
                if (data_[j] > data_[j + 1])
                {
                    T tmp = data_[j];
                    data_[j] = data_[j + 1];
                    data_[j + 1] = tmp;
                }
    }

    //iterator-like access (raw pointers)
    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end()   const { return data_ + size_; }
};

#endif
