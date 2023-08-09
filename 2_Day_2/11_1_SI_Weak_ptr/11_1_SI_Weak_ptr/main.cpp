//
//  main.cpp
//  11_1_SI_Weak_ptr
//
//  Created by Sathya Babu on 01/08/23.
//
#include <iostream>
#include <memory>
 

// a dead lock can happen while using the shared_ptr

std::weak_ptr< int > gw;
 
void observe()
{
    std::cout << "gw.use_count() == " << gw.use_count() << "; ";
    // we have to make a copy of shared pointer before usage:
    if (std::shared_ptr<int> spt = gw.lock())
        std::cout << "*spt == " << *spt << '\n';
    else
        std::cout << "gw is expired\n";
}
 
int main()
{
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;
 
        observe();
    }
 
    observe();
}
/*
 
 gw.use_count() == 1; *spt == 42
 gw.use_count() == 0; gw is expired
 Program ended with exit code: 0
 */
