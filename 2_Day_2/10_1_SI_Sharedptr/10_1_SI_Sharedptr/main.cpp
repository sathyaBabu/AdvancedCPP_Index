//
//  main.cpp
//  10_1_SI_Sharedptr
//
//  Created by Sathya Babu on 01/08/23.
//

#include <iostream>
using namespace std ;

class A {
    public :
    void show() {
        cout << " A:: show() "<< endl ;
        
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "shared_ptr !\n";
    
    shared_ptr< A >  p1( new A );
    cout << p1.get() << endl ;  // 0x600000004030
    p1->show();  //  A:: show()
    
    
    shared_ptr< A >  p2 ( p1 ); // 0x600000004030  ref by 2 objects..
    
    
    cout << " p1 Address : " << p1.get() << endl ; // 0x600000004030
    cout << " p2 Address : " << p2.get() << endl ; // 0x600000004030
    
    // lets get the ref count.. how many obj are using the same memory
    
    cout << " p1 returns the number of shared_ptr objects  : " << p1.use_count() << endl ; // 0x600000004030
    cout << " p2 returns the number of shared_ptr objects  : " << p2.use_count() << endl ; // 0x600000004030
    
    p1.reset() ;
    
   // p2 = std::move( p1 );
    
    cout << " p1 After relinquishes owenership  : " << p1.get() << endl ; // 0x600000004030
    cout << " Display count  : " << p2.use_count() << endl ; // 0x600000004030
    cout << " p1 Address : " << p1.get() << endl ; // 0x600000004030
    
    return 0;
}

/*
 
 shared_ptr !
 0x60000000c010
  A:: show()
  p1 Address : 0x60000000c010
  p2 Address : 0x60000000c010
  p1 returns the number of shared_ptr objects  : 2
  p2 returns the number of shared_ptr objects  : 2
  p1 After relinquishes owenership  : 0x0
  Display count  : 1
  p1 Address : 0x0
 Program ended with exit code: 0
 
 
 */
