//
//  main.cpp
//  17_decaySTD
//
//  Created by Sathya Babu on 17/11/21.
//  if (std::is_same<typename std::decay<T>::type,int>::value)

#include <iostream>
using namespace std;

template<class T>
void func(T&& param) {
    if (std::is_same<T,int>::value)
        std::cout << endl << " From std::is_sameparam is an int\n";
    else
        std::cout << "param is not an int\n";
}


template<class T>
void funcDecay(T&& param) {
    if (std::is_same<typename std::decay<T>::type,int>::value)
        std::cout <<  endl << " From STD::Decayparam is an int\n";
    else
        std::cout << "param is not an int\n";
}

int main() {
    int three = 3;
    func(three);  //prints "param is not an int"!!!!
    funcDecay(three);  //prints From STD::Decayparam is an int
    
    
}
