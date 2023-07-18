//
//  main.cpp
//  17_Coroutines_Generate_1
//
//  Created by Sathya Babu on 21/10/22.
//
//

#include <concepts>
#include <experimental/coroutine>
//#include <experimental/generator>
#include <exception>
#include <iostream>
#include<algorithm>

resumable bar(){
    
}
resumable foo(){
    std::cout << " First line " << std::endl ;
    co_wait std::experimental::suspend_always();
    std::cout << " Second line " << std::endl ;
    co_wait std::experimental::suspend_always();
    std::cout << " Third line " << std::endl ;
   
}
int main(){
    
    resumable res1 = foo();
}
//
//
//
//std::experimental::Generator<int> getNext(int start = 0, int step = 1)
//  { auto value = start;
//    while (true) {
//        co_yield value;
//        value += step;
//    }
//}
// int main() {
//
//
//     std::cout << '\n';
//     std::cout << "getNext():";
//      auto gen1 = getNext();
//      for (int i = 0; i <= 10; ++i) {
//      gen1.next();
//      std::cout << " " << gen1.getValue();
//      }
//
//      std::cout << "\n\n";
//      std::cout << "getNext(100, -10):";
//      auto gen2 = getNext(100, -10);
//      for (int i = 0; i <= 20; ++i) {
//      gen2.next();
//      std::cout << " " << gen2.getValue();
//      }
//
//      std::cout << "\n";
//}
