//
//  main.cpp
//  Consteval_constexpr
//   Immediate functions
//  Created by Sathya Babu on 11/07/23.
//
/*
 
 Immediate functions
 Similar to constexpr functions, but functions with a consteval specifier must produce a constant. These are called immediate functions.
 
 
 The consteval keyword in C++20 is used to indicate that a function must be evaluated at compile-time. It ensures that the function is called only in constant expressions and requires the compiler to perform the evaluation during compilation.

 Here's an example code that demonstrates the usage of consteval:

 cpp

 
 In this example, the square function is declared with the consteval keyword. It calculates the square of an integer and returns the result. Since the square function is marked as consteval, it can only be called in constant expressions.

 In the main function, we call the square function with the argument 5. Since 5 is known at compile-time, the compiler evaluates the square function during compilation and assigns the result to the constexpr variable result. The value 25 is then printed to the console.

 Note that consteval functions are subject to stricter restrictions than regular constexpr functions. They must be simple, deterministic, and evaluated at compile-time. They cannot have side effects or rely on runtime behavior.

 consteval is useful in scenarios where you want to ensure compile-time evaluation of a function to optimize performance or enforce constraints at compile-time.

 Please keep in mind that consteval is a C++20 feature and may not be available in older compilers.
 
 */
#include <iostream>
                                // cant be  const
consteval int square(int x) {  // works similer : constexpr int square(int x)
    return x * x;
}

int main() {
    constexpr int result = square(5);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
// Result: 25
