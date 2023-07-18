//
//  main.cpp
//  17_View_std_1
//
//  Created by Sathya Babu on 12/04/23.
// 17_Vector_Take_range_filter_Transform_1

#include <algorithm>
#include <vector>
#include <iostream>
#include <ranges>

// phase II
#include <ranges>   // new header!
#include<numeric>    // accumulate

////
/*
 std::views is a library introduced in C++20 that provides a range of views that can be applied to sequences or containers. It allows you to create and compose views without copying the underlying data.

 Here is an example of how to use std::views::filter and std::views::transform to filter and transform elements of a std::vector:
 
 In this example, std::views::filter creates a filtered view of the numbers vector, only including odd numbers. Then std::views::transform creates a transformed view of the filtered view, computing the squares of the odd numbers. Finally, the transformed view is printed out. Since views do not copy the underlying data, this is an efficient way to apply multiple transformations to a container without creating intermediate containers.
 */



void compose_view_filter_transform(){
    
    std::cout << "\n compose_view_filter_transform ! \n ";
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};

        // Create a view that only includes odd numbers
        auto odd_numbers = numbers | std::views::filter([](int x){ return x % 2 != 0; });

        // Create a view that includes the squares of the odd numbers
        auto squares_of_odd_numbers = odd_numbers | std::views::transform([](int x){ return x * x; });

        // Print the squares of the odd numbers
        for (int x : squares_of_odd_numbers) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    // 1 9 25

}

void compose_betterWay(){
    std::cout << " \n compose a better way  \n " << std::endl ;
    std::vector vec{1, 2, 3, 4, 5, 6};
    auto v = vec | std::views::reverse | std::views::drop(2);

    std::cout << *v.begin() << '\n';
}

////
class Square {
public:
    int operator()(int x) const {
        return x * x;
    }
};
void views_transform_ssquare(){
    
    std::cout << " \n Adding our class Square to std::views::transform  \n " << std::endl ;
    std::vector<int> nums = {1, 2, 3, 4, 5};

        // Define a callable object that squares each element of the range
        Square square;

        // Use std::views::transform to create a new range of squares
        // square each number first then accumulate
        auto squares = nums | std::views::transform(square);

        // Use std::accumulate to compute the sum of the squares
        int sum = std::accumulate(squares.begin(), squares.end(), 0);

        std::cout << "The sum of the squares is: " << sum << '\n'; // 55
}
void dropTill_3() {
    std::cout << "\n Display all numbers ! \n ";
    std::vector <int> vec = {1, 2, 3, 4, 5,20,30,40,50};
    // print entire vector
    for (const int& num : vec) {
        std::cout << num << ' ';
    }
    std::cout << "\n Drop till 3 ! \n ";
    // print the vector but skip first few elements
    for (const int& num : vec | std::views::drop(3)) { // drops till 3
        std::cout << num << ' ';
    }
    
}
/*
 Hello world!1 2 3 4 5 20 30 40 50
 4 5 20 30 40 50 Program ended with exit code: 0
 */

//////
int is_even(int n )  {return n % 2 == 0;};
void main2(){
    namespace rv = std::ranges::views;
    // create a functional pipeline to transform a vector of integers:
        std::vector<int> n { 1,1,2,3,5,8,13,21,34,55,89};
        
        auto v = n | rv::filter(is_even)
                   | rv::reverse
                   | rv::take(2) ;
        
       
        for( auto i : v ){
            std::cout << " : " << i << std::endl;  // 34  8

        }
        // or
       // std::ranges::copy(v, std::ostream_iterator< int >( std::cout, " " ) );
}
int main() {
    const std::vector numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto even = [](int i) { return 0 == i % 2; };

    std::vector<int> temp;
    std::copy_if(begin(numbers), end(numbers), std::back_inserter(temp), even);
    std::vector<int> temp2(begin(temp)+1, end(temp));
    
    for (auto iter = rbegin(temp2); iter!=rend(temp2); ++iter)
        std::cout << *iter << ' ';
    // 10 8 6 4 Program ended with exit code: 0
    
    // Phase II Better way
    using namespace std::views;
       auto rv = reverse(drop(filter(numbers, even), 1));
             //auto rv = reverse(filter(numbers, even));
        for (auto& i : rv)
            std::cout << i << ' ';
    
    main2();  // implementing the above code withot holding ref..
    
    
    dropTill_3();
    compose_view_filter_transform();
    
    compose_betterWay(); // 4
    
    views_transform_ssquare();
   
}
/*
 10 8 6 4 10 8 6 4
 : 34
  : 8
  Display all numbers !
  1 2 3 4 5 20 30 40 50
  Drop till 3 !
  4 5 20 30 40 50 Program ended with exit code: 0
 */
