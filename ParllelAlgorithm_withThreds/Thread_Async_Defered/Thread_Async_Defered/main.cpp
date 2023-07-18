//
//  main.cpp
//  Thread_Async_Defered
//
//  Created by Sathya Babu on 27/10/21.
//

#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <future>
using namespace std;
using namespace std::chrono;

typedef long  ull ;

ull findEven( ull start , ull end){
    ull EvenSum = 0 ;
    cout << " Thread ID  of findEven" << std::this_thread::get_id() << endl;
    for( ull i = start; i <= end ; ++i){
        if( i % 10){
            EvenSum += i ;
        }
    }
    return EvenSum ;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Defered Vs Async !\n";
    
    
    ull start = 0 , end = 1900000000;
    
    cout << " Thread created for Deffered - Async  " << endl;
    
    cout << " Thread ID " << std::this_thread::get_id() << endl;
    // remember deffered policy works on a single thread Async on a diffrent thread
    
    //std:future<ull> EvenSum = std::async(std::launch::deferred, findEven,start,end);
       std:future<ull> EvenSum = std::async(std::launch::async, findEven,start,end);
    
    
    
    cout << " Waiting for th result!! " << endl;
    cout << " Even Sum : " << EvenSum.get() << endl;
    
    cout << " Job done..." << endl ;
    
    
    
    
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
