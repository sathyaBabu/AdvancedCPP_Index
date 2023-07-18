//
//  main.cpp
//  co3_Threads_1
//
//  Created by Sathya Babu on 01/12/21.
//
/*
   Threads :
     
        cpu : sockets  -> 2 threads... cycles from the sockets
        10/50/200 -> thread pool
 
                         A  (1/4ms) local stack of your OS( PID )
 
                B                    C
 
                          D
 
 
     
 AsyncThread, defered threads..
                        Will not use the stack!!!
      Socket : 2 threads..
 
 */

#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <future>
using namespace std;
using namespace std::chrono;


typedef unsigned long long ull ;

ull EvenSum = 0 ;

ull OddSum = 0 ;

void findEven( ull start , ull end )
{
    for( ull i = start ; i <= end ; i++){
        if( i % 2 ){
            EvenSum += i ;
        }
    }
}


void findODD( ull start , ull end )
{
    for( ull i = start ; i <= end ; i++){
        if( !(i % 2) ){
            OddSum += i ;
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    ull start = 0 , end = 1900000000;
    auto startTime = high_resolution_clock::now();

    
    
    // Phase III
    
    std::thread t3( [ & ] { this_thread::sleep_for(3s); std::cout <<endl; }) ;
    std::thread t1( [ & ] {(findEven,start,end); }) ;
    std::thread t2( [ & ] {(findODD,start,end); } );
    
    t1.join();
    t2.join();
    t3.join();
    
    
    // Phase II
//            std::thread t1( findEven, start,end);
//            std::thread t2( findODD,  start,end);  // executed by thread in 2 sec..
//
//            t1.join();
//            t2.join();  // wait
//
//           // t1.detach();
//            if( t1.joinable())
//            {
//                t1.join();
//
//            }
                    
      
    
    
    // Phase I
    
//        findEven(start, end);   // Sec : 8
//        findODD(start, end);
//
    
    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);
    
    cout << " Executed even sum : "<<  endl;
    cout << " Executed Odd  sum : "<<  endl;
    
    cout << " Sec : "<< duration.count()/1000000 << endl;
    
    
    return 0;
}
