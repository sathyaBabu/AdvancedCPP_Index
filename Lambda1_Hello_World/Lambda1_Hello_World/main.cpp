//
//  main.cpp
//  Lambda1_Hello_World
//
//  Created by Sathya Babu on 10/10/21.
//

#include<iostream>
using namespace std;

int main()
{
    auto func = [] () { cout << "Hello world"<< endl ; };
    func(); // now call the function
    
    // gets called by itself
    []  { cout << " \n Check on me too..."<< endl ; } () ;
    
    auto func_ret = [] () { cout << " \n Lets return "<< endl ; return 123 ; };
    cout << func_ret(); // now call the function
    
    
    typedef int (*fun_ptr)();
    fun_ptr f =  [] () -> int  { cout << " \n Hmm Lets return  from a function pointer "<< endl ; return 123 ;};
    f();
}

/*
Okay, did you spot the lambda, starting with []? That identifier, called the capture specification, tells the compiler we're creating a lambda function. You'll see this (or a variant) at the start of every lambda function.

Next up, like any other function, we need an argument list: (). Where is the return value? Turns out that we don't need to give one. In C++11, if the compiler can deduce the return value of the lambda function, it will do it rather than force you to include it. In this case, the compiler knows the function returns nothing. Next we have the body, printing out "Hello World". This line of code doesn't actually cause anything to print out though--we're just creating the function here. It's almost like defining a normal function--it just happens to be inline with the rest of the code.

It's only on the next line that we call the lambda function: func() -- it looks just like calling any other function. By the way, notice how easy this is to do with auto! You don't need to sweat the ugly syntax of a function pointer.
 
 */
