//
//  main.cpp
//  26_Step3
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

struct PrintInt{
    
    void operator() ( int i ){
        
        cout << i << endl ;
    }
    
};
struct PrintCString{
    
    void operator() ( const char* str  ){
        
        cout << str << endl ;
    }
    
    
};

template<class... Ts>  // Ts hold ( PrintCString,PrintInt )
struct Print : Ts... {
    
    using Ts::operator()... ;
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::vector< var_t > vars = { 1,2,"Hello Variadic ! "};
    
   // Print print;
    for( auto& v : vars ){
        //std::visit( print, v );
        std::visit( Print< PrintCString,PrintInt > {} , v );
    }
    return 0;
}
