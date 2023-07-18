//
//  main.cpp
//  Variadic_simple_2_x
//
//  Created by Sathya Babu on 16/10/21.
//

#include <iostream>

using namespace std;

// Alias..

           //typedef float f ;  // C++
           using f = float ; // c++11

           typedef void(*FP)(int);
           // vs
           using FP = void(*)(int);

           void foo( FP) ;


template <typename T>
void print(const T& t) {
   
    cout << " in me "<< t << endl;
}

template <typename First, typename... Rest>
void print(const First& first, const Rest&... rest) {
   // std::cout << __PRETTY_FUNCTION__ << "\n";
    cout << first << ", ";
    print(rest...); // recursive call using pack expansion syntax
}

int main()
{
   
  
    print(1); // calls second overload

    // these call the third overload, the variadic template,
    // which uses recursion as needed.
    print(10, 20);
    print(100, 200, 300);
    print("first", 2, "third", 3.14159);
}
/*
 in me 1
void print(const First &, const Rest &...) [First = int, Rest = <int>]
10,  in me 20
void print(const First &, const Rest &...) [First = int, Rest = <int, int>]
100, void print(const First &, const Rest &...) [First = int, Rest = <int>]
200,  in me 300
void print(const First &, const Rest &...) [First = char [6], Rest = <int, char [6], double>]
first, void print(const First &, const Rest &...) [First = int, Rest = <char [6], double>]
2, void print(const First &, const Rest &...) [First = char [6], Rest = <double>]
third,  in me 3.14159
Program ended with exit code: 0
 */
