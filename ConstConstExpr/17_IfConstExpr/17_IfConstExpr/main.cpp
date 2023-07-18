//
//  main.cpp
//  17_IfConstExpr
//
//  Created by Sathya Babu on 03/11/21.
//

#include <iostream>
#include<type_traits>
#include<limits>
using namespace std;
/*
 const applies for variables, and prevents them from being modified in your code.

 constexpr tells the compiler that this expression results in a compile time constant value, so it can be used in places like array lengths, assigning to const variables, etc. The link given by Oli has a lot of excellent examples.

 Basically they are 2 different concepts altogether, and can (and should) be used together.
 */



const     double PI1 = 3.141592653589793;
constexpr double PI2 = 3.141592653589793;

//constexpr double PI3 = PI1;  // error


constexpr double PI3 = PI2;  // ok




// Error : // Variable length array declaration not allowed at file scope
// int i =100;
//int arr[i]; // Variable length array declaration not allowed at file scope

// works
const int ii = 100;
int cAry[ ii ] ;

  // Check the following block..
constexpr int func_constexpr(int X, int Y)
{
    
    return(X*Y);
}

   int func(int X, int Y)
{
    return(X*Y);
}

void func(int*)    {  cout << " in func int*  " <<  endl; }
void func(double*) { cout << "  in func double*  " <<  endl; }


template <typename T>
void  template_func(T t) {cout << " template deduced t type   " << t << endl;}

//void func(nullptr) { cout << "  in func nullptr  " <<  endl; }// dosent work


//void func(nullptr_t) { cout << "  in func nullptr_t  " <<  endl; }// works

//int array2[func(10,20)]; // ERROR - func() is not a constexpr function.



int array1[func_constexpr(10,20)]; // OK - func_constexpr() can be evaluated at compile time.

//int array3[func_constexpr(10,rand())]; // ERROR - even though func_constexpr() is the 'constexpr' function, the expression 'constexpr(10,rand())' can't be evaluated at compile time.



//  can be applied on member functions too

  class test3
{
    public:

    int value;

    // constexpr const method - can't chanage the values of object fields and can be evaluated at compile time.
    constexpr  int getvalue() const
    {
        
        return(value);
    }

    constexpr test3(int Value)
        : value(Value)
    {
    }
};


constexpr test3 x(100); // OK. Constructor is constexpr.

int array[x.getvalue()]; // OK. x.getvalue() is constexpr and can be evaluated at compile time.

// makes no diffrence..
//                template<typename T>
//                void printTypeInfo(const T&)
//                {
//                    if constexpr ( std::is_integral<T>::value){
//                        std::cout << " is integral "<< endl ;
//                        }else{
//                            std::cout << " is not integral "<< endl ;
//                    }
//                }



template<typename T>
auto printTypeInfo(const T& t )
{
    if constexpr ( std::is_integral<T>::value){
        std::cout << " is integral "<< endl ;
        return t+1;
        }else{
            std::cout << " is not integral "<< endl ;
            return t+0.1;
            //  without constexpr after if we tend to get this declaaration error : 'auto' in return type deduced as 'double' here but deduced as 'int' in earlier return statement
    }
}

                template<typename T>
                auto printTypeInfoMultiple(const T& t )
                {
                    if constexpr ( std::is_integral<T>::value && std:: is_same<bool,T>::value){
                        std::cout << " \n is integral "<< endl ;
                        return t+1;
                        }else if constexpr ( std::is_floating_point<T>::value){
                            std::cout << "\n is not integral  Floating point now..."<< endl ;
                            return t+0.1;
                            //  without constexpr after if we tend to get this declaaration error : 'auto' in return type deduced as 'double' here but deduced as 'int' in earlier return statement
                        } else {
                            cout << " \n Default else and t holds "<< t << endl;
                            return t ;
                        }
                }

// used to express nulptr_t
struct ClassWithMember { void func(); };


int main(int argc, const char * argv[]) {
    // insert code here...
    
   
    
    //****************
    printTypeInfo(5);
    printTypeInfo(3.5);
   
        int *ptr = nullptr;                // OK
        void (ClassWithMember ::*method_ptr)() = nullptr; // OK

      //  NULL n1, n2;// Use of undeclared identifier 'n1'
    
        nullptr_t n1,n2 ;
        n1 = n2;
    // NOTE:As nullptr is an integer literal with value zero, you can not able to use its address which we accomplished by deleting & operator.
        nullptr_t *null = &n1;           // deleted kind Address can't be taken. can be asssigned since  nullptr acts as an integral type Ambigues!!!!
    
    // int ptr_not_ok = reinterpret_cast<int>(nullptr); // Not OK
    long ptr_ok = reinterpret_cast<long long>(nullptr); // OK
    ptr_ok = 12345678;
    cout << " null reinterpreted as long " << ptr_ok << endl;
    
//    func(nullptr);                            // compilation error,Call to 'func' is ambiguous
    
    // lets check the same now after creating func( nullptr) function!!
   // func(nullptr);  //  Call to 'func' is ambiguous
    
    int *ptrr = nullptr;
   // ptrr = 0; ok
    
    if (ptrr == 0){}          // OK
    if (ptrr == nullptr){}   //  OK

    int a = 0;
  //  if (a == nullptr);      // error: invalid operands of types 'int' and 'std::nullptr_t' to binary 'operator=='
    

    // func(reinterpret_cast<int*>(nullptr)); // error: invalid cast from type 'std::nullptr_t' to type 'int*'
    
    
    func(static_cast<int*>(nullptr));   //ok
    template_func(static_cast<int*>(nullptr));         // OK   template deduced t type   0x0
    
   

   // func(nullptr);         // deduces T = nullptr_t
    func((int*)nullptr);   // deduces T = int*, prefer static_cast though
    
    
    
    //------------------------
    
    std::uint_fast16_t sometype { 0 };   // fast_32_t : 4294967295
      --sometype; // intentionally overflow to invoke wraparound behavior

      std::cout << " size of fast16_t "<< sizeof(uint_fast16_t ) << " sometype = " << sometype; //  size of fast16_t 2 : 65535   sometype = 65556
    
    
    cout << printTypeInfoMultiple(5);
    cout << printTypeInfoMultiple(3.5);
    cout << printTypeInfoMultiple(true);
    cout << printTypeInfoMultiple("Hello there!.");
    
    
    return 0;
}
/*
 is integral
 is not integral
 null reinterpreted as long 12345678
 in func int*
 template deduced t type   0x0
 in func int*
 size of fast16_t 2 sometype = 65535
 Default else and t holds 5
5
 is not integral  Floating point now...
3.6
 is integral
2
 Default else and t holds Hello there!.
Hello there!.Program ended with exit code: 0
 */
