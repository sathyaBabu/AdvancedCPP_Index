//
//  main.cpp
//  2_Step_4
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include <vector>
using namespace  std;


using var_t = std::variant< int, const char* >;  // 1



template< class... Ts>  // PrintCString, PrintInt
struct Print : Ts...{
    
    using   Ts::operator()...;
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::vector< var_t > vars = { 1,2,"Hello there... "};
    
    auto PrintInt =     [] ( int i ) {  cout << i << endl ; } ;
    auto PrintCString = [] ( const  char*  str ) {  cout << str << endl ; } ;
    
//    Print print ;
    for( auto& v : vars ){
//        std::visit( Print<PrintCString,PrintInt>{} ,v );  //   std::visit( print ,v );
        std::visit(
                   Print< decltype( PrintCString) , decltype( PrintInt )> { PrintCString,PrintInt} , v );
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
