//
//  main.cpp
//  17_VisitAS_Visitor
//
//  Created by Sathya Babu on 27/11/21.
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
    using Ts::operator() ...;
};
template<class... Ts>               // (a)
Overload(Ts...) -> Overload<Ts...>; // Lambdas provide this call operator.   calls this line (a) overload() operator

struct CallVisitor
{

    
   void  eye(){  cout << " Red  eye called..." << endl ;}
   void  sky(){  cout << " Blue eye called..." << endl ;}
       
  
};
struct CountVisitor
{

    
   void  eye(){  cout << " Red  eye called..." << endl ;}
   void  sky(){  cout << " Blue eye called..." << endl ;}
       
  
};

// visitable

class Red
{
  public:
    
    void eye()
    {
        cout << "Red::eye\n";
    }
    int count;
    
};
class Blu
{
  public:
  
    void sky()
    {
        cout << "Blu::sky\n";
    }
    int count;
};
int main(){
  
    std::cout << '\n';
    variant<CallVisitor,CountVisitor> item { CallVisitor() };
   // auto CallVisitor  =
    
    std::visit( Overload {     // (1)  holds following varadic lambda's
               [  ]( CallVisitor& )           { CallVisitor.eye(); },
               [  ]( CallVisitor& )           { CallVisitor.sky(); },
              
    }, item );
    
    
    //(2)
//    std::variant<char, int, float> var = 123;
//    std::cout << std::visit(TypeOfIntegral, var) << '\n';
//
    std::cout << " end of  Phase I" << endl ;
    
    // (3)   ****************************************** END of Ist Phase
    
//              std::vector<std::variant<char, long, float, int, double, long long>>  // (1)
//                         vecVariant = {5, '2', 5.4, 100ll, 2011l, 3.5f, 2017};

//    variant<CallVisitor,CountVisitor> item ;{ CallVisitor(); };
             // for (auto v : item) {                                           // (3)
                  // std::cout << std::visit(CallVisitor, item) << '\n';
               //  }

              std::cout << " end of  Phase II" << endl ;
    
    // (4)   ****************************************** END of IInd  Phase
    
    std::cout << '\n';
//
//        std::vector<std::variant<std::vector<int>, double, std::string>>      // (4)
//            vecVariant2 = { 1.5, std::vector<int>{1, 2, 3, 4, 5}, "Hello "};

//        auto DisplayMe = Overload {                                           // (5)
//            [](std::vector<int>& myVec) {
//                    for (auto v: myVec) std::cout << v << " ";  // display all vector data
//                    std::cout << '\n';
//                },
//            [](auto& arg) { std::cout << arg << '\n';},
//        };

        for (auto v : vecVariant2) {                                         // (6)
            std::visit(DisplayMe, v);
        }

    std::cout << " end of  Phase III" << endl ;
  
}
