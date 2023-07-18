//
//  main.cpp
//  17_Vector_FromScratch_2
//
//  Created by Sathya Babu on 29/06/23.
//

/*
 iterator :
 
 the MyVector class includes an inner class iterator that represents an iterator for MyVector. The iterator class provides the necessary member functions required by the iterator concept, such as operator*, operator++, operator==, and operator!=.

 The begin() member function returns an iterator pointing to the first element of the vector (i.e., the data_ pointer). The end() member function returns an iterator pointing to the position just after the last element of the vector (i.e., data_ + size_).

 In the main function, a for loop is used to iterate over the elements of myVector using begin() and end() iterators. The operator* is used to dereference the iterator and access the element.

 Note that this is a simplified implementation of iterators for MyVector. In practice, iterators typically support more functionality like bidirectional or random access. The standard library provides the std::vector container with iterators that offer a complete implementation of the iterator concept.
 
 rValue
 
 we have introduced an rvalue reference constructor MyVector(MyVector&& other) and an rvalue reference assignment operator operator=(MyVector&& other). These new functions take an rvalue reference to another MyVector object, allowing the transfer of ownership of the data from the source object to the destination object. After the transfer, the source object's data_ pointer is set to nullptr to avoid double deletion of the data in the destructor.

 In the main function, we can still create MyVector objects using the default constructor, and elements can be added using push_back as before. The range-based for
 
 In this updated code:  std::unique_ptr<T[]> data_;

 std::unique_ptr is used instead of raw pointers to manage the dynamically allocated array data_. This provides automatic memory management and ensures proper resource cleanup.
 The move constructor and move assignment operator use std::move to transfer ownership of the std::unique_ptr from the source object to the destination object.
 The default keyword is used to define a default destructor for MyVector, taking advantage of the default destructor implementation provided by the compiler.
 std::make_unique is used to create a std::unique_ptr with the specified size
 
 
 In the line data_ = std::move(newData);, using std::forward is not appropriate in this context.

 The std::forward function is typically used in forwarding references (also known as universal references) to preserve value category (lvalue or rvalue) and to enable perfect forwarding. It is mainly used in template code where type deduction takes place.

 In the case of data_ = std::move(newData);, we are explicitly moving the std::unique_ptr from newData to data_ using std::move. The purpose of std::forward is to preserve the value category of a function argument when forwarding it to another function template. Since data_ is not a function argument, but rather an object being assigned to, using std::forward is not necessary.

 Using std::move in this case is appropriate and sufficient for transferring ownership of the std::unique_ptr from newData to data_. It conveys the intention of moving the ownership of the dynamically allocated array from one object to another.
 
 std::unique_ptr<T[]> data_;
 
 
 This version utilizes the member initialization list to initialize data_, size_, and capacity_ by calling the move assignment operator of std::unique_ptr and copying the values from other. The destructor of std::unique_ptr will automatically release the resources previously held by data_ when other is destroyed.

 This approach simplifies the code and takes advantage of the default behavior of std::unique_ptr, reducing the risk of potential errors and ensuring proper resource management.
 
 Note that this is a simplified implementation of iterators for MyVector. In practice, iterators typically support more functionality like bidirectional or random access. T
 
 */
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

    MyVector() : data_(nullptr), size_(0), capacity_(0) {}

    MyVector(MyVector&& other) noexcept : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
/*
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

 */
    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            //  using std::forward is not appropriate in this context.
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
                //         begin                  end        destination
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
        return iterator(data_.get()); // vector.get() gets the address
    }

    iterator end() {
        return iterator(data_.get() + size_);
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
