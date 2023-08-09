//
//  main.cpp
//  2_4_SI_LambdaWithVariant
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include<vector>
using  namespace  std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    // Visitor( visitable )
    auto printVisitor = []( const auto& t )  { cout << t << endl ;  };
//
//    std::variant< int, float , std::string > intFloatString{ 1234.89f };
//    std::visit( printVisitor, intFloatString );
    
    std::vector< std::variant< int, float , std::string > > intFloatString{ 123, 12.345f, "Hello Lambda"};
    
    for(auto visitorArg : intFloatString)
      std::visit( printVisitor, visitorArg );
    
    return 0;
}

/*
 
 Hello, World!
 10
 123
 12.345
 Hello Lambda
 Program ended with exit code: 0
 */
