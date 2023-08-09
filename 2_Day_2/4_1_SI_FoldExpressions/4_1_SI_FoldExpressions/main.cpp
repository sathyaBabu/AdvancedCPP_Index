//
//  main.cpp
//  4_1_SI_FoldExpressions
//
//  Created by Sathya Babu on 01/08/23.
//

#include <iostream>
using namespace std;

template< typename... T>
auto doSomeStuff(T... t ) {
    
    return ( t+ ...);
    // i +=  (...)
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << doSomeStuff(1,2.02,3,4,5) << endl ;
    return 0;
}
// 15.02


