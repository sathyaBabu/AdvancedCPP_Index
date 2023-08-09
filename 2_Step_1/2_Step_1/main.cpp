//
//  main.cpp
//  2_Step_1
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include <vector>
using namespace  std;


using var_t = std::variant< int, const char* >;  // 1

struct Print {
    
    void operator() ( int i ){
        cout << i << endl ;
    }
    void operator() (const char* str){
        cout << str << endl ;
    }
    
};



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::vector< var_t > vars = { 1,2,"Hello there... "};
    
    Print print ;
    for( auto& v : vars ){
        std::visit( print ,v );
    }
    return 0;
}
