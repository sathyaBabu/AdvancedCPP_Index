//
//  main.cpp
//  2_6_SI_mutable
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int ammo{ 10 };
    
    auto shoot{
        
        [ ammo ](  )  mutable {
            
            --ammo;
            cout << " Pew! " << ammo << " Shot's left " << "... " << endl ;
        }
        
        
    };
    shoot(  );
    shoot(  );
    
    return 0;
}
/*
 Hello, World!
  Pew! 9 Shot's left ...
  Pew! 8 Shot's left ...
 Program ended with exit code: 0
 */
