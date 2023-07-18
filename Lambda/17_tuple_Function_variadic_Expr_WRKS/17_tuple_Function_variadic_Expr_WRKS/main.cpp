//
//  main.cpp
//  17_tuple_Function_variadic_Expr_WRKS
//
//  Created by Sathya Babu on 16/05/23.
//
#include <iostream>
#include <tuple>
#include <functional>

// Function to add two integers
int add(int a, int b) {
    return a + b;
}

// Function to multiply two floats
float multiply(float a, float b) {
    return a * b;
}

// Function to concatenate two strings
std::string concatenate(const std::string& str1, const std::string& str2) {
    return str1 + str2;
}

// Function to print the result
template<typename... Funcs, typename... Args>
void printResult(const std::tuple<std::function<Funcs>...>& tuple, Args&&... args) {
    auto invokeFunction = [&](auto&& func) {
        using FunctionType = std::decay_t<decltype(func)>;
        if constexpr (std::is_invocable_v<FunctionType>) {
            std::cout << "Result: " << func() << std::endl;
        } else {
            std::cout << "Error: Invalid function" << std::endl;
        }
    };

    std::apply([&](auto&&... funcs) {
        ( invokeFunction(funcs), ... );
    }, tuple);
}

int main() {
    // Compose a tuple with function pointers
    std::tuple<std::function<int()>, std::function<float()>, std::function<std::string()>> funcTuple(
        []() { return add(3, 4); },
        []() { return multiply(2.5f, 6.3f); },
        []() { return concatenate("Hello", "World"); }
    );

    // Call the functions using the tuple
    printResult(funcTuple); // Call each function with no arguments

    return 0;
}
/*
 Result: 7
 Result: 15.75
 Result: HelloWorld
 Program ended with exit code: 0
 */
// std::apply
/*
 
 #include <iostream>
 #include <tuple>

 // Function to add three integers
 int add(int a, int b, int c) {
     return a + b + c;
 }

 int main() {
     // Create a tuple of arguments
     std::tuple<int, int, int> args(1, 2, 3);

     // Apply the add function to the tuple of arguments
     int result = std::apply(add, args);

     // Print the result
     std::cout << "Result: " << result << std::endl;

     return 0;
 }

 */
