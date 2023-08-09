//
//  main.cpp
//  2_10_SI_CaptureThis
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
using namespace std ;

class Foo
{
    public :
    Foo() : _x( 007 ) {}
    
    void foo() { cout << "foo() called" << endl ; }
    
    void Func() {
        [ this ] ()  { foo() ; cout << _x << "James Bond... .. . " << endl ;}() ;
    }
    
    private :
    
    int _x ;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Foo f ;
    f.Func() ;
    
    return 0;
}
/*
 
 Hello, World!
 foo() called
 7James Bond... .. .
 Program ended with exit code: 0
 */
