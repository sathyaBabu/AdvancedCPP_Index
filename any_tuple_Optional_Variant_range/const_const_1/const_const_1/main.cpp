//
//  main.cpp
//  const_const_1
//
//  Created by Sathya Babu on 07/08/23.
//

#include <iostream>
using namespace std;

class A {
    private :
    
    int  x , y ;
    
    int * xx, yy ;
    
    mutable int var ;  // can be modified under a const function
    
    public :
    int getX() const
    {
        // note on top var is mutable
        var = 99 ;
        return  x ;
    }
    // next phase
    const int* const getXX() const
    {
        return  xx ;
    }
    
    void setX(int _x ) // const
    {
        x = _x ;
    }
    
};

void print( const A& a ){
    
    // if u remove    :  int getX()
    // 'this' argument to member function 'getX' has type 'const A', but function is not marked const
    cout << a.getX() << endl ;
    
}
// Phase II

constexpr int getValue(int value ){ return value * 2 ;}

int main(int argc, const char * argv[]) {
    
            // Phase I

            const int cInt = 100;

            const int *a = 123 ;  // Cannot initialize a variable of type 'const int *' with an rvalue of type 'int'

            const int *b = cInt ; // Cannot initialize a variable of type 'const int *' with an lvalue of type 'const int

            // Where on earth we are heading towards!!!!
            // lets deal with expressions down the lane!

            const int* a = new int ;


            // since const is *a content cannot be changed
            //*a = 123 ; // Read-only variable is not assignable



            // means the same
            const int* aa = new int ;  // content cant be changed its read only

           // *aa = 321 ; // Read-only variable is not assignable
            aa = (int*)&cInt ;  // ok

            int* const b = new int ;  // addr can be changed down the lane





            int* const c = new int ;
            // since const is b content cannot be changed

            b = (int*)&cInt ; // Cannot assign to variable 'b' with const-qualified type 'int *const'

            *b = 34 ;
            *aa = 12 ; // Read-only variable is not assignable


            // what if

            const int* const abc = new int ;  // content or addr cant be changed

            *abc = 567 ;
            abc = (int*)&cInt ;
            abc = nullptr ;


    
    // Phase II
   const  int res = getValue( 6 ); // after declaring const static_assert( res == 12); is ok
    // insert code here...
    std::cout << "value  << std::endl ";
    static_assert( res == 12); // Static_assert expression is not an integral constant expression
    
    return 0;
}
