//
//  main.cpp
//  HigherOrderFunReturning
//
//  Created by Sathya Babu on 10/10/21.
//
/*
 Higher order functions are simply functions that take functions as parameter or return a function. In C++ that's any callable object ( std::function , function pointer, lambda, functor, anything that implements operator() )
 
 */
#include<iostream>
const auto less_than = [](auto x) {

    return [x](auto y) {

        return y < x;

    };

};

int main(void)

{

    auto less_than_five = less_than(5);
    std::cout <<  " TRUE "<< less_than_five(22)<< std::endl;
    std::cout <<  " FALSE  "<< less_than_five(3) << std::endl;
    std::cout <<  " TRUE "<< less_than_five(10) << std::endl;

    return 0;

}
