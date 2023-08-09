//
//  main.cpp
//  17_Clamp_Simple_MultiBounds_1
//
//  Created by Sathya Babu on 19/04/23.
//
/*
 We can modify the clamp function to accept multiple pairs of lowerBound and upperBound values and apply them sequentially. Here's an example:
 
 In this example, we have modified the clamp function to accept a std::vector of pairs, where each pair represents a lower and upper bound. The function then applies each bound sequentially using std::clamp and returns the final result.

 In the main function, we define a double value and a vector of pairs representing the bounds. We then call the clamp function with these values and print the result.
 */
#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
T clamp(T value, const std::vector<std::pair<T, T>>& bounds) {
//    for (const auto& bound : bounds) {
//        value = std::clamp(value, bound.first, bound.second);
//    }
    
    //  as me as above but a better way to code..
    
    for (const auto& [ first, second  ]: bounds) {
        value = std::clamp(value, first,  second);
    }
    return value;
}

int main() {
    double value = 10.5;
    std::vector<std::pair<double, double>> bounds = {{0.0, 5.0}, {8.0, 12.0}};
    double result = clamp(value, bounds);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
// Result: 8

