//
//  main.cpp
//  9_1_SI_UniquePtr
//
//  Created by Sathya Babu on 01/08/23.
//

#include <iostream>
using namespace std;

struct Foo{
    
    Foo() { cout << " At Foo const " << endl ;}
    ~Foo() { cout << " At Foo destructor " << endl ;}
    
    void foo() {cout << " At foo() ... " << endl ;}
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "unique_ptr !\n";
    
    std::unique_ptr< Foo > p1 ( std::make_unique< Foo>() );
    if( p1 )  p1->foo();
    
//    std::unique_ptr< Foo > p2; // ( std::make_unique< Foo>() );
   // p2 = p1 ;
    
    std::unique_ptr< Foo > p2 ( std:: move( p1 ));
    
    p2->foo();
    
//    p1->foo(); should not work...
    
    return 0;
}
/*
 
 
 unique_ptr !
  At Foo const
  At foo() ...
  At foo() ...
  At Foo destructor
 Program ended with exit code: 0
 
 */
