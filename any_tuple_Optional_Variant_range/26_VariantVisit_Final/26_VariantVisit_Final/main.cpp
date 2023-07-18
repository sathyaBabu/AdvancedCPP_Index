//
//  main.cpp
//  26_VariantVisit_Final
//
//  Created by Sathya Babu on 26/04/23.
//
#include <iostream>
#include <vector>
#include <typeinfo>
#include <variant>
using namespace std;

/*
 Line (1) is the overload pattern and line (2) is the deduction guide for it.
 The struct Overload can have arbitrary many base classes (Ts ...).
 It derives from each class public and brings the call operator (Ts::operator...)
     of each base class into its scope.
 The base classes need an overloaded call operator (Ts::operator()).
 Lambdas provide this call operator. The following example is as simple as it can be.
 */
template<typename ... Ts>
struct Overload : Ts ...
{
    using Ts::operator() ...;  // ???
};
template<class... Ts>               // (a)
Overload(Ts...) -> Overload<Ts...>; // Lambdas provide this call operator.   calls this line (a) overload() operator

int main()
{
  
    std::cout << '\n';
     //  Overload happens to be variadic Template..
    
    auto TypeOfIntegral = Overload {     // (1)  holds following varadic lambda's
               [](char)           { return "char"; },
               [](int)            { return "int"; },
               [](unsigned int)   { return "unsigned int"; },
               [](long int)       { return "long int"; },
               [](long long int)  { return "long long int"; },
               [](auto)           { return "unknown type"; },
    };
    
    
    //(2)
    std::variant<char, int, float> var = 123;
    std::cout << std::visit(TypeOfIntegral, var) << '\n';
    
    std::cout << " end of  Phase I" << endl ;
    
    // (3)   ****************************************** END of Ist Phase
    
              std::vector<std::variant<char, long, float, int, double, long long>>  // (1)
                         vecVariant = {5, '2', 5.4, 100ll, 2011l, 3.5f, 2017};

              for (auto v : vecVariant) {                                           // (3)
                   std::cout << std::visit(TypeOfIntegral, v) << '\n';
                 }

              std::cout << " end of  Phase II" << endl ;
    
    // (4)   ****************************************** END of IInd  Phase
    
    std::cout << '\n';

        std::vector<std::variant<std::vector<int>, double, std::string>>      // (4)
            vecVariant2 = { 1.5, std::vector<int>{1, 2, 3, 4, 5}, "Hello "};

        auto DisplayMe = Overload {                                           // (5)
            [](std::vector<int>& myVec) {
                    for (auto v: myVec) std::cout << v << " ";  // display all vector data
                    std::cout << '\n';
                },
            [](auto& arg) { std::cout << arg << '\n';},
        };


        for (auto v : vecVariant2) {                                         // (6)
            std::visit(DisplayMe, v);
        }

    std::cout << " end of  Phase III" << endl ;
  
}
/*
 
 int
  end of  Phase I
 int
 char
 unknown type
 long long int
 long int
 unknown type
 int
  end of  Phase II

 1.5
 1 2 3 4 5
 Hello
  end of  Phase III
 Program ended with exit code: 0
 */
