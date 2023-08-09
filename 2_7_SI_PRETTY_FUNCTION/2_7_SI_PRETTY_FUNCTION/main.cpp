//
//  main.cpp
//  2_7_SI_PRETTY_FUNCTION
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
using namespace std ;


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int x = 100 ; int y = 200 ;
    
    auto print = [ & ] {
        
        cout << __PRETTY_FUNCTION__ << endl ;
        cout << " x  : "  << x << " Y : " << y << endl ;
        
    };
    print();
    
    return 0;
}
/*
 
 Hello, World!
 auto main(int, const char **)::(anonymous class)::operator()() const
  x  : 100 Y : 200
 Program ended with exit code: 0
 
 */
