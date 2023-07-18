//
//  main.cpp
//  16_CRTP_VS_VirtualFun_2
//
//  Created by Sathya Babu on 31/10/22.
//  NO virtual here

//- Compiler Time Polymorphism and
//- Creating State Machines


#include <iostream>
using namespace std;

template<typename  type>
class Base{
    public :
     void fun() {
         cout << " Base::fun Delegates to the Appropriate class... " << endl ;
         static_cast<type*>(this)->fun();
         
     }
};

class Triangle: public Base< Triangle >{
    public :
      void fun() { cout << " Triangle :: fun called... " << endl ; }
};

class Rectangle : public Base< Rectangle >{
    public :
      void fun() { cout << " Rectangle :: fun called... " << endl ; }
};


template<typename  type>
void callFunction( Base< type > bp ){
    bp.fun();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Virtual function !\n";
    
   
    Triangle tri;
    Rectangle rect ;
    
    callFunction( tri );
    callFunction( rect );
    return 0;
}
/*
 
 Base::fun Delegates to the Appropriate class...
 Triangle :: fun called...
 Base::fun Delegates to the Appropriate class...
 Rectangle :: fun called...
 
 */
