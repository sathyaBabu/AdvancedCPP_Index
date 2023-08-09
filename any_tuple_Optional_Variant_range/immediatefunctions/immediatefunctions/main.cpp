//
//  main.cpp
//  immediatefunctions
//
//  Created by Sathya Babu on 19/07/23.
//

#include <iostream>
consteval int add(int a, int b) {
    return a + b;
}

int main() {
    constexpr int result = add(5, 3);  // Evaluated at compile-time
    std::cout << result << std::endl; // Output: 8

    int x, y;
    std::cin >> x >> y;
    // ERROR : Call to consteval function 'add' is not a constant expression
    // Works : when we change this to consteval -> constexpr
       int dynamicResult = add(x, y);    // Evaluated at runtime
    std::cout << dynamicResult << std::endl;

    return 0;
}
