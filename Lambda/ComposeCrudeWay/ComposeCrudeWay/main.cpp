//
//  main.cpp
//  ComposeCrudeWay
//
//  Created by Sathya Babu on 10/07/23.
//


#include <iostream>
#include <functional>

template <typename F>
concept Function = requires(F f) {
    typename std::invoke_result_t<F>;
};

template <Function F1, Function F2>
auto operator>>(F1 f1, F2 f2) {
    return [f1, f2](auto input) {
        return f2(f1(input));
    };
}

int addOne(int x) {
    return x + 1;
}

int multiplyByTwo(int x) {
    return x * 2;
}

int subtractThree(int x) {
    return x - 3;
}

int divideByFour(int x) {
    return x / 4;
}

int main() {
    auto composed = [](int x) {
        return divideByFour(subtractThree(multiplyByTwo(addOne(x))));
    };

    int input = 10;
    int result = composed(input);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
// Result: 4
