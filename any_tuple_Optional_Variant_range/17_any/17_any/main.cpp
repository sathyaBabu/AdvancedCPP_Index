//
//  main.cpp
//  17_any
//
//  Created by Sathya Babu on 05/11/21.
//
#include <any>
#include<complex>
#include<string>
#include <iostream>
 
#include <iostream>
#include <any>
using namespace std ;


int main()
{
         void* ptr;
         float f = 123.3f;

         // assign float address to void pointer
         ptr = &f;

         cout << "The content of pointer is ";
         cout << *(float*)ptr << endl;
         // use type casting to print pointer content
         cout << "The content of pointer  using static_cast is ";
         cout << *(static_cast<float*>(ptr));
    
    
  
    
    std::any val = 10;
//    std::cout << " before casting Val : " << val << std::endl;// Invalid operands to binary expression ('basic_ostream<char, Invalid operands to binary expression ('basic_ostream<char, std::char_traits<char>>' and 'std::any') and 'std::any')

    int xx = std::any_cast<int>(val);
    std::cout << "Value of xx: " << xx << std::endl;

    
 
    // any type
    std::any a = 1;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';
 
    // bad cast
    try
    {
        a = 1;
        std::cout << std::any_cast<float>(a) << '\n';
    }
    catch (const std::bad_any_cast& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
 
    // has value
    a = 1;
    if (a.has_value())
    {
        std::cout << a.type().name() << '\n';
    }
 
    // reset
    a.reset();
    if (!a.has_value())
    {
        std::cout << "no value\n";
    }
 
    // pointer to contained data
    a = 1;
    int* i = std::any_cast<int>(&a);
    std::cout << *i << "\n";
    
       auto a10 = std::make_any<float>(3.0);
       auto a11 = std::make_any<std::string>("hello");
       auto a13 = std::make_any<std::complex<double>>(3.0, 4.0);
       //auto a14 = std::make_any<std::set<int,decltype(sc)>>({4, 8, -7, -2, 0, 5},
    //sc);
    
   // hello
    std::cout << std::any_cast<std::string>(a11) << '\n';
    
}
/*
 Value of x: 10
 i: 1
 d: 3.14
 b: true
 Exception caught: bad any cast
 i
 no value
 1
 hello
 Program ended with exit code: 0
 */
