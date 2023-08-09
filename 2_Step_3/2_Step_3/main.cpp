//
//  main.cpp
//  2_Step_3
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include <vector>
using namespace  std;


using var_t = std::variant< int, const char* >;  // 1

struct PrintInt {
    
    void operator() ( int i ){
        cout << i << endl ;
    }
    
};

struct PrintCString {
    
   
    void operator() (const char* str){
        cout << str << endl ;
    }
    
};

template< class... Ts>  // PrintCString, PrintInt
struct Print : Ts...{
    
    using   Ts::operator()...;
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::vector< var_t > vars = { 1,2,"Hello there... "};
    
//    Print print ;
    for( auto& v : vars ){
        std::visit( Print<PrintCString,PrintInt>{} ,v );  //   std::visit( print ,v );
    }
    return 0;
}
/*
 
 Hello, World!
 1
 2
 Hello there...
 Program ended w
 
 */
