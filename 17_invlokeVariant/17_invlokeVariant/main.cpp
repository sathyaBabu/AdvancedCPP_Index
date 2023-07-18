//
//  main.cpp
//  17_invlokeVariant
//
//  Created by Sathya Babu on 20/11/21.
//
// invoke is callable..
//


#include <iostream>

void foo() { std::cout << "foo() gets invoked..\n"; };

void print_num(int i)
{
    std::cout << i << '\n';
}
 
struct PrintNum {
    void operator()(int i) const
    {
        std::cout <<  " From PrintNum  operator() : " << i << '\n';
    }
};
int main()
{
    auto c = [] { std::cout << "hi from lambda\n" ;};

    std::invoke(foo);
    std::invoke(c);
    
    // invoke a free function
        std::invoke(print_num, -9);
     
        // invoke a lambda
        std::invoke([]() { print_num(42); });
     
    // invoke a function object
        std::invoke(PrintNum(), 18);


}
