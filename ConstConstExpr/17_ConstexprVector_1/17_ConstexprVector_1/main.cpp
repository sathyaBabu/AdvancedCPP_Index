//
//  main.cpp
//  17_ConstexprVector_1
//
//  Created by Sathya Babu on 23/03/23.
//
/*
 In this code, we are trying to initialize a and b with the size of a std::vector<int>. Since the size of the vector cannot be determined at compile-time, the constexpr variable b will result in a compile-time error, while the const variable a will be initialized at run-time.

 So, in summary, we should use constexpr when we know that the value of the variable can be evaluated at compile-time, while we should use const for all other cases.
 */
#include <iostream>
#include <vector>

int main() {
  const int a = std::vector<int>{1, 2, 3}.size();
  constexpr int b = std::vector<int>{1, 2, 3}.size();
  
  std::cout << a << std::endl;
  std::cout << b << std::endl;
}
