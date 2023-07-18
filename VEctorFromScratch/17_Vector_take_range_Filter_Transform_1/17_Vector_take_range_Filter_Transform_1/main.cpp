//
//  main.cpp
//  17_Vector_take_range_Filter_Transform_1
//
//  Created by Sathya Babu on 09/04/23.
//  17_View_std_1
// https://www.cppstories.com/2022/ranges-composition/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

#include <iomanip>

void transform() {
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  
  // Create a range that transforms each element of the original range
  auto square_numbers = numbers | std::views::transform([](int x) { return x * x; });
  
  // Print the transformed numbers
    std::cout << " Transform 1  ";
  for (int number : square_numbers) {
    std::cout << number << " "; // 1 4 9 16 25
  }
  std::cout << std::endl;

  std::vector<std::string> words = {"apple", "banana", "cherry"};

  // Create a range that transforms each element of the original range
  auto word_lengths = words | std::views::transform([](const std::string& word) { return word.length(); });

  // Print the transformed words
    std::cout << " Transform 2  ";
  for (int length : word_lengths) {
    std::cout << length << " "; //  5 6 6
  }
  std::cout << std::endl;

 
}
//In this example, we create two ranges using std::views::transform. The first range transforms each number in the numbers vector to its square. The second range transforms each word in the words vector to its length. We then print the transformed numbers and lengths using a for loop.
//
//std::views::transform takes a function as an argument that transforms each element of the original range. In the first example, we pass a lambda function that takes an integer and returns its square. In the second example, we pass a lambda function that takes a string reference and returns the length of the string.


void join() {
    std::vector<std::vector<int>> outer {{1, 2}, {3, 4}, {5, 6}};

    // concatenate the inner vectors into a single range
    auto joined = outer | std::views::join;

    // iterate over the concatenated range and print its elements
    std::cout << " Join ";
    for (int n : joined) {
        std::cout << n << ' ';  // 1 2 3 4 5 6
    }
    std::cout << '\n';
}
//
//In this example, we have a vector of vectors outer containing three inner vectors, each of which contains two integers. We apply the std::views::join view adapter to this range, which creates a new range that concatenates the inner vectors into a single range. We then iterate over the concatenated range and print its elements.
//
//The output of this program will be:
//
//Copy code
//1 2 3 4 5 6
//Note that the std::views::join view does not copy or move the elements of the input ranges. Instead, it stores iterators to the input ranges and dereferences them as needed when iterating over the concatenated range. This makes std::views::join efficient and lightweight.
//

//In this example, we first create a std::vector<int> called nums with five elements: 1, 2, 3, 4, and 5.
//
//Then, we use std::views::take to create a new view called first_three, which only contains the first three elements of nums.
//
//Finally, we loop over the first_three view using a range-based for loop and print out each number. The output of this program will be:
//
//Copy code
//1 2 3
//As you can see, std::views::take allows us to easily create a new view that contains only a portion of an existing range.
//

//
//
//std::views::join example
//std::views::join is a view adapter in C++20 that concatenates the elements of ranges. It takes a range of ranges and returns a single range containing all the elements of the inner ranges in order.


//
//
//




void filter() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Use views::filter to filter only even numbers
    auto even_nums = nums | std::views::filter([](int n) { return n % 2 == 0; });

    // Print the filtered range
    std::cout << " Filter ";
    for (int n : even_nums) {
        std::cout << n << ' ';
    }
    std::cout << '\n'; // 2 4 6 8 10

  
}
/*
 In the above code, we create a std::vector of integers called nums that contains the numbers from 1 to 10. We then use std::views::filter to create a new range view called even_nums that contains only the even numbers from nums.

 Finally, we print out the filtered range using a range-based for loop. The output of the program will be:
 
 2 4 6 8 10


 
 */

/*
 
    Using Vector to reverse drop an element and print
 
 
 */
int even_1(int i ) { return 0 == i % 2; };

void reverse(){
    const std::vector numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto even = [](int i) { return 0 == i % 2; };

    std::vector<int> temp;
    std::copy_if(begin(numbers), end(numbers), std::back_inserter(temp), even_1);
    std::vector<int> temp2(begin(temp)+1, end(temp));
    
    std::cout << " Reverse Bad way ";
    for (auto iter = rbegin(temp2); iter!=rend(temp2); ++iter)
        std::cout << *iter << ' ';
    // 10 8 6 4 Program ended with exit code: 0
    
    // Phase II Better way reffer  17_View_std_1   for independent same code which works
   // using namespace std::views;
    std::cout << " \n Reverse Better way ";
       auto rv = std::views::reverse(std::views::drop(std::views::filter(numbers, even), 1));
             //auto rv = reverse(filter(numbers, even));
        for (auto& i : rv)
            std::cout << i << ' ';
}

void trim_transform_1(){
    const std::string text { "    Hey there!" };
    std::cout << std::endl<< (text) << '\n';

    auto firstNonSpace = std::find_if_not(text.begin(), text.end(), ::isspace);
    std::string temp(firstNonSpace, text.end());
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        
    std::cout << std::quoted(temp) << '\n'; // #include <iomanip>
}
void trim_transform_2(){
    const std::string text { "    Hey there!" };
    std::cout << std::endl<< (text) << '\n';
// c++ 23
    
//    auto conv = std::views::transform(
//            std::views::drop_while(text, ::isspace),
//            ::toupper
//        );
//
//    std::string temp(conv.begin(), conv.end());
    
    //  c++ 23
//    auto temp = text |
//                    std::views::drop_while(isspace) |
//                    std::views::transform(::toupper) |
//                    std::ranges::to<std::string>();
//
//
    std::cout << std::quoted(text) << '\n'; // #include <iomanip>
}


int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    for (int x : v | std::views::take(3)) {
        std::cout << x << ' ';
    }
    std::cout << '\n';  // 1 2 3
    
    transform();
    join();
    filter();
    reverse();
    trim_transform_1();

    return 0;
}
/*
 
 1 2 3
  Transform 1  1 4 9 16 25
  Transform 2  5 6 6
  Join 1 2 3 4 5 6
  Filter 2 4 6 8 10
  Reverse Bad way 10 8 6 4
  Reverse Better way 10 8 6 4
     Hey there!
 "HEY THERE!"
 Program ended with exit code: 0
 
 */
