//
//  main.cpp
//  17_Concept_2_GOOD
//
//  Created by Sathya Babu on 14/05/23.
//

#include <iostream>
#include <type_traits>


template <typename T>
concept Copyable = std::is_copy_constructible_v<T>;


// Phase I

class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

class Copyable2 {
public:
    Copyable2() = default;
    Copyable2(const Copyable2&) = default;
    Copyable2& operator=(const Copyable2&) = default;
};



// Phase II

class MyClass {
public:
    MyClass() { std::cout << "Constructor called." << std::endl; }
    MyClass(const MyClass& other) { std::cout << "Copy constructor called." << std::endl; }
};


template <typename T>
// requires (!Copyable<T>) throws error while calling  copy_if_possible(obj1, obj2);
void copy_if_possible(const T& a, const T& b) requires Copyable<T> {
    T copy = a;
    copy = b;
    std::cout << "Object copied successfully." << std::endl;
}

int main() {
    // Phase I
    
    std::cout << std::boolalpha;
    std::cout << "Is NonCopyable copy constructible? " << std::is_copy_constructible_v<NonCopyable> << std::endl;
    std::cout << "Is Copyable copy constructible? " << std::is_copy_constructible_v<Copyable2> << std::endl;
    
    // Phase II
    
    MyClass obj1, obj2;
    
    // following line is not copyable!! obj1 is not copyable
   // std::unique_ptr< MyClass > obj1 = std::make_unique< MyClass >();
   
    
    copy_if_possible(obj1, obj2); // Output: Copy constructor called.
    int x = 5, y = 10;
    copy_if_possible(x, y); // Output: Object copied successfully.
    return 0;
}
/*
 Constructor called.
 Copy constructor called.
 Object copied successfully.
 Object copied successfully.
 Program ended with exit code: 0
 */

//#include <iostream>
//#include <vector>
//#include <type_traits>
//
//template <typename T>
//concept Copyable = std::is_copy_constructible_v<T>;
//
//struct Foo {};
//
//int main() {
//  static_assert(Copyable<int>);
// // static_assert(!Copyable<Foo>);
//
//    (!Copyable<Foo> );
//  std::vector<int> v1 {1, 2, 3};
//  std::vector<int> v2 = v1;
//
//  // Won't compile, as std::vector<Foo> is not copyable
//   std::vector<!Copyable<Foo>> v3;
//   std::vector<Foo> v4 = v3;
//
//  std::cout << "Copyable concept passed" << std::endl;
//
//  return 0;
//}
