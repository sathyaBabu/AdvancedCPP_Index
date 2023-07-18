//
//  main.cpp
//  Thread_1
//
//  Created by Sathya Babu on 10/07/23.
//



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
    
            // Phase II
//            std::thread t1(findEven, start, end);  // 3 sec
//            std::thread t2(findOdd, start, end);
//
//            t1.join();
//            t2.join();
//    // Phase I
    findOdd(start,end );  //  // 8 sec
    findEven(start,end);
    
    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);
    
    cout << " Even Sum : " << EvenSum << endl;
    cout << " Odd  Sum : " << OddSum << endl;
    
    cout << " Job done..." << endl ;

    cout <<  " Sec : "<< duration.count()/1000000 << endl;
    
    
    
    
    return 0;
}
/*
 Defered Vs Async !
  Thread created for Deffered - Async
  Thread ID 0x1000e7d40
  Waiting for th result!!
  Even Sum :  Thread ID  of findEven0x16fe87000
 1624500000000000000
  Job done...
 Program ended with exit code: 0
 */
