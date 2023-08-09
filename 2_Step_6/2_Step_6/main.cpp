//
//  main.cpp
//  2_Step_6
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include <vector>
using namespace  std;


using var_t = std::variant< int, const char* >;  // 1

//
//template< class... Ts>
//struct Print : Ts... {
//    using Ts :: operator()...;  // int char*
//};
//template< class... Ts>  // PrintCString, PrintInt
//auto MakePrint( Ts... ts) {
//    return Print<Ts...>{ ts...};
//};

// Phase II

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::vector< var_t > vars = { 1,2,"Hello there... "};
    
//    Print print ;
    for( auto& v : vars ){

        std::visit(
//                   MakePrint(
                   overloaded{
                       
                       [] ( int i ) {  cout << i << endl ; } ,
                       [] ( const  char*  str ) {  cout << str << endl ; }
                       
                       
                   }, v );
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
