//
//  main.cpp
//  17_apply_vs_invoke
//
//  Created by Sathya Babu on 13/07/23.
//
#include <iostream>
#include <functional>
#include <tuple>
/*
 
 we have a printSum function that takes two integer arguments and prints their sum. We also have a Foo struct with a member function printProduct that takes two double arguments and prints their product.

 Using std::apply, we create a tuple args containing the arguments (10, 20). We then pass this tuple to std::apply, along with the function printSum. std::apply expands the tuple and passes its elements as separate arguments to the function, resulting in a call to printSum(10, 20).

 Using std::invoke, we create an instance of Foo and invoke its member function printProduct using the address-of operator &. We pass the instance foo as the first argument, followed by the remaining arguments (2.5, 3.5).
     std::invoke internally handles the member function invocation, resulting in a call to foo.printProduct(2.5, 3.5).

 Both std::apply and std::invoke are useful for invoking callable objects with arguments, but
 
 
       std::apply is specifically designed to work with tuples and unpack their elements as arguments, while
 
       std::invoke can handle different types of callable objects and member functions.
 
 */
void printSum(int a, int b) {
    std::cout << "Sum: " << (a + b) << std::endl;
}

struct Foo {
    void printProduct(double x, double y) {
        std::cout << "Product: " << (x * y) << std::endl;
    }
};

int main() {
    // Example using std::apply
    auto args = std::make_tuple(10, 20);
    std::apply(printSum, args);  // Equivalent to printSum(10, 20)

    // Example using std::invoke
    Foo foo;
    std::invoke(&Foo::printProduct, foo, 2.5, 3.5);  // Equivalent to foo.printProduct(2.5, 3.5)

    return 0;
}
/*
 
 Sum: 30
 Product: 8.75
 Program ended with exit code: 0
 */
