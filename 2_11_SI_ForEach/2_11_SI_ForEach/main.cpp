//
//  main.cpp
//  2_11_SI_ForEach
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include<vector>

using namespace  std ;

//std::function<<#class Fp#>>
void ForEach( const std::vector< int >& values , void ( *funptr )(int ))
{
    cout << "\n  Getting connected to the net.. " << endl ;
    
            for( int value : values ){
                cout << "\n  Received the data from stock market INFOSYS " << endl ;
                funptr( value );
            }
    
    cout << "\n  Disconnect fromthe  net.. " << endl ;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::vector< int > values { 1,2,3,4,5};
    // observing for the change in the data..
    
    ForEach( values , []( int value ){ cout << "Value : " << value << endl ; } );
    return 0;
}
/*
 
 Hello, World!

   About to call lambda-> callBack
 Value : 1

   About to call lambda-> callBack
 Value : 2

   About to call lambda-> callBack
 Value : 3

   About to call lambda-> callBack
 Value : 4

   About to call lambda-> callBack
 Value : 5
 Program ended with exit code: 0
 */
