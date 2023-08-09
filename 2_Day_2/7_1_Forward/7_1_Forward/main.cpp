//
//  main.cpp
//  7_1_Forward
//
//  Created by Sathya Babu on 01/08/23.
//

#include <iostream>
using namespace std ;

void funda( int&& avar)
{
    
    cout << " R - value over load called " << endl;
    
}

void funda( int& avar)
{
    
    cout << " l - value over load called " << endl;
    
}

template< typename T>
T&& my_forward( typename std::remove_reference< T >:: type& param)
{
    
    return  static_cast< T&&> ( param);
}

template< typename  T>
void call_funda( T&& parg )
{
    
   // funda( std::move( parg ) );
    
    
   
   // funda( my_forward< T >( parg ) );
    // funda(  parg  );
    
    // lValue and rValue as is..
   funda( std::forward< T >( parg ) );
  
    
    
    
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int myVar = 5 ;
    call_funda( myVar );  //  l Value
    
    call_funda( 4 );      //  r Value
    
    return 0;
}
