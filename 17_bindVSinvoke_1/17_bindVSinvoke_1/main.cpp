//
//  main.cpp
//  17_bindVSinvoke_1
//
//  Created by Sathya Babu on 28/03/23.
//
/*
 
 std::bind and std::invoke are two different utilities in C++ that serve different purposes.

 std::bind is a function template that creates a callable object that binds a function or function object to a set of arguments. The resulting callable object can be invoked later with any additional arguments. It is often used to create a function object with pre-bound arguments.

 std::invoke is a function template that provides a uniform way to call a callable object, whether it is a function pointer, a member function pointer, a function object or a lambda expression. It can be used to call a function object without knowing its specific type.

 Here is an example to demonstrate the difference between the two:
 
 In this example, std::bind is used to create a callable object that binds the first argument of foo to 1 and the second argument to a placeholder _1. The resulting function object can then be invoked with an additional argument, which will be passed as the second argument to foo.

 Similarly, std::bind is used to create a callable object that binds the member function bar of Bar to an instance of Bar and the first argument to a placeholder _2 and the second argument to a placeholder _1. The resulting function object can then be invoked with two additional arguments, which will be passed as the first and second arguments to bar.

 On the other hand, std::invoke is used to call a function or member function without creating a function object. In this example, it is used to call the function foo and the member function bar directly with the appropriate arguments.
 
 */
#include <iostream>
#include <functional>

void foo(int x, int y) {
    std::cout << "foo(" << x << ", " << y << ")" << std::endl;
}

class Bar {
public:
    void bar(int x, int y) {
        std::cout << "Bar::bar(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    // Example with std::bind
    auto f1 = std::bind(foo, 1, std::placeholders::_1);
    f1(2); // calls foo(1, 2)

    Bar b;
    auto f2 = std::bind(&Bar::bar, &b, std::placeholders::_2, std::placeholders::_1);
    f2(3, 4); // calls b.bar(4, 3)

    // Example with std::invoke
    std::invoke(foo, 5, 6); // calls foo(5, 6)

    Bar b2;
    std::invoke(&Bar::bar, &b2, 7, 8); // calls b2.bar(7, 8)

    return 0;
}
/*
 foo(1, 2)
 Bar::bar(4, 3)
 foo(5, 6)
 Bar::bar(7, 8)
 Program ended with exit code: 0
 */
