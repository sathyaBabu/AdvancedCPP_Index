//
//  main.cpp
//  co3_ThreadMutex
//
//  Created by Sathya Babu on 01/12/21.
//

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;


std::mutex mut;

int myCash = 0 ;
void addMoney(){
    
    mut.lock();
    
        ++myCash ;   //  critical section
    
    mut.unlock();
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::thread t1 ( addMoney );
    std::thread t2 ( addMoney );
    t1.join();
    t2.join();
    
    return 0;
}
