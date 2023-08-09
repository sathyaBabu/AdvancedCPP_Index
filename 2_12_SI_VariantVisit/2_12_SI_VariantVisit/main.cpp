//
//  main.cpp
//  2_12_SI_VariantVisit
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include <vector>
#include <typeinfo>
#include <variant>

//  When we need Overload() template?

//
int main(){

    std::cout << '\n';

    std::vector< std::variant<char, long, float, int, double, long long>>      // 1
               vecVariant = {5, '2', 5.4, 100ll, 2011l, 3.5f, 2017};

    for (auto& v: vecVariant){
        std::visit([](auto arg){std::cout << arg << " ";}, v);                // 2
    }

    std::cout << '\n';

    for (auto& v: vecVariant){
        std::visit([](auto arg){std::cout << typeid(arg).name() << " ";}, v); // 3
    }

    std::cout << "\n\n";

}
/*
 
 5 2 5.4 100 2011 3.5 2017
 i c d x l f i
 
 int char double hex long float

 */
