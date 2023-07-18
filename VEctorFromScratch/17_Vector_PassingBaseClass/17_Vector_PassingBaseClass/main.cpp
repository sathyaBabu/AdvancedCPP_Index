//
//  main.cpp
//  17_Vector_PassingBaseClass
//
//  Created by Sathya Babu on 28/04/23.
//
#include <iostream>
#include <vector>
#include <memory>

class BaseClass {
public:
    virtual void print() = 0;
};

class DerivedClass1 : public BaseClass {
public:
    void print() override {
        std::cout << "This is DerivedClass1" << std::endl;
    }
};

class DerivedClass2 : public BaseClass {
public:
    void print() override {
        std::cout << "This is DerivedClass2" << std::endl;
    }
};

void print_vector(const std::vector<std::shared_ptr<BaseClass>>& vec) {
    for (const auto& ptr : vec) {
        ptr->print();
    }
}

int main() {
    std::vector<std::shared_ptr<BaseClass>> vec;
    vec.push_back(std::make_shared<DerivedClass1>());
    vec.push_back(std::make_shared<DerivedClass2>());
    print_vector(vec);
    return 0;
}
