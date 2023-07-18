//
//  main.cpp
//  17_Vector_fromScratch_3_revIterator
//
//  Created by Sathya Babu on 29/06/23.
//
#include <iostream>
#include <algorithm>
#include <memory>

template<typename T>
class MyVector {
private:
    std::unique_ptr<T[]> data_;
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

    // Reverse iterator class
    class reverse_iterator {
    private:
        T* ptr_;

    public:
        reverse_iterator(T* ptr) : ptr_(ptr) {}

        T& operator*() const {
            return *ptr_;
        }

        reverse_iterator& operator++() {
            --ptr_;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator temp = *this;
            --ptr_;
            return temp;
        }

        bool operator==(const reverse_iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const reverse_iterator& other) const {
            return !(*this == other);
        }
    };

    MyVector() : data_(nullptr), size_(0), capacity_(0) {}

    MyVector(MyVector&& other) noexcept : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }

    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    ~MyVector() = default;

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
            std::unique_ptr<T[]> newData = std::make_unique<T[]>(newCapacity);

            if (data_) {
                std::copy(data_.get(), data_.get() + size_, newData.get());
            }

            data_ = std::move(newData);
            capacity_ = newCapacity;
        }
    }

    size_t size() const {
        return size_;
    }

    iterator begin() {
        return iterator(data_.get());
    }

    iterator end() {
        return iterator(data_.get() + size_);
    }

    reverse_iterator rBegin() {
        return reverse_iterator(data_.get() + size_ - 1);
    }

    reverse_iterator rEnd() {
        return reverse_iterator(data_.get() - 1);
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

    std::cout << "Forward iteration: ";
    for (auto it = myVector.begin(); it != myVector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Reverse iteration: ";
    for (auto it = myVector.rBegin(); it != myVector.rEnd(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
/*
 
 Added the reverse iterator as a patch to this code
 m
 Forward iteration: 10 20 30
 Reverse iteration: 30 20 10
 Program ended with exit code: 0
 */
