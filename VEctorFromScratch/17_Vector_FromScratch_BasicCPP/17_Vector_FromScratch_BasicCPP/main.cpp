//
//  main.cpp
//  17_Vector_FromScratch_BasicCPP
//
//  Created by Sathya Babu on 29/06/23.
//
/*
 
 n the above code, a MyVector class template is created. It manages a dynamically allocated array data_ to store the elements, and keeps track of the current size_ and capacity_ of the vector.

 The push_back function is used to add elements to the vector. If the current size exceeds the capacity, the reserve function is called to increase the capacity by allocating a larger array and copying the existing elements.

 The size function returns the current size of the vector, and the operator[] allows accessing elements using the index.

 In the main function, an instance of MyVector<int> is created and elements are added using push_back. Then, the elements are printed using a loop and the operator[].
 
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

    T& operator[](size_t index) {
        return data_[index];
    }
};

int main() {
    MyVector<int> myVector;
    myVector.push_back(10);
    myVector.push_back(20);
    myVector.push_back(30);

    for (size_t i = 0; i < myVector.size(); ++i) {
        std::cout << myVector[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
// 10 20 30
