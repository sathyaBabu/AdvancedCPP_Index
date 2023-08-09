//
//  main.cpp
//  17_Clamp_Simple_1
//
//  Created by Sathya Babu on 19/04/23.
//

/*
 std::clamp is a C++17 algorithm that takes in a value and two boundary values, and returns the value if it is between the boundaries, otherwise the closest boundary value.
 
 In this example, value is initially set to 10, and lower_bound and upper_bound are set to 0 and 5 respectively. std::clamp is then called with these values, and the resulting clamped value is stored in clamped_value. Since 10 is greater than the upper bound of 5, clamped_value is set to 5. The original value and clamped value are then printed to the console.
 */
#include <iostream>
#include <algorithm>

int main() {
    int value = 10;
    int lower_bound = 0;
    int upper_bound = 5;
    
    
    int clampedValue1 = value;
    if (value < lower_bound) {
        clampedValue1 = lower_bound;
    } else if (value > upper_bound) {
        clampedValue1 = upper_bound;
    }
    
    
    std::cout << "Phase I using if : " << std::endl;
    
    std::cout << "Original value: " << value << std::endl;
    std::cout << "Clamped value: " << clampedValue1 << std::endl;

    
    std::cout << "Phase II using clamp  : " << std::endl;
    

    int clamped_value = std::clamp(value, lower_bound, upper_bound);

    std::cout << "Original value: " << value << std::endl;
    std::cout << "Clamped value: " << clamped_value << std::endl;

    return 0;
}
/*
 hase I using if :
 Original value: 10
 Clamped value: 5
 Phase II using clamp  :
 Original value: 10
 Clamped value: 5
 Program ended with exit code: 0
 */
