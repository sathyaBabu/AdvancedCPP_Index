//
//  main.cpp
//  Weak_ptr_3_Wrks
//
//  Created by Sathya Babu on 12/10/21.
//

#include <iostream>
#include <memory>
 
std::weak_ptr<int> gw;
 
void observe()
{
    std::cout << "gw.use_count() == " << gw.use_count() << "; ";
    // we have to make a copy of shared pointer before usage:
    if (std::shared_ptr<int> spt = gw.lock()) {
        std::cout << "*spt == " << *spt << '\n';
    }
    else {
        std::cout << "gw is expired\n";
    }
}

int main()
{
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;
 
        observe();
    }
 
      observe();
    if (std::is_same<int, int>::value)
           std::cout << "Yep! its same... ." << std::endl;
       
    char *str = NULL;
    
    if (std::is_same<str, nullptr>::value)
           std::cout << "Yep! its same... ." << std::endl;
       
       
}
/*
 gw.use_count() == 1; *spt == 42
 gw.use_count() == 0; gw is expired
 Program ended with exit code: 0
 */
