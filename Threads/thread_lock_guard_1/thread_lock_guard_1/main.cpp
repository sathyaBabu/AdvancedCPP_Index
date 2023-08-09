//
//  main.cpp
//  thread_lock_guard_1
//
//  Created by Sathya Babu on 06/08/23.
//
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
/*
 In this code, we have a criticalSection function that is called by multiple threads concurrently. The function contains a critical section of code that needs to be protected from concurrent access. We achieve this by creating a std::mutex named myMutex, and then we use std::lock_guard to lock the mutex before entering the critical section. The std::lock_guard ensures that the mutex is locked when it is constructed and unlocks it when it is destroyed (at the end of the scope).

 As a result, only one thread at a time can execute the critical section, preventing any race conditions and ensuring that the output is consistent and without any interleaving.
 */
std::mutex myMutex;

void criticalSection(int threadId) {
    // Lock the mutex using std::lock_guard
    std::lock_guard<std::mutex> lock(myMutex);

    // This section is now protected by the mutex
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << threadId << " is executing iteration " << i << std::endl;
    }
}

int main() {
    std::vector<std::thread> threads;

    // Create 5 threads and run the criticalSection function concurrently
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(criticalSection, i);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
/*
 
 Thread 0 is executing iteration 0
 Thread 0 is executing iteration 1
 Thread 0 is executing iteration 2
 Thread 0 is executing iteration 3
 Thread 0 is executing iteration 4
 Thread 1 is executing iteration 0
 Thread 1 is executing iteration 1
 Thread 1 is executing iteration 2
 Thread 1 is executing iteration 3
 Thread 1 is executing iteration 4
 Thread 3 is executing iteration 0
 Thread 3 is executing iteration 1
 Thread 3 is executing iteration 2
 Thread 3 is executing iteration 3
 Thread 3 is executing iteration 4
 Thread 4 is executing iteration 0
 Thread 4 is executing iteration 1
 Thread 4 is executing iteration 2
 Thread 4 is executing iteration 3
 Thread 4 is executing iteration 4
 Thread 2 is executing iteration 0
 Thread 2 is executing iteration 1
 Thread 2 is executing iteration 2
 Thread 2 is executing iteration 3
 Thread 2 is executing iteration 4
 */
