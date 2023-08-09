//
//  main.cpp
//  2_16_ThreadsMutex
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int myCash = 0 ;

std::mutex m ;
// 1/4 ms

void addMoney()
{
    m.lock();
      
       ++myCash;
    
    m.unlock();
    
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Mutex \n";
    
    
    std::thread t1(addMoney );
    std::thread t2(addMoney );
    
    t1.join();
    t2.join();
    
    cout << myCash << endl;
    
    return 0;
}
// Mutex
//2
