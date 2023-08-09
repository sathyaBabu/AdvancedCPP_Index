//
//  main.cpp
//  2_11_SI_Invoke
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
using namespace std ;

void foo() { cout << "foo() gets invoked... " << endl ;}

void print_num( int i ){
    cout << " Printing i " << i << endl ;
}

struct PrintNum{
    void operator() ( int i ) const {
        cout << "From PrintNum operator() :" << i << endl ;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::invoke( foo) ;
    
    auto c = []{ cout << " Hi from lambda ..." ;};
    
    std::invoke( c);
    
    std::invoke(  print_num , 123 );
    
    std::invoke( [](){ print_num( 42 ) ; });
    
    std::invoke( PrintNum() , 190 );
    return 0;
}
