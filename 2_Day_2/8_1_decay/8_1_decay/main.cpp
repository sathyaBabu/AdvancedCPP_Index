//
//  main.cpp
//  8_1_decay
//
//  Created by Sathya Babu on 01/08/23.
//

#include <iostream>
using namespace std ;

template<typename T>
void func( T&& param ){
    if( std::is_same<T,int>::value){
        cout << " is an int " << endl ;
    }else
    {
        cout << " param is not an  int " << endl ;
    }
}



template<typename T>
void funcDecay( T&& param ){
    if( std::is_same< typename std::decay< T >::type,int>::value){
        cout << " is an int " << endl ;
    }else
    {
        cout << " param is not an  int " << endl ;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int three = 3 ;
    func( three );  //  param is not an  int
    funcDecay( three );  //  is an int
    return 0;
}
/*
 
 Hello, World!
  param is not an  int
  is an int
 
 Program ended with exit code: 0
 
 */
