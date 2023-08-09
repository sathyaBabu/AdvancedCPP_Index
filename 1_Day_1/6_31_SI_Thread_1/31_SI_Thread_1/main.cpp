//
//  main.cpp
//  31_SI_Thread_1
//
//  Created by Sathya Babu on 31/07/23.
//


/*
 
 
     stack...
 
     A B C D   needs time slice  ????
 
    processor CPU 4   4   Core[  GZh ]  x 2   thread = 16 threads..   /2 = 8 OS 8 for us..
 
    50 threads...
    thread pool executor ( 100 )
 
      -  -    -   -  -  -   -  -
 
 
    C++ 20 / kotlin     coRoutine  will not use the stack it works on heap..
 
     core x 1 million threads...
 
 
 
 
 
 */

#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <future>

using namespace std;
using namespace std::chrono;

typedef unsigned long  long ull ;


ull OddSum = 0 ;
ull EvenSum = 0 ;


void findEven( ull start , ull end){
   
    cout << " Thread ID  of findEven" << std::this_thread::get_id() << endl;
    for( ull i = start; i <= end ; ++i){
        if( i % 10){
            EvenSum += i ;
            
        }
    }
    
    
}


void findOdd( ull start , ull end){
  
    cout << " Thread ID  of findEven" << std::this_thread::get_id() << endl;
    for( ull i = start; i <= end ; ++i){
        if( !(i % 10) ){
            OddSum += i ;
           
        }
    }
    
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << " Just About threads... !\n";
    
    
    ull start = 0 , end = 1900000000;
    
    auto startTime = high_resolution_clock::now();
    
    
    // Phase I   Sec : 6
//
//    findOdd( start,end);
//    findEven( start,end);
    
    
    // Phase II 3 sec..
    
    std::thread t1( findEven ,start, end    );   //1/4 ms blocking
    
    std::thread t2( findOdd,start, end    );
    
    //  run blocking threads  kicks in..
    
    t1.join();
    t2.join();
    
    
    // Async threads are non blocking threads.. parallal threads...
    
    
    
    
    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);
    
    cout << " Even Sum : " << EvenSum << endl;
    cout << " Odd  Sum : " << OddSum << endl;
    
    cout << " Job done..." << endl ;

    cout <<  " Sec : "<< duration.count()/1000000 << endl;
    
    
    
    
    
}
/*
 
 Just About threads... !
 Thread ID  of findEven0x16fe87000
 Thread ID  of findEven0x16ff13000
 Even Sum : 1624500000000000000
 Odd  Sum : 180500000950000000
 Job done...
 Sec : 3
Program ended with exit code: 0
 */
