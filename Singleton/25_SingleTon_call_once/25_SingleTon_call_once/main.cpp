//
//  main.cpp
//  25_SingleTon_call_once
//
//  Created by Sathya Babu on 25/04/23.
//
/*
The purpose of std::call_once is to ensure that a specific block of code is executed exactly once,
even in a multithreaded environment where multiple threads may attempt to execute the
code simultaneously. The std::call_once function uses a synchronization mechanism to ensure that the block of code is executed by only one thread, while other threads wait for it to complete.
*/

#include <mutex>
#include<iostream>
using namespace std ;

class Singleton {
public:
     static
     Singleton& getInstance() {
         // std::once_flag used to ensure that the initialization code is executed only once.
        std::call_once(flag_, []() { instance_ = new Singleton(); } );
        return *instance_;
    }

private:
    Singleton() {}

    static Singleton* instance_;
    static std::once_flag flag_;
};

Singleton* Singleton::instance_ = nullptr;
std::once_flag Singleton::flag_;

int main() {
//    Singleton& s1 = Singleton::getInstance();
//    Singleton& s2 = Singleton::getInstance();

    
    Singleton& s1 = s1.getInstance();
    Singleton& s2 = s2.getInstance();

    if (&s1 == &s2) {
        std::cout << "Singleton works!" << std::endl;
    }

    return 0;
}

// Singleton works!
