//
//  main.cpp
//  1_2_SI_Variant
//
//  Created by Sathya Babu on 02/08/23.
//
/*
  Agenda for the day
 
  Union - variant
  Lambdas..
  Lambda recursions
 
  Visitor
  Variants vs visit..
  Assignment
  lambdas in observer LiveDat( Study code )
  Observer
 
  tuple - optional
 
  threads
 
   inline namespace   ( Api versioning )
 
   Time permits..
   factory vs CoVariant
  
 
 
 */

#include <iostream>

using namespace std;

union Value{
    
    int    i ;
    double d ;
};
Value v;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
   
    v.d = 12.12345 ;
    cout << v.d << endl ;
    
    cout << v. i<< endl ;  // bad access..
    
    
    std::variant< int , std::string> var5{ 120 },var6{"Hi"};
    //             0        1
    
    cout <<" var5 int " << std::get< 0 >( var5 ) << endl ;
    cout <<" var6 data " << std::get< std::string >( var6 ) << endl ;
    
    cout <<" var5  index  " << var5.index() << endl ;
    cout <<" var6  index  " << var6.index() << endl ;
    
    
       
    return 0;
}
/*
 
 Hello, World!
 12.1235
 -694066715
  var5 int 120
  var6 data Hi
  var5  index  0
  var6  index  1
 Program ended with exit code: 0
 */
