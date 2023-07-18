//
//  main.cpp
//  17_Parallel_Algo_Basic
//
//  Created by Sathya Babu on 16/06/23.
// https://www.programiz.com/cpp-programming/online-compiler/

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <chrono>

int square(int num) {
    // Simulating some computation
    for (int i = 0; i < 10000000; ++i) {
        // Do some work
    }
    return num * num;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Perform a parallel transform using std::transform and std::execution::par
    std::vector<int> squaredNumbers(numbers.size());
    
    auto startTime = std::chrono::high_resolution_clock::now();

    //  std::execution::par,
    

    std::transform(std::execution::par, numbers.begin(), numbers.end(),squaredNumbers.begin(), square);

    // Print the squared numbers
    std::cout << "Squared numbers: ";
    
    // Print the modified vector
      for (int num : squaredNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
 
   
    
     auto endTime = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    auto duration = std::chrono::duration_cast< std::chrono::microseconds >(endTime - startTime )  ;

    

    // Print the execution time
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;


    return 0;
}
/*
 
 std::transform( numbers.begin(), numbers.end(),squaredNumbers.begin(), square);
 Squared numbers: 1 4 9 16 25
 Execution time: 93316 microseconds
 
 
 std::transform(std::execution::par, numbers.begin(), numbers.end(),squaredNumbers.begin(), square);

 Execution time:73099  microseconds
 
 
 std::transform(std::execution::seq, numbers.begin(), numbers.end(),squaredNumbers.begin(), square);
 Squared numbers: 1 4 9 16 25
 Execution time: 48269 microseconds


 */
