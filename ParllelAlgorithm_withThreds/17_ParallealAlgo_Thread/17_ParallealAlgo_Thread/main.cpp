//
//  main.cpp
//  17_ParallealAlgo_Thread
//
//  Created by Sathya Babu on 16/06/23.
//
#include <iostream>
#include <thread>
#include <vector>
using namespace std ;

// Function to be executed in parallel
void performTask(int id) {
    std::cout << "Thread " << id << " started" << std::endl;
    cout << "  performTask Thread  ID : "<< std::this_thread::get_id() << endl;
    // Simulating some computation
    for (int i = 0; i < 10000000; ++i) {
        // Do some work
    }
    std::cout << "Thread " << id << " finished" << std::endl;
}

int main() {
    // Number of threads to be created
    int numThreads = 4;

    // Vector to hold the thread objects
    std::vector<std::thread> threads;
    cout << " Main  Thread  ID : "<< std::this_thread::get_id() << endl;

    // Create and start the threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(performTask, i);
    }

    // Join the threads
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "All threads finished" << std::endl;

    return 0;
}
/*
 Thread Thread 0 started
 Thread 2 started
 3 started
 Thread 1 started
 Thread 2 finished
 Thread 0 finished
 Thread 3 finished
 Thread 1 finished
 All threads finished
 Program ended with exit code: 0
 */
