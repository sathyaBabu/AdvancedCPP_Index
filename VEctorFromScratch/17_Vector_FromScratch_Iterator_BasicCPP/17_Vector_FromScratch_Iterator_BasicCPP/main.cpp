//
//  main.cpp
//  17_Vector_FromScratch_Iterator_BasicCPP
//
//  Created by Sathya Babu on 29/06/23.
//
/*
 
 In this updated code, the MyVector class includes an inner class iterator that represents an iterator for MyVector. The iterator class provides the necessary member functions required by the iterator concept, such as operator*, operator++, operator==, and operator!=.

 The begin() member function returns an iterator pointing to the first element of the vector (i.e., the data_ pointer). The end() member function returns an iterator pointing to the position just after the last element of the vector (i.e., data_ + size_).

 In the main function, a for loop is used to iterate over the elements of myVector using begin() and end() iterators. The operator* is used to dereference the iterator and access the element.
 
 
 
 */
#include <iostream>
#include <algorithm>

template<typename T>
class MyVector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

public:
    class iterator {
    private:
        T* ptr_;

    public:
        iterator(T* ptr) : ptr_(ptr) {}

        T& operator*() const {
            return *ptr_;
        }

        iterator& operator++() {
            ++ptr_;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }

        bool operator==(const iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    MyVector() : data_(nullptr), size_(0), capacity_(0) {}

    ~MyVector() {
        delete[] data_;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(newCapacity);
        }

        data_[size_] = value;
        ++size_;
    }

    void reserve(size_t newCapacity) {
        if (newCapacity > capacity_) {
            T* newData = new T[newCapacity];

            if (data_) {
                std::copy(data_, data_ + size_, newData);
                delete[] data_;
            }

            data_ = newData;
            capacity_ = newCapacity;
        }
    }

    size_t size() const {
        return size_;
    }

    iterator begin() {
        return iterator(data_);
    }

    iterator end() {
        return iterator(data_ + size_);
    }

    T& operator[](size_t index) {
        return data_[index];
    }
};

int main() {
    MyVector<int> myVector;
    myVector.push_back(10);
    myVector.push_back(20);
    myVector.push_back(30);

    std::cout << " Display using size() "<< std::endl;
    for (size_t i = 0; i < myVector.size(); ++i) {
        std::cout << myVector[i] << " ";
    }
    
    std::cout << " Display using begin() "<< std::endl;
    std::cout << std::endl;
    
    for (auto it = myVector.begin(); it != myVector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << " Display using itr.begin() "<< std::endl;
    for( MyVector<int>:: iterator itr1 = myVector.begin(); itr1 != myVector.end(); ++itr1)
        {
            std::cout << *itr1 << " ";
        }
        

    return 0;
}
/*
 
 Display using size()
10 20 30  Display using begin()

10 20 30
 Display using itr.begin()
10 20 30 Program ended with exit code: 0
 */
