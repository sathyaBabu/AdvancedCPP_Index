//
//  main.cpp
//  17_foldExpressions
//
//  Created by Sathya Babu on 03/11/21.
//

#include <iostream>
using namespace std;

template<typename  ... T>
auto doSomeStuff( T ... t){
    return ( t + ...);

}

int main()
{
 
    cout << doSomeStuff(1,2,3,4,5) << endl ;
    
    // Phase II
    
    const auto add = []<class... T>( T ...args) {
           return (args +...);
       };
      cout << " Sum " << add(1,2,3) << endl ;
 
  return 0;
}
/*
 15
  Sum 6
 Program ended with exit code: 0
 */
