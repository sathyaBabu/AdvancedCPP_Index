//
//  main.cpp
//  17_Forward_1
//
//  Created by Sathya Babu on 03/11/21.
//

/*
 Forward argument
 Returns an rvalue reference to arg if arg is not an lvalue reference.

 If arg is an lvalue reference, the function returns arg without modifying its type.

 This is a helper function to allow perfect forwarding of arguments taken as rvalue references to deduced types,
 preserving any potential move semantics involved.

 The need for this function stems from the fact that all named values (such as function parameters) always evaluate as lvalues (even those declared as rvalue references), and this poses difficulties in preserving potential move semantics on template functions that forward arguments to other functions.

 Both signatures return the same as:
  
 static_cast<decltype(arg)&&>(arg)


 By providing two signatures and using remove_reference on T, any instantiation is forced to explicitly
 specify the type of T (any implicitly deduced T would have no match).

 */
#include <iostream> //main header
using namespace std; //for namespace

void funda(int&& avar)    //R-value overload
{
    cout << "R-Value overload called" << endl;
}

void funda(int& avar)     //L-value overload
{
    cout << "L-Value overload called" << endl;
}


/// phase II
 template <typename T>
T&& my_forward(typename std::remove_reference<T>::type& param)
{
    return static_cast<T&&>(param);
}

template<typename T>
void call_funda(T&& parg) //Argument Universal Reference
{
    //funda(std::forward<T>(parg));  //  std::forward<T>
   // funda(my_forward<T>(parg));      // my forward
   // funda(move(parg));
   
    funda( std::forward<T>(parg) ) ; // perfect forwarding as rvalue as lvalue
}


int main()
{
    int mvar=5;
    call_funda(mvar);    // Calls L-value overload
    
    /*
     5 is an rvalue of type int.
     T is deduced to int.
     The call to bar therefore uses int as the template argument for std::forward.
     The return type of std::forward<U> is U && (in this case, that's int &&) so t is forwarded as an rvalue.
     */
    call_funda(4);       // Calls R-value overload
    return 0;
}
