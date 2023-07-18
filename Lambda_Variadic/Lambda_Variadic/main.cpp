//
//  main.cpp
//  Lambda_Variadic
//
//  Created by Sathya Babu on 12/10/21.
//

#include <iostream>

void print() {}

template <typename First, typename... Rest>

void print(const First &first, Rest &&... args)
{

    std::cout << first << std::endl;
    print(args...);

}

int main()
{
//                   [ capture list ] (parameters) -> return-type
    auto variadic_generic_lambda = [](auto... param) { print(param...);  };

    variadic_generic_lambda(1, "LOL🤣", 17.1,"Sathya",999);

}
