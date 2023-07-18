//
//  main.cpp
//  17_Coroutine_CoYeild_1
//
//  Created by Sathya Babu on 09/04/23.
//
/*
 In this example, we define a coroutine range that takes two integers start and end and produces a sequence of integers between them. Inside the coroutine, we use co_yield to produce the next value in the sequence and suspend the coroutine. The coroutine resumes execution when getValue() is called on the generator object returned by range.

 The promise_type struct is used to define the promise object associated with the coroutine. It has a current_value member that holds the current value produced by the coroutine. The get_return_object() function is used to create the generator object that will be returned by the coroutine.

 The initial_suspend() and final_suspend() functions are used to specify when the coroutine should be suspended and resumed. In this case, we always suspend and resume the coroutine immediately.

 The yield_value() function is called by co_yield to produce a value and suspend the coroutine. It sets the current_value member of the promise object and returns a suspend_always object to indicate that the coroutine should be suspended.

 Finally, in main(), we create a generator object gen by calling range(1, 5). We then call getValue() on the generator object to get the next value in the sequence. This will cause the coroutine to resume execution, produce a value using co_yield, and then suspend again. We repeat this process until we have received all values in the sequence.
 */
#include <iostream>
#include <experimental/coroutine>

struct Generator {
    struct promise_type {
        int current_value;

        auto get_return_object() {
            return Generator{ std::experimental::coroutine_handle<promise_type>::from_promise(*this) };
        }
        auto initial_suspend() { return std::experimental::suspend_always{}; }
        auto final_suspend() { return std::experimental::suspend_always{}; }
        void unhandled_exception() { std::exit(1); }
        auto yield_value(int value) {
            current_value = value;
            return std::experimental::suspend_always{};
        }
    };

    std::experimental::coroutine_handle<promise_type> coroutine;

    Generator(std::experimental::coroutine_handle<promise_type> h) : coroutine(h) {}
    ~Generator() { if (coroutine) coroutine.destroy(); }

    int getValue() {
        coroutine.resume();
        return coroutine.promise().current_value;
    }
};

Generator range(int start, int end) {
    for (int i = start; i <= end; ++i) {
        co_yield i;
    }
}

int main() {
    auto gen = range(1, 5);
    std::cout << gen.getValue() << std::endl; // 1
    std::cout << gen.getValue() << std::endl; // 2
    std::cout << gen.getValue() << std::endl; // 3
    std::cout << gen.getValue() << std::endl; // 4
    std::cout << gen.getValue() << std::endl; // 5
    return 0;
}
