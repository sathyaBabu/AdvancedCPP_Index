//
//  main.cpp
//  26_Variant_Visit
//
//  Created by Sathya Babu on 26/04/23.
//

#include <iostream>

#include <iostream>
#include <vector>
#include <typeinfo>
#include <variant>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Variant vs visit \n";
    
    std::vector< std::variant<char, long, float, int, double, long long> >      // 1
                   vecVariant = {'2',5, 5.4, 100ll, 2011l, 3.5f, 2017};
    
    for (auto& v: vecVariant){
        
           std::visit( [](auto arg){std::cout << arg << " ";},   v);// 2
           //std::visit( visitable , visitor );
        
       }
    
    for (auto& v: vecVariant){
        
           std::visit( [](auto arg){std::cout << typeid(arg).name()  << " ";},   v);// 2
         //std::visit( visitable , visitor );
        
       }
    
    return 0;
}
