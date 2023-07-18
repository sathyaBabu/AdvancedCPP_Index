//
//  main.cpp
//  26_Step_7_Forward_decay
//
//  Created by Sathya Babu on 26/04/23.
//


#include <iostream>
#include <memory>
#include <utility>
#include <variant>
#include <array>
#include <string>
#include <algorithm>

//#include <decltype>

using namespace std;
template<typename  ...B>
struct visitor : B...
{
    template<typename  ...T>
    visitor( T&& ... t) : B(std::forward<T>(t))...
    {
        
    }
    using B::operator()...; // overloading multiple operator here
    
    
};
template<typename  ...T>
visitor(T ...) -> visitor<std::decay_t<T>...>;
//////////////   lambda template override - depricated in c++20




int main(int argc, const char * argv[]) {
    // insert code here...
    auto o = visitor (

                      [] (auto const& a) {std::cout << a << endl ;},
                      [] (string  const& str) {std::cout << str << endl;},
                      [] (float f) {std::cout <<  f << endl;}

                      );
    
    o("Sathya");
    o(10);
    o(12.2f);
    return 0;
}
