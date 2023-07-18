//
//  main.cpp
//  17_Functional_Composition_4_HandleErr
//
//  Created by Sathya Babu on 23/06/23.
//
#include <iostream>
#include <functional>
#include <variant>

// Error type
struct Error {
    std::string message;
};

// Function type for error-handling steps
using ErrorHandler = std::function<std::variant<int, Error>(int)>;

// Error-handling functions
std::variant<int, Error> divideByTwo(int value) {
    if (value % 2 == 0) {
        return value / 2;
    } else {
        return Error{"Value is not divisible by 2"};
    }
}

std::variant<int, Error> addTen(int value) {
    return value + 10;
}

std::variant<int, Error> subtractFive(int value) {
    if (value >= 5) {
        return value - 5;
    } else {
        return Error{"Value is less than 5"};
    }
}

// Function for composing error-handling functions
template<typename Func1, typename Func2>
auto compose(Func1 f1, Func2 f2) {
    return [=](int x) -> std::variant<int, Error> {
        auto result = f1(x);
        if (std::holds_alternative<int>(result)) {
            return f2(std::get<int>(result));
        } else {
            return std::get<Error>(result);
        }
    };
}

int main() {
    // Build the error-handling chain
    auto errorHandler = compose( compose(divideByTwo, addTen), subtractFive );

    // Test the error handling
    int value = 7;
    auto result = errorHandler(value);
    if (std::holds_alternative<int>(result)) {
        std::cout << "Result: " << std::get<int>(result) << std::endl;
    } else {
        std::cout << "Error: " << std::get<Error>(result).message << std::endl;
    }

    return 0;
}
// Error: Value is not divisible by 2

