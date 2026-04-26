#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <stdexcept>
#include <initializer_list>

template <typename T>
class MyVector
{
private:
    T*  data_;
    int size_;
    int capacity_;

    void grow()
    {
        int newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(newCap);
    }

    void reallocate(int newCap)
    {
        T* newData = new T[newCap];
        for (int i = 0; i < size_; ++i)
            newData[i] = data_[i];
        delete[] data_;
        data_     = newData;
        capacity_ = newCap;
    }

    void copyFrom(const MyVector& other)
    {
        data_     = new T[other.capacity_];
        size_     = other.size_;
        capacity_ = other.capacity_;
        for (int i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

public:
    MyVector()
        : data_(nullptr), size_(0), capacity_(0) {}

    explicit MyVector(int n, const T& val = T())
        : data_(new T[n]), size_(n), capacity_(n)
    {
        for (int i = 0; i < n; ++i)
            data_[i] = val;
    }

    MyVector(std::initializer_list<T> il)
        : data_(new T[il.size()]), size_(0), capacity_((int)il.size())
    {
        for (const T& v : il)
            data_[size_++] = v;
    }

    MyVector(const MyVector& other)
    {
        copyFrom(other);
    }

    MyVector& operator=(const MyVector& other)
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

    T& operator[](int index)
    {
        return data_[index];
    }

    const T& operator[](int index) const
    {
        return data_[index];
    }

    T& at(int index)
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyVector::at - index out of range");
        return data_[index];
    }

    const T& at(int index) const
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyVector::at - index out of range");
        return data_[index];
    }

    T& front()
    {
        if (size_ == 0) throw std::out_of_range("MyVector::front - vector is empty");
        return data_[0];
    }

    const T& front() const
    {
        if (size_ == 0) throw std::out_of_range("MyVector::front - vector is empty");
        return data_[0];
    }

    T& back()
    {
        if (size_ == 0) throw std::out_of_range("MyVector::back - vector is empty");
        return data_[size_ - 1];
    }

    const T& back() const
    {
        if (size_ == 0) throw std::out_of_range("MyVector::back - vector is empty");
        return data_[size_ - 1];
    }

    T*       data()       { return data_; }
    const T* data() const { return data_; }

    int  size()     const { return size_;      }
    int  capacity() const { return capacity_;  }
    bool empty()    const { return size_ == 0; }

    void reserve(int newCap)
    {
        if (newCap > capacity_)
            reallocate(newCap);
    }

    void shrink_to_fit()
    {
        if (size_ < capacity_)
            reallocate(size_);
    }

    void push_back(const T& val)
    {
        if (size_ == capacity_) grow();
        data_[size_++] = val;
    }

    void pop_back()
    {
        if (size_ == 0)
            throw std::out_of_range("MyVector::pop_back - vector is empty");
        --size_;
    }

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

    void erase(int index)
    {
        if (index < 0 || index >= size_)
            throw std::out_of_range("MyVector::erase - index out of range");
        for (int i = index; i < size_ - 1; ++i)
            data_[i] = data_[i + 1];
        --size_;
    }

    void clear()
    {
        size_ = 0;
    }

    void resize(int n, const T& val = T())
    {
        if (n > capacity_) reallocate(n);
        for (int i = size_; i < n; ++i)
            data_[i] = val;
        size_ = n;
    }

    int find(const T& val) const
    {
        for (int i = 0; i < size_; ++i)
            if (data_[i] == val) return i;
        return -1;
    }

    void sort()
    {
        for (int i = 0; i < size_ - 1; ++i)
            for (int j = 0; j < size_ - i - 1; ++j)
                if (data_[j] > data_[j + 1])
                {
                    T tmp      = data_[j];
                    data_[j]   = data_[j + 1];
                    data_[j+1] = tmp;
                }
    }

    T*       begin()       { return data_;        }
    T*       end()         { return data_ + size_; }
    const T* begin() const { return data_;        }
    const T* end()   const { return data_ + size_; }
};

#endif
