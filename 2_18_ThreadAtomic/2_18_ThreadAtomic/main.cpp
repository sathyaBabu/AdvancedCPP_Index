//
//  main.cpp
//  2_18_ThreadAtomic
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include <atomic>         // std::atomic, std::memory_order_relaxed
#include <thread>         // std::thread
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    
    std::atomic< int > counter = 0 ;
    
//    int counter = 0 ;
    
    
    auto work = [ &counter ] () {
        
        for( int i = 0 ; i < 1000 ; i += 1 ){
            counter += 1 ;
        }
    };
    
    
    std::thread t1( work );
    std::thread t2( work );
    
    t1.join();
    t2.join();
    
    cout << "counter = " << counter << endl ;
    
    
    return 0;
}
