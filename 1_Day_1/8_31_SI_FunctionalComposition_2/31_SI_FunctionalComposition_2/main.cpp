//
//  main.cpp
//  31_SI_FunctionalComposition_2
//
//  Created by Sathya Babu on 31/07/23.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
using namespace std ;


void compute( int& value ){
    
    cout << " Thread in Compute() " << std::this_thread::get_id() << endl ;
//    for( int i =0 ; i <= 1000000 ; ++i )
//    {
        value *= 2 ;
   // }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::vector< int > data { 1,2,3,4,5 };
    
    std::vector< std::future< void > > futures ;
    
    cout << " main Thread  " << std::this_thread::get_id() << endl ;
    
    for( auto& value : data ){
        futures.emplace_back( std::async( std::launch::async, compute, std::ref( value )));
       // futures.wait();
    }
    
    for(  auto& future : futures )
    {
        future.wait();
    }
    
    for( const auto& value : data ){
        cout << value << " " ;
    }
    
    
    return 0;
}
/*
 
 Hello, World!
  main Thread  0x1f382de00
  Thread in Compute() 0x16fe87000
  Thread in Compute() 0x17002b000
  Thread in Compute() 0x16ff9f000
  Thread in Compute() 0x16ff13000
  Thread in Compute() 0x1700b7000
 2 4 6 8 10 Program ended with exit code: 0

 */
