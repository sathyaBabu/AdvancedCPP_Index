//
//  main.cpp
//  constinit_likeStatic
//
//  Created by Sathya Babu on 19/07/23.
//
#include <iostream>

/*
 The constinit keyword in C++20 is used to specify that a variable should be initialized at compile-time with a constant initializer and have static storage duration. It ensures that the variable is initialized before any dynamic initialization takes place.
 
 */
constinit int globalVariable = 42;

void  funn(){
 
    std::cout << "Global variable in funn() : " << globalVariable++ << std::endl;
}

int main() {
    std::cout << "Global variable: " << globalVariable << std::endl;
    funn();
    funn();
    funn();
    return 0;
}
/*
 Global variable: 42
 Global variable in funn() : 42
 Global variable in funn() : 43
 Global variable in funn() : 44
 Program ended with exit code: 0
 */
