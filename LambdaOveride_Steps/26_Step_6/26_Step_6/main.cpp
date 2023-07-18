//
//  main.cpp
//  26_Step_6
//
//  Created by Sathya Babu on 26/04/23.


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

// Phase I
template<class... Ts>  // Ts hold ( PrintCString,PrintInt )
struct Print : Ts... {
    
    using Ts::operator()... ; // do you remember what __PRETTY_FUNCTION__ displayed from function object
      //auto main()::(anonymous class)::operator()() const : 100 , 200
      //  ()(1,2,3,4)
};
//
//template<class... Ts>
//auto MakePrint( Ts... ts ){
//    return  Print< Ts...> { ts...};
//}


template<class... Ts>
 Print( Ts... ts ) ->Print<Ts...>;




// Phase II
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;


int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::vector< var_t > vars = { 1,2,"Hello Variadic ! "};
    
    
   // Print print;
    for( auto& v : vars ){
        //std::visit( print, v );
        std::visit(
                   overload{
                       [](int i) { std::cout << i << std::endl; } ,  // (1)
                       [](const char* str) { std::cout << str << std::endl;; }
                   }, v );
    }
    return 0;
}
