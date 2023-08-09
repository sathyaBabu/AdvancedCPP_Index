//
//  main.cpp
//  2_5_SI_Capture
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
using namespace std ;

auto makeMeAdeveloper( const std::string& name )
{
    
    int age = 23 ;
    
    // return  [ &,age  ]() {
    // return  [ name,age  ]() {
       return  [ = ]() {
        cout << "I'm a developer, My name is " << name << " Age is " << age << endl ;
    };
    
}

int main(int argc, const char * argv[]) {
    
    
    auto saySomeThing { makeMeAdeveloper(" Sathya ")     };
    
    saySomeThing();
    return 0;
}
/*
 I'm a developer, My name is  Sathya  Age is 23
 Program ended with exit code: 0
 */
