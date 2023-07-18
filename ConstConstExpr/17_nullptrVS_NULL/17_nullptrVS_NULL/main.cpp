//
//  main.cpp
//  17_nullptrVS_NULL
//
//  Created by Sathya Babu on 16/11/21.
//
#include <cstddef>
#include <iostream>

using namespace std;
// sizeof(std::nullptr_t) is equal to sizeof(void *). : std::nullptr_t is the type of the                                                        null pointer literal
// NULL                   is equal to (void*)0

// function with integer argument
void  fun(int N)   { cout << "fun(int)"; }
  
// Overloaded function with char pointer argument
void  fun(char* s)  { cout << "fun(char *)"; }
  
// Phase II
void fun(std::nullptr_t)
{
   std::cout << "null pointer overload\n";
}
template<class T>
constexpr T clone(const T& t)
{
    return t;
}
 
void g(int*)
{
    std::cout << "Function g called\n";
}
 
int main()
{
    
   // fun(NULL); // *** Call to 'fun' is ambiguous WHILE CONVERTING***
    /*
     NULL is typically defined as (void *)0 and conversion of NULL to integral types is allowed. So the function call fun(NULL) becomes ambiguous.
     */
    fun(nullptr); // calls fun(char* s) in phase I
    // after declaring fun(std::nullptr_t) ****it calls this method
    int n = NULL;
    
    int *ptr = nullptr;
   // n = nullptr; // Assigning to 'int' from incompatible type 'std::nullptr_t'
    
    

    // Below line compiles
       if (ptr) { cout <<  endl << "true"<<endl; }
       else { cout << endl <<  "false"<< endl; }  // since its null : returns false
    
    // creating two variables of nullptr_t type
        // i.e., with value equal to nullptr
        std::nullptr_t np1 ;
      
       
      
        // Initialize a pointer with value equal to np1
        char *x = np1;  // same as x = nullptr (or x = NULL
                        // will also work)
        if (x == nullptr)
            cout << "x is null" << endl;  // x is null
        else
            cout << "x is not null" << endl;
    
    
    g(nullptr);        // Fine
    g(NULL);           // Fine  (void*)0
    g(0);              // Fine
 
    g(clone(nullptr)); // Fine
//  g(clone(NULL));    // ERROR: non-literal zero cannot be a null pointer constant
//  g(clone(0));       // ERROR: non-literal zero cannot be a null pointer constant
}
/*
 fun(char *)  // Phase II null pointer overload
 false
 x is null
 Function g called
 Function g called
 Function g called
 Function g called
 Program ended with exit code: 0
 
 */
