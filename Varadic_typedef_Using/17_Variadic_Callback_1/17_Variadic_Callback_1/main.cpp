//
//  main.cpp
//  17_Variadic_Callback_1
//
//  Created by Sathya Babu on 13/04/23.
//
#include <iostream>

template <typename Func>
void call(Func f)
{
    f();
}

template <typename Func, typename... Funcs>
void call(Func f, Funcs... fs)
{
    f();
    call(fs...);
}

template <typename... Args>
auto sum(Args... args)
{
    return (args + ...);
}

template <typename... Args>
auto product(Args... args)
{
    return (args * ...);
}

auto add() { std::cout << "Adding" << std::endl; }
auto sub() {std::cout << "Subtracting" << std::endl; }
auto mul() {std::cout << "Multiplying" << std::endl; }
auto divv() { std::cout << "Dividing" << std::endl; }

int main()
{
    /*
     auto add = [](){ std::cout << "Adding" << std::endl; };
     auto sub = [](){ std::cout << "Subtracting" << std::endl; };
     auto mul = [](){ std::cout << "Multiplying" << std::endl; };
     auto div = [](){ std::cout << "Dividing" << std::endl; };
     
     */
   
    call(add, sub, mul, divv);
    
    std::cout << sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << product(1, 2, 3, 4, 5) << std::endl;
    
    return 0;
}
/*
 Adding
 Subtracting
 Multiplying
 Dividing
 15
 120
 Program ended with exit code: 0
 */
