//
//  main.cpp
//  17_VisitorVariantObj
//
//  Created by Sathya Babu on 05/11/21.
// https://gieseanw.wordpress.com/2017/05/03/a-true-heterogeneous-container-in-c/

// https://www.cppstories.com/2020/04/variant-virtual-polymorphism.html/

#include <iostream>
#include <string>
#include <variant>
#include <vector>

struct MyVisitor_OLD_USE_THE_TEMPLATEONE_INSTED_OF_THIS
{
   void operator()(int& _in){_in += _in;}
   void operator()(double& _in){_in += _in;}
   void operator()(std::string& _in){_in += _in;}
};

struct MyVisitor
{
    template<class T>
    void operator()(T& _in){_in += _in;}
};


/////  Phase II
///
class Base {
public:
    virtual ~Base() = default;
    
    virtual void PrintName() const {
        std::cout << "calling Bases!\n";
    }
};

class Derived : public Base {
public:
    void PrintName() const override {
        std::cout << "calling Derived!\n";
    }
};

class ExtraDerived : public Base {
public:
    void PrintName() const override {
        std::cout << "calling ExtraDerived!\n";
    }
};

struct CallPrintName {
    void operator()(const Derived& d) { d.PrintName(); }
    void operator()(const ExtraDerived& ed) { ed.PrintName(); }
};


///
/////////////
int main()
{
    auto lambdaPrintVisitor = [](auto&& _in){std::cout << _in;};
    std::vector<std::variant<int, double, std::string>> variantCollection;
    variantCollection.emplace_back(1);
    variantCollection.emplace_back(2.2);
    variantCollection.emplace_back("foo");
    
    // print them
    for (const auto& nextVariant : variantCollection)
    {
        std::visit(lambdaPrintVisitor, nextVariant);
        std::cout << " ";
    }
    std::cout << std::endl;
    
    // double them
    for(auto& nextVariant : variantCollection)
    {
        std::visit(MyVisitor{}, nextVariant);
    }
    
    // print again
    for (const auto& nextVariant : variantCollection)
    {
        std::visit(lambdaPrintVisitor, nextVariant);
        std::cout << " ";
    }
    std::cout << std::endl;
//
    
    // step I
    Base *base ;
    Derived derived ;

    base = &derived;
    base->PrintName();

    // step II Modern C++
    std::unique_ptr<Base> pObject = std::make_unique<Derived>();
    pObject->PrintName();
    
    // step III variant
    std::variant<Derived, ExtraDerived> var;
    std::visit(CallPrintName{}, var);
    
    // step IV
    std::variant<Derived, ExtraDerived> var2;
    var2 = ExtraDerived{};
    auto caller = [](const auto& obj) { obj.PrintName(); };
    std::visit(caller, var2);
}

/*
 1 2.2 foo
 2 4.4 foofoo
 Program ended with exit code: 0
 
 *****Comparing variant Polymorphism
 
 Lets summarize the pros and cons of using std::variant<> for polymorphism and inhomogeneous collections.
 Benefits are:
 • You don’t need common base types (non-intrusive).
 • You don’t have to use pointers for inhomogeneous collections.
 • No need for virtual member functions.
 • Value semantics (no access of freed memory or memory leaks).
 • Elements in a vector are located together (instead of distributed via pointers in heap memory).
 
 Constraints and drawbacks are:
 
 • Close set of types (you have to know all alternatives at compile time).
 • Elements all have the size of the biggest element type (an issue if element type sizes differ a lot).
 • Copying elements might be more expensive.
 In general, I would recommend now to program polymorphism with std::variant<> by default, because it is usually faster (no new and delete, no virtual functions for non-polymorphic use), a lot safer (no pointers), and usually all types are known at compile-time of all code.
 Just when you have to deal with reference semantics (using the same objects at multiple places) or passing objects around becomes to expensive (even with move semantics), runtime polymorphism with inheritance might still be appropriate.

 
 */
