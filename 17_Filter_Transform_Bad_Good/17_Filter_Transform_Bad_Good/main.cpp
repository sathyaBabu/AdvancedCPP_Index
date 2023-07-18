// 17_Filter_transform_Bad_Good

#include <iostream>
#include <ranges>

// 17_Filter_transform_Bad_Good
 
auto even (int i) { return 0 == i % 2; };
auto square(int i )  { return i * i; };
int main()
{
//    auto even = [](int i) { return 0 == i % 2; };
//    auto square = [](int i) { return i * i; };
    
    for (int i : std::views::iota(0, 7)  // reads from 0 - 6
                 | std::views::filter(even)
                // | std::views::transform(square)
         )
        std::cout << i << ' ';
    
    std::cout <<std::endl;
    
    
    
  auto ii = std::views::iota(0, 7)  //  // reads from 0 - 6
            | std::views::filter(even)
            | std::views::transform(square)  ;
    
    for( auto x : ii ){
        std::cout << x << ' ';
    }
    std::cout <<std::endl;
    
}
/*
 0 2 4 6
 0 4 16 36
 Program ended with exit code: 0
 */
