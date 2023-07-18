//
//  main.cpp
//  19_Si_seq_par
//
//  Created by Sathya Babu on 10/07/23.
//




#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include<execution>

int numElems = 1000;


int display(int& x){
    x *= 2 ;
    return x ;
}
int main() {
    std::vector<int> nums = {5, 2, 4, 1, 3};
    for (int i=0; i<numElems; ++i) {
      nums.emplace_back( i * 10 );
    }

    // Start the timer
    auto startTime = std::chrono::high_resolution_clock::now();

    // Perform the for_each algorithm in parallel
    // (std::execution::seq  12 ms
    // (std::execution::par  9 ms
    
    
    // remember I have not installed 20 - 23
    // std::execution::seq,
    std::for_each(  nums.begin(), nums.end(), display);
    
    
    // Stop the timer
        auto endTime = std::chrono::high_resolution_clock::now();

        // Calculate the elapsed time
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

        // Print the modified vector
        std::cout << "Modified vector: ";
        for (int num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        // Print the execution time
        std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
/*
 19960 19980
 Execution time: 5 microseconds
 
 
 */


// https://www.programiz.com/cpp-programming/online-compiler/

