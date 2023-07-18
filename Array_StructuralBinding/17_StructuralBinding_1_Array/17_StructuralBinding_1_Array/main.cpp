//
//  main.cpp
//  17_StructuralBinding_1_Array
//
//  Created by Sathya Babu on 08/07/23.
//
#include <iostream>
#include<map>

struct Point {
    int x;
    int y;
};
// phase II

struct MyStruct {
      int i = 0;
      std::string s;
};


// phase III

MyStruct getStruct() {
     return MyStruct{42, "hello"};
}


// phase VIII raw array

auto getArr() -> int( & )[2] {
    
     int arr[] = {1, 2};
    return arr;
}

int main() {
    Point p{10, 20};

    auto [x, y] = p;

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;

    // phase II
    MyStruct ms{ 123,"Bangalore"};
//    ms.i = 100 ;
//    ms.s = "Sathya ";
    
    auto [u,v] = ms;
    
    std::cout << "u : " << u  << std::endl;  // 100
    std::cout << "v : " << v << std::endl;   // Sathya

    // phase III
    
    std::cout << "Legacy Way 1 MyStruct  i  : " << getStruct().i  << std::endl;  // MyStruct i   : 42
    std::cout << "Legacy Way 2 MyStruct  s  : " << getStruct().s << std::endl;   //MyStruct  s  : hello

    MyStruct myStru = getStruct();
    std::cout << "Legacy Way MyStruct  i  : " << myStru.i << std::endl;  // MyStruct i   : 42
    std::cout << "Legacy Way MyStruct  s  : " << myStru.s << std::endl;
    
    // cleaner way of coding
    
    std::cout << "Clean code using Structural Binding...  C++ 17 "  << std::endl;
    
    auto[ id, val ] = getStruct(); // id and val name i and s of returned struct
    
    id += 123 ;  // works
  
    std::cout << "id : " << id << std::endl;  //id = 43
    std::cout << "val : " << val << std::endl;   // hello

    // Phase IV  without struct binding
    
    std::map<int, std::string> myMap;
       myMap.insert({1, "one"});
       myMap.insert({2, "two"});
       myMap.insert({3, "three"});

       // Iterating over the map using a for loop
       for (const auto& pair : myMap) {
           int key           = pair.first;
           std::string value = pair.second;

           std::cout << "Key: " << key << ", Value: " << value << std::endl;
       }
    /*
     Key: 1, Value: one
     Key: 2, Value: two
     Key: 3, Value: three
     */

    
    // Phase V with structured binding
    /*
     With structured bindings, we can directly extract and assign the key and value of each
     pair using [key, value] instead of accessing them explicitly using pair.first
     and pair.second.

    Using structured bindings improves the readability and conciseness of the
     code by eliminating the need for explicit member function calls.

   

     */
    
    // Iterating over the map using structured bindings
       for (const auto& [key, value] : myMap) {
           std::cout << "Key: " << key << ", Value: " << value << std::endl;
       }
    
    /*
     Key: 1, Value: one
     Key: 2, Value: two
     Key: 3, Value: three
     */

    
    // Phase VI a deep dive into Structured Bindings
    
    auto [ u1,v1 ] = ms;
//    behaves as if we’d initialize a new entity e with ms and let the structured bindings u and v become
//    alias names for the members of this new object, similar to defining:
    
    
    auto e = ms;
//    aliasname u = e.i;
//    aliasname v = e.s;
    
//    decltype( u1 ) = e.i;
//    decltype( v1 ) = e.s;
    
    MyStruct ms2{42,"hello"};
    auto [u2,v2] = ms2;
    
    ms2.i = 77;
    std::cout << u2; // prints 42
    std::cout << ms2.i; // prints 77
    
    
    //////
    ///  using Reference   NOT LVALUE!
    
    
    MyStruct ms3{420,"hello Mr 420"};
    auto& [u3,str] = ms3;
    
    ms.i = 77;
    
    std::cout << " u3 " << u3 << std::endl ; // 420
    u3= 99;
    std::cout <<  " ms3.i " <<ms3.i << std::endl ; // 99
    std::cout <<  " ms3.s  " <<ms3.s << std::endl ; // hello Mr 420
    std::cout <<  " str " << str << std::endl ; // hello Mr 420
    // the initialized entity is a reference to ms // affects the value of u
    
    // get ref
    const auto& [a,b] = getStruct();
    std::cout << "a : " << a << '\n'; // OK  a : 42
    
    // std::cout << "a : " << a << '\n';
    // Cannot assign to variable 'a' with const-qualified type 'const int'
    
    // Phase VII  pair
    
    std::pair<int, std::string> myPair(42, "Paired a val with string.");

        auto [val1, str1] = myPair;

        std::cout << "val1 :  " << val1 << std::endl;
        std::cout << "str1 :  " << str1 << std::endl;
    
    // phase VIII raw array
    std::cout << "Legacy way of usibg array  "  << std::endl;
    auto& arr = getArr();

        // Access and modify elements of the array
        arr[0] = 10;
        arr[1] = 20;

        // Print the modified array
        for (int i = 0; i < 2; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    
    std::cout << "Clean code using Structural Binding...  C++ 17 "  << std::endl;
    auto [xx, yy] = getArr();
    std::cout << "array 1  :  " << xx << std::endl;
    std::cout << "array 2  :  " << yy << std::endl;
    return 0;
}
