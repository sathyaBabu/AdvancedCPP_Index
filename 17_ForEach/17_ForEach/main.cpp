//
//  main.cpp
//  17_ForEach
//
//  Created by Sathya Babu on 10/09/22.
//
/*
 1. Advantages of foreach loop
 It eliminates the possibility of errors and makes the code more readable.
 Easy to implement
 Does not require pre-initialization of the iterator
 2. Disadvantages of foreach loop
 Cannot directly access the corresponding element indices
 Cannot traverse the elements in reverse order
 It doesn’t allow the user to skip any element as it traverses over each one of them

 */


#include <iostream>
#include <algorithm>
#include <vector>
using namespace std ;

// receive lambda as funPtr(int ) = (int){ prints the value }

void ForEach( const std::vector< int >&values, void( *funPtr )( int ) ){
    cout << " processing the data for  lambda {}"<<endl;
    for( int value : values)
    {
       // cout << " about to call lambda {}"<<endl;
        funPtr( value +=5 );    // its a call back {}
    }
    cout << " processing the data ENDS...for  lambda {}"<<endl;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::vector< int > values = { 1,2,3,4,5 };
    
    ForEach(  values , [](int value ) { cout << " Value : "<< value << endl ;}  );
    return 0;
}

/*
 Hello, World!
  about to call {}
  Value : 1
  about to call {}
  Value : 2
  about to call {}
  Value : 3
  about to call {}
  Value : 4
  about to call {}
  Value : 5
 Program ended with exit code: 0
 */
