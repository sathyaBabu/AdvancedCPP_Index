//
//  main.cpp
//  17_apply_onTuppleFun_arg
//
//  Created by Sathya Babu on 17/05/23.
//
//
//  main.cpp
//  17_tuple_Function_variadic_Expr_WRKS
//
//  Created by Sathya Babu on 16/05/23.
//
#include <iostream>
#include <tuple>
#include <functional>


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

/*
 Result: 6
 Program ended with exit code: 0
 */
