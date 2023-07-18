//
//  main.cpp
//  17_Threads_2
//
//  Created by Sathya Babu on 26/05/23.
//
#include <iostream>
#include <vector>
#include <thread>
using namespace std;
//std::mutex mutex;

template <typename Func, typename Iterator>
void executeThreads(Func&& func, Iterator begin, Iterator end) {
    std::vector<std::thread> threads;
    for (auto it = begin; it != end; ++it) {
        
        std::lock_guard<std::mutex> lock(mutex);
        std::this_thread::sleep_for(std::chrono::seconds(3)); // block for 3 sec
        threads.emplace_back(std::forward<Func>(func), std::ref(*it));
    }

    // Join the threads
    for (auto& thread : threads) {
        cout << thread.get_id() << endl;
        thread.join();
    }
}

void printValue(int& value) {
    
    std::cout << "Value: " << value << std::endl;
}
// to pass raw numbers
void printValue2(int value) {
    
    std::cout << "Value: " << value << std::endl;
}

int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};

    executeThreads(printValue, values.begin(), values.end());
    
    std::vector< std::thread > threads2;

    
    cout << " Phase II \n ";
    
    std::thread tt1( printValue2, 100);
    std::thread tt2( printValue2, 200);
    tt1.join();
    tt2.join();
    
    cout << " Phase III \n ";
    
    // to pass raw numbers
    threads2.emplace_back( printValue2, 10);
    threads2.emplace_back( printValue2, 20);
    threads2.emplace_back( printValue2, 30);
    
    for (auto& thread : threads2) {
            thread.join();
        }

    return 0;
}
/*
 
 
 
 Value: 1
 Value: 2
 Value: 3
 Value: 4
 0x16fe87000
 Value: 5
 0x16ff13000
 0x16ff9f000
 0x17002b000
 0x1700b7000
 
 Phase II
 Value: 10
Value: 20
Value: 30
Program ended with exit code: 0
 Program ended with exit code: 0
 */
