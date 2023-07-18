//
//  main.cpp
//  17_DispatcherTable_MAP
//
//  Created by Sathya Babu on 01/11/21.
//
/*
 How does the magic work? The dispatch table is my case a std::map that contains pairs of const char and std::function<double(double,double). Of course, you can use a std::unordered_map instead of a std::map. std::function is a so-called polymorphic function wrapper. Thanks to std::function, it can take all that behaves like a function. This can be a function, a function object, or a lambda-function (line 14 -17). The only requirements of std::function<double(double,double)> are that its entities needs two double arguments and return a double argument. This requirement is fulfilled by the lambda-functions.

 I use the function object in the lines 20 - 23. Therefore, the call of dispTable['+'] in line 20 returns that function object which was initialized by the lambda-function [](double a, double b){ return a + b; } (line 14). To execute the function object, two arguments are needed. I use them in the expression dispTable['+'](3.5, 4.5).

 A std::map is a dynamic data structure. Therefore, I can add and use the '^' operation (line 27) at runtime. Here is the calculation.


 */
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
void setValue(  const int& val ) {} // this is declared as lvalue
int main(){

    int h = 23;
    setValue(h);
    setValue(23);
    std::cout  << std::endl;
       
        

  // dispatch table
  std::map< const char , std::function<double(double,double)> > dispTable{
   // std::map< const char , double (*function_type)(double,double)> dispTable{ // error
    {'+',[](double a, double b){ return a + b;} },
    {'-',[](double a, double b){ return a - b;} },
    {'*',[](double a, double b){ return a * b;} },
    {'/',[](double a, double b){ return a / b;} } };

  // do the math
  std::cout << "3.5+4.5= " << dispTable['+'](3.5,4.5) << std::endl;
  std::cout << "3.5-4.5= " << dispTable['-'](3.5,4.5) << std::endl;
  std::cout << "3.5*4.5= " << dispTable['*'](3.5,4.5) << std::endl;
  std::cout << "3.5/4.5= " << dispTable['/'](3.5,4.5) << std::endl;

  // add a new operation
  dispTable['^']=  [](double a, double b){ return std::pow(a,b);};
  std::cout << "3.5^4.5= " << dispTable['^'](3.5,4.5) << std::endl;

  std::cout << std::endl;

};
/*
 3.5+4.5= 8
 3.5-4.5= -1
 3.5*4.5= 15.75
 3.5/4.5= 0.777778
 3.5^4.5= 280.741

 Program ended with exit code: 0
 */
