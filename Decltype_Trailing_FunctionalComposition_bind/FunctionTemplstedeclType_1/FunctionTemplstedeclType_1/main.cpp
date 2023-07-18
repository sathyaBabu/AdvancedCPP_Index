//
//  main.cpp
//  FunctionTemplstedeclType_1
//
//  Created by Sathya Babu on 06/04/22.
//

#include <iostream>
using namespace std;

const std::string message = " I'm here...\n ";

const std::string& foo(){
    return message;
}

  // Explain this at end PHASE II *******

struct A { double x; };
const A* a;
 
decltype(a  -> x) y;       // type of y is double (declared type)
decltype((a -> x)) z = y; // type of z is const double& (lvalue expression)
   
  //**********************************

   // Re visit this part of the code.. after you soil your hands with lambda!

//                                auto f = [](int a, int b) -> int { return a * b };
//
//                                decltype(f) g = f; // the type of a lambda function is unique and unnamed
//
//                                int         i = 1 ;
//                                decltype(i) j = i * 2;
//
//                              int   ii = f(2, 2);
//                              int   jj = g(3, 3);
//
//                                cout << "i = " << ii << ", "
//                                          << "j = " << jj << '\n';





// ******** Function pointers following is more of a generic type
int add(int x, int y) {
  return x + y;
}

int mull(int x, int y) {
  return x * y;
}

//
// Function Objects
            //
            class Adder {
              public:
                int operator()(int x, int y) const {
                  return x + y;
                }
            };

            class Multiplier {
              public:
                int operator()(int x, int y) const {
                  return x * y;
                }
            };

int resultOfCalculation(int (*op)(int, int),
                           int x, int y) {
  return (*op)(x, y);
}

//******************************    phase II
/////////   Check on recurssion
//
///
                template <typename FN, typename T1, typename T2>
                auto resultOfCalculation_2(
                  const FN& op,
                  const T1& x,
                  const T2& y
                ) -> decltype(op(x, y)) {
                  return op(x, y);
                }

///
///////////////
///
int (*myFnptr )(int,int)        = add ;   // Ishan to understand..( pointing to line 85 )
int ( *fnptr )( int x ,int  y ) = mull ;


// auto not int
auto getvalue() -> int { // Function with trailing return type must specify return type 'auto', not 'int'
    return 23;
    
}



auto f(float x) -> decltype( x )   // x 52   // auto 52.32

{
    return x + 42.32; // error Thread 1: breakpoint 1.1 (1) : //-> decltype(x)
}

// phase VIII raw array

auto getArr() -> int( & )[2] {
    
     int arr[] = {1, 2};
    return arr;
}


auto add1( int a , int b ) { return a + b ; }


// auto assumes the return type as int though its a reference
// Phase I
//auto increment( int& a  ) { a++; return a ; }
// ERROR -> type deducing dint happen here we forced auto with auto&

            auto& increment( int& a  ) { a++; return a ; }

// thats when decltype( auto ) comes handy
//decltype( auto )increment( int& a  ) { a++; return a ; }


int main() {
  
      const auto      f1 = foo();   // when you are not sure of the return type( Dynamic)
      
      decltype(foo()) f2 = foo();   // making decltype( to dynamic )
      decltype(auto)  f3 = foo();

      // explain this NOW  ****---> TOP part of the code..   decltype(a  -> x) y;
      
      std::cout<< f1;
      std::cout<< f2;
      std::cout<< f3;
    
    std::cout << getvalue() << std::endl;
    
    // Phase I
       int x = 100;
       // change the above line to auto&  works now
       int& y = increment( x );//Non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
       
       cout << x << endl ;
       cout << y << endl;
    
    
    cout <<  " f returned :   " << f(10) << endl;
    
    
    
    for( int i =1; i<=5 ;i++){
        auto   xx = resultOfCalculation( add, 100, i );
      std::cout << "\n ******* x  resultOfCalculation **** " << xx;
    }
    
    
    ////////////   phase II
    ///
    for( int i =1; i<=5 ;i++){
        auto   xx = resultOfCalculation_2( mull, 200, i );
      std::cout << "\n ******* x  resultOfCalculation_2 **** " << xx;
    }
    
    std::function< int (int,int)> func = add;
    cout << " func sum : " << func( 32,20 ) << endl ; // func sum : 52
    
    //   rew array vs Structural binding concept
    
    // phase VIII raw array
        std::cout << "Legacy way of usibg array  "  << std::endl;
        auto& arr = getArr();

            // Access and modify elements of the array
            arr[0] = 10;
            arr[1] = 20;

            // Print the modified array
            for (int i = 0; i < 2; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        
        std::cout << "Clean code using Structural Binding...  C++ 17 "  << std::endl;
        auto [xx, yy] = getArr();
        std::cout << "array 1  :  " << xx << std::endl;
        std::cout << "array 2  :  " << yy << std::endl;
    
    std:: cout << "myFnptr  returns : " << myFnptr(100,200) << endl ;
        std:: cout << "myFnptr  returns : " << mull(100,200) << endl ;

    // variadic expression

        // Good news..
         using namespace std::placeholders ;
        std::function<int (int) > default_add_funcObj = std::bind(&add, 123, _1);
           int  sum = default_add_funcObj(700);
            // Will return 823
        std::cout<< "std::bind returns fun object " << sum << std::endl;;
          
    
    
}
/*
 I'm here...
  I'm here...
  I'm here...
 23
101
101
 f returned :   52.32

 ******* x  resultOfCalculation **** 101
 ******* x  resultOfCalculation **** 102
 ******* x  resultOfCalculation **** 103
 ******* x  resultOfCalculation **** 104
 ******* x  resultOfCalculation **** 105
 ******* x  resultOfCalculation_2 **** 200
 ******* x  resultOfCalculation_2 **** 400
 ******* x  resultOfCalculation_2 **** 600
 ******* x  resultOfCalculation_2 **** 800
 ******* x  resultOfCalculation_2 **** 1000 func sum : 52
Legacy way of usibg array
10 1
Clean code using Structural Binding...  C++ 17
array 1  :  1
array 2  :  2
myFnptr  returns : 300
myFnptr  returns : 20000
std::bind returns fun object 823
Program ended with exit code: 0
 */
