//
//  main.cpp
//  2_3_SI_LambdaVariadic
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
using namespace std ;


void print() {}

template <typename First, typename... Rest>

void print(const First &first, const Rest... args)
{

    std::cout << first << std::endl;
    print(args...);

}
//
//template< typename T>
//int addd(T... args)
//{
//
//   return  (args + ...)
//}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Lambda calls the varadic !\n";
    
    auto  varadic_generic_lambda =   []( auto... param  ){  print( param...) ;  } ;
    
    varadic_generic_lambda( 1, "First ", 12.4 , "Bangalore ",560043 );
    
    // fold expressions here
    
    
    const auto add = [] < typename... T > (  T... args) { return  (args + ...);     };
    cout << " Sum from fold = " << add( 1,2,3,4,5);  // Sum from fold = 15
    
    return 0;
}
/*
 Lambda calls the varadic !
 1
 First
 12.4
 Bangalore
 560043
  Sum from fold = 15Program ended with exit code: 0
 */
