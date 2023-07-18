//
//  main.cpp
//  26_Step_5
//
//  Created by Sathya Babu on 26/04/23.
//


#include <iostream>
#include <vector>
#include <typeinfo>
#include <variant>
using namespace std;

/*
template<typename ... Ts>
struct Overload : Ts ...
{
    using Ts::operator() ...;  // ???
};
template<class... Ts>               // (a)
Overload(Ts...) -> Overload<Ts...>; // Lambdas provide this call operator.   calls this line (a) overload() operator
*/

using var_t = std::variant< int, const char* > ;

// Function object is nothing but lambdas..


template<class... Ts>  // Ts hold ( PrintCString,PrintInt )
struct Print : Ts... {
    
    using Ts::operator()... ;
    
};

template<class... Ts>
auto MakePrint( Ts... ts ){
    return  Print< Ts...> { ts...};
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::vector< var_t > vars = { 1,2,"Hello Variadic ! "};
    
    
   // Print print;
    for( auto& v : vars ){
        //std::visit( print, v );
        std::visit(
                     MakePrint(
                                [](int i) { std::cout << i << std::endl; } ,  // (1)
                                [](const char* str) { std::cout << str << std::endl;; }
                          ), v );
    }
    return 0;
}
