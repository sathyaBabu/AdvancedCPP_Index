//
//  main.cpp
//  2_Step7
//
//  Created by Sathya Babu on 02/08/23.
//
//
//#include <iostream>
//#include <vector>
//using namespace  std;
//
//
//using var_t = std::variant< int, const char* >;  // 1
//
////
////template< class... Ts>
////struct Print : Ts... {
////    using Ts :: operator()...;  // int char*
////};
////template< class... Ts>  // PrintCString, PrintInt
////auto MakePrint( Ts... ts) {
////    return Print<Ts...>{ ts...};
////};
//
//// Phase II
//
//template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
//template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
//
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//
//    std::vector< var_t > vars = { 1,2,"Hello there... "};
//
////    Print print ;
//    for( auto& v : vars ){
//
//        std::visit(
////                   MakePrint(
//                   overloaded{
//
//                       [] ( int i ) {  cout << i << endl ; } ,
//                       [] ( const  char*  str ) {  cout << str << endl ; }
//
//
//                   }, v );
//    }
//    return 0;
//}
///*
//
// Hello, World!
// 1
// 2
// Hello there...
// Program ended w
//
// */




#include <iostream>
#include <memory>
#include <utility>
#include <variant>
#include <array>
#include <string>
#include <algorithm>

//#include <decltype>

using namespace std;
/*
 
 The using declaration then makes both function call operators available for type overload.
  With- out the using declaration, the base classes would have two different overloads of the same member
  function operator(), which is ambiguous.1
 
 */
//template <typename... T>
//struct Overloader : T... /* […] */ {
//    // […]
//};
//
//template <typename... T>
//constexpr auto make_overloader(T&&... t) {
//    return Overloader<T...>{std::forward<T>(t)...};
//}


//  or

//            template<typename... Ts>
//              struct overload : Ts...
//            {
//                using Ts::operator()...;
//            };
//            // base types are deduced from passed arguments:
//              template<typename... Ts>
//              overload(Ts...) -> overload<Ts...>;
///

template<typename  ...B>
struct visitor : B...
{
    template<typename  ...T>
    visitor( T&& ... t) : B( std::forward<T>(t) )...
    {
        
    }
    using B::operator()...; // overloading multiple operator here
    
    
};
template<typename  ...T>
visitor(T ...) -> visitor< std::decay_t< T >... >;
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
/*
 
 Sathya
 10
 12.2
 Program ended with exit code: 0
 
 */
