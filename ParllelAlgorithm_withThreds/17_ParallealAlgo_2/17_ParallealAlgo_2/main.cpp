//
//  main.cpp
//  17_ParallealAlgo_2
//
//  Created by Sathya Babu on 25/05/23.
//  A code to represent parallel algorithm

/*
 
 In this example, we have a vector of integers data. We want to apply a computation-intensive task represented by the compute function to each element of the vector in parallel using asynchronous threads.

 The program launches asynchronous tasks using std::async with the std::launch::async policy. Each task is assigned to a separate asynchronous thread, which executes the compute function on the respective element of data.

 The std::async function returns a std::future object, which represents the result of the asynchronous task. We store these std::future objects in a vector futures.

 After launching all the tasks, we iterate over the futures vector and wait for each task to complete using the wait member function of std::future. This ensures that we synchronize with the completion of all the asynchronous tasks.

 Finally, we output the results stored in the data vector.

 Note that the number of threads created by std::async may vary depending on the implementation and the system's capabilities. The actual parallelism achieved may also depend on various factors, such as the number of available CPU cores and the workload distribution.

 Keep in mind that using asynchronous threads introduces some overhead due to thread creation and synchronization. It's important to carefully consider the balance between the computational workload and the cost of parallelization.
 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

void compute(int value) {
    // Simulate some computationally intensive task
    for (int i = 0; i < 1000000; ++i) {
        value *= 2;
    }
}

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};

    std::vector<std::future<void>> futures;

    // Launch asynchronous tasks
    for (auto& value : data) {
        futures.emplace_back(std::async(std::launch::async, compute, std::ref(value)));
    }

    // Wait for the tasks to complete
    for (auto& future : futures) {
        future.wait();
    }

    // Output the results
    for (const auto& value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
// 1 2 3 4 5
