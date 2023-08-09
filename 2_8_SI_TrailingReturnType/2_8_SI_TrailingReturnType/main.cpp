//
//  main.cpp
//  2_8_SI_TrailingReturnType
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
using namespace std ;


auto testSpeedString = [] ( int speed ) -> std::string { if ( speed > 100)
    return " Yoy are a super fast driver... " ; else return  " You are a good composed driver";
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    auto str = testSpeedString( 120 ); //  Yoy are a super fast driver...
    cout << str << endl ;
    
    return 0;
}
