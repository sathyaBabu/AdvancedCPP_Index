//
//  main.cpp
//  ComposeBetterWay
//
//  Created by Sathya Babu on 10/07/23.
//


/*
 
  Works :
 In this example, the compose function now accepts variadic template parameters Funcs... fs,
 representing the multiple functions to be composed. The compose function uses recursion to
 compose the functions one by one. When there are no more functions to compose (sizeof...(fs) == 0),
 it returns the last function f. Otherwise, it returns a lambda function that invokes the current function f
  with the result of recursively calling compose with the remaining functions fs.

 You can now pass multiple functions to the compose function, and it will compose them in the order you specify.
 
 */


#include <iostream>
#include <functional>

template<typename Func, typename... Funcs>
auto compose(Func f, Funcs... fs) {
    if constexpr (sizeof...(fs) == 0) {
        return f;
    } else {
        return [=](auto... args) {
         //   return [=](auto&&... args) {
            return f(compose(fs...)((args)...));
           // return f(compose(fs...)(std::forward<decltype(args)>(args)...));
        };
    }
}

int addOne(int x) {
    return x + 1;
}

int multiplyByTwo(int x) {
    return x * 2;
}

int subtractThree(int x) {
    return x - 3;
}

int divideByFour(int x) {
    return x / 4;
}

int main() {
    auto composedFunc = compose(addOne, multiplyByTwo, subtractThree, divideByFour);
    //                             5           4                2             5

    int result = composedFunc(20);

    std::cout << "Result: " << result << std::endl;  // Output: 10

    return 0;
}
// Result: 5
