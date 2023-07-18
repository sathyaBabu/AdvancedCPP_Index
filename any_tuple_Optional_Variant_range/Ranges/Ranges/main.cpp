//
//  main.cpp
//  Ranges
//
//  Created by Sathya Babu on 11/07/23.
//
/*
 In this code, the range function returns a range view using the std::views::iota function. The std::views::iota function creates a range of integers starting from start and ending before end. This range can be iterated over using a range-based for loop, as shown in the main function. The loop will iterate over the numbers from 0 to 9 and print each number.
 */
#include <iostream>
#include <ranges>

auto range(int start, int end) {
    return std::views::iota(start, end);
//    return start++;
}

int main() {
    
    // creates a range with begin() and end()
    for (int i : std::ranges::iota_view{1, 10})
           std::cout << i << ' ';
    
       std::cout << '\n';
    
       for (int i : std::views::iota(1, 10))
           std::cout << i << ' ';
    
       std::cout << '\n';
   
    for (int n : range(0, 10)) {
        std::cout << n << std::endl;
    }
    
    
    
    return 0;
}
/*
 1 2 3 4 5 6 7 8 9
 1 2 3 4 5 6 7 8 9
 0
 1
 2
 3
 4
 5
 6
 7
 8
 9
 Program ended with exit code: 0
 */
