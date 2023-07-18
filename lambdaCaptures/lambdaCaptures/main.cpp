//
//  main.cpp
//  lambdaCaptures
//
//  Created by Sathya Babu on 12/07/23.
//

#include <iostream>
#include <iostream>
#include <string>

// returns a lambda  same as :   void  ( *fn )();  ---  fn = fun; ---- fn()
auto makeDeveloper(const std::string& name)
{
  // Capture name by reference and return the lambda.
  return [&]() {
    std::cout << "I am a Developer , my name is " << name << '\n'; // Undefined behavior
  };
}

int main()
{
  
  auto sayName{ makeDeveloper("Sathya") };

  // Call the lambda function that make Sathya returned.
  sayName();

  return 0;
}
// I am a Developer , my name is Sathya
