//
//  main.cpp
//  17_Iterator_1
//
//  Created by Sathya Babu on 18/02/23.
//
/*
 The Iterator pattern in C++17 is used to provide a way to access the elements of a container without exposing the internal structure of the container.

 Here is an example implementation of the Iterator pattern in C++17:
 
 In this example, we have an Iterator abstract base class, which provides a common interface for iterating over elements. We also have an Aggregate abstract base class, which provides a common interface for creating iterators.

 We then have concrete subclasses ConcreteIterator and ConcreteAggregate, which provide concrete implementations of the Iterator and Aggregate interfaces, respectively.

 In the main function, we create a ConcreteAggregate object with a vector of integers, and we use its createIterator method to create a new iterator. We then iterate over the elements in the container using the iterator's first, next, isDone, and currentItem methods.

 This implementation of the Iterator pattern provides a way to access the elements of a container without exposing its internal structure. It also allows for different types of iterators to be created for the same container, allowing for greater flexibility in accessing container elements.
 
 1
 2
 3
 4
 5
 Program ended with exit code: 0
 */

#include <vector>
#include <iostream>

class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual int currentItem() const = 0;
};

// Provider
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator> createIterator() = 0;
};

// wil not inspect data of the class..
class ConcreteIterator : public Iterator {
public:
    ConcreteIterator(const std::vector<int>& data)
        : data_{data} {}

    void first() override {
        index_ = 0;
    }

    void next() override {
        ++index_;
    }

    bool isDone() const override {
        return index_ >= data_.size();
    }

    int currentItem() const override {
        return data_[index_];
    }

private:
    const std::vector<int>& data_;
    size_t index_ = 0;
};

class ConcreteAggregate : public Aggregate {
public:
    explicit ConcreteAggregate(const std::vector<int>& data)
        : data_{data} {}

    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<ConcreteIterator>(data_);
    }

private:
    const std::vector<int> data_;
};

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    ConcreteAggregate aggregate(data);
    auto it = aggregate.createIterator();

    for (it->first(); !it->isDone(); it->next()) {
        std::cout << it->currentItem() << std::endl;
    }
}
/*
 1
 2
 3
 4
 5
 Program ended with exit code: 0
 */
