//
//  main.cpp
//  CaptureTuple
//
//  Created by Sathya Babu on 12/07/23.
//

#include <iostream>
#include <tuple>

template < class... Args>
void captureTest(Args... args) {
    
    const auto lambda = [args...] {
    const auto tup = std:: make_tuple(args...); std:: cout << "tuple size: " <<
    std:: tuple_size< decltype (tup)>:: value << '\n' ;
        std:: cout << "tuple 1st: " <<
        std:: get<0> (tup) << '\n' ;
      };
    lambda(); // call it
    
}
int main() {
    captureTest(1 , 2 , 3 , 4 );
    captureTest("Hello world" , 10.0f );
}

//
//tuple size: 4
//tuple 1st: 1
//tuple size: 2
//tuple 1st: Hello world
//Program ended with exit code: 0
