//
//  main.cpp
//  17_optional
//
//  Created by Sathya Babu on 04/11/21.
//
#include <optional>

  #include <string>
  #include <iostream>
#include <complex>
using namespace std;

// convert string to int if possible:
/*
 
 std::optional<> model a nullable instance of an arbitrary type. The instance might be a member, an argument, or a return value. You could also argue that a std::optional<> is a container for zero or one element.
 
 */
  std::optional<int> asInt(const std::string& s)
  {
    try {
      return std::stoi(s);
    }
    catch (...) {
      return std::nullopt;
    }
}
int main() {
for (auto s : {"42", " 077", "hello", "0x33"} ) { // try to convert s to int and print the result if possible:
    
    std::optional<int> oi = asInt(s);
    
    if (oi) {
        std::cout << "convert '" << s << "' to int: " << *oi << "\n"; }
    else {
        std::cout << "can't convert '" << s << "' to int\n";
        }
    
    }
    
   
    
    std::optional<std::string> os;
    std::string s = "a very very very long string";
    os = std::move(s);
    std::string s2 = *os;
    std::string s3 = std::move(*os);
    // OK, moves // OK copies // OK, moves
    
    std::cout << "Moved on to s3 :  '" << s3 << endl ;
    return 0;
}
