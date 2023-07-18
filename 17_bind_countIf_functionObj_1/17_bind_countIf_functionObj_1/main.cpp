//
//  main.cpp
//  17_bind_countIf_functionObj_1
//
//  Created by Sathya Babu on 19/03/23.
// std::bind acts as a functional adapter  function adapter


#include <iostream>
using namespace std ;
// phase I


int add(int first, int second)
{
    cout << first <<" " << second << endl;
    return first + second;
}
// Phase III
//                20         10
int divide(int first, int second)
{
    return first / second  ;   // 20 / 2
}
int divideMe(int number, int den)
{
    std::cout << "number " << number << endl ;
    if( number % den == 0 )
    return true  ;   // 20 / 2
    
    return false;
}

// Phase VI  function adapter
using namespace std::placeholders ;

int countIf()
{
    int arr[10] = {1,20,13,4,5,6,10,28,19,15};
    return std::count_if(arr, arr + sizeof(arr)/sizeof(int) , std::bind(&divideMe, _1, 5));
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    // Phase I
    // auto add_func = std::bind(&add, _1, _2);
    auto add_func = std::bind(&add, std::placeholders::_2, std::placeholders::_1);
    std::cout << "add_func sum " << add_func(7,3) <<std::endl ; //  (3,7) 10
    
    // Phase II
    auto add_func_2 = std::bind(&add, 300, std::placeholders::_1);
    std::cout << "add_func_2 sum " << add_func_2(7) << std::endl; // 307
    
    // Phase III  place holder
    auto div_func_placeHolder = std::bind(&divide, std::placeholders::_2,                                                               std::placeholders::_1);
    
    std::cout << "div_func_placeHolder divide  " << div_func_placeHolder(10,20) <<std::endl; // 2
    
    
    // Phase VI
    
   
    
    std::cout<<"Divisible number of elements " << countIf()<<std::endl;
    
    // Phase V
    // remember std::bind returns fun objec
    
    // following line works too
    //  auto default_add_funcObj = std::bind(&add, 123, _1);
    std::function<int (int) > default_add_funcObj = std::bind(&add, 123, _1);
       int  sum = default_add_funcObj(700);
        // Will return 823
    std::cout<< "std::bind returns fun object " << sum << std::endl;;
      
    
    return 0;
}
/*
 
 Hello, World!
 add_func sum 10
 add_func_2 sum 307
 div_func_placeHolder divide  2
 Divisible number of elements 4
 std::bind returns fun object 823
 Program ended with exit code: 0
 
 */
