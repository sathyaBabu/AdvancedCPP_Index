//
//  main.cpp
//  31_SI_ThreadsAsyncDef
//
//  Created by Sathya Babu on 31/07/23.
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

ull EvenSum = 0 ;

ull OddSum = 0 ;

ull findEven( ull start , ull end )
{
    ull EvenSum = 0 ;
    
    cout << "  Find Even Async Thread  ID : "<< std::this_thread::get_id() << endl;
    
    for( ull i = start ; i <= end ; i++){
        if( i % 2 ){
            EvenSum += i ;
        }
    }
    return EvenSum;
}



ull findODD( ull start , ull end )
{
    ull EvenSum = 0 ;
    cout << "  Find ODD Async Thread  ID : "<< std::this_thread::get_id() << endl;
    
    for( ull i = start ; i <= end ; i++){
        if( !(i % 2) ){
            OddSum += i ;
        }
    }
    return  OddSum;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Just about t hreads...!\n";
    
    ull start = 0 , end =  1900000000;
    
    // Co routines.. Faster..
    auto startTime = high_resolution_clock::now();

 cout << " main()  Async Thread  ID : "<< std::this_thread::get_id() << endl;
    
    
    //// Body of our work
    ///
        
//    std::future< ull >  EvenSum = std::async( std::launch::async, findEven, start, end );
//    std::future< ull >  EvenOdd = std::async( std::launch::async, findODD, start, end );
//
//
    
    
std::future< ull >  EvenSum = std::async( std::launch::deferred, findEven, start, end );
std::future< ull >  EvenOdd = std::async( std::launch::deferred, findODD, start, end );

    
    
    
    cout << " Just for fun....."<< endl;
        
           
            cout << " even sum : "<<  EvenSum.get() << endl;
            cout << " Odd sum : "<<  EvenOdd.get() << endl;
            cout << " Job done... "   << endl;
        
        
        auto stopTime = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stopTime - startTime);
            
            cout << " Sec : "<< duration.count()/1000000 << endl;  // count()⁄1,000,000) of a second.
            
            
           
    // remember deffered policy works on a single thread Async on a diffrent thread
    return 0;
}
/*
 Just about t hreads...!
  main()  Async Thread  ID : 0x1f382de00
  Just for fun.....
  even sum :   Find Even Async Thread  ID : 0x1f382de00
 902500000000000000
  Odd sum :   Find ODD Async Thread  ID : 0x1f382de00
 902500000950000000
  Job done...
  Sec : 6
 Program ended with exit code: 0
 */
