//
//  main.cpp
//  17_Vector_FromScratch
//
//  Created by Sathya Babu on 29/06/23.
//
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

    MyVector(MyVector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

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

    for (auto it = myVector.begin(); it != myVector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
