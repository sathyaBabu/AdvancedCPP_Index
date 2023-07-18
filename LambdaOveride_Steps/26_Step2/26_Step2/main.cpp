//
//  main.cpp
//  26_Step2
//
//  Created by Sathya Babu on 26/04/23.
//
//
//  main.cpp
//  26_Step_1
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

struct Print : PrintInt , PrintCString {
    
    using  PrintInt::operator();
    using  PrintCString::operator();
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::vector< var_t > vars = { 1,2,"Hello Variadic ! "};
    
   // Print print;
    for( auto& v : vars ){
        //std::visit( print, v );
        std::visit( Print{}, v );
    }
    return 0;
}
