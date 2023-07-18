//
//  main.cpp
//  17_Coroutine_Fib_Generator_1
//
//  Created by Sathya Babu on 06/04/23.
//  Coroutine Fib Generator
// to search for this created code in GPT

//   Coroutines Lazy generators with Coroutines an example in c++
#include <iostream>
#include <experimental/coroutine>
/*
 how coroutines can be used to implement lazy generators in C++.
 
 In this example, we define a fibonacci_generator struct with a nested promise_type struct. The promise_type struct defines the promise object that is returned from the coroutine. We use the get_return_object method to get the generator object, and the initial_suspend and final_suspend methods to specify when the coroutine should be suspended and resumed. We also define a yield_value method to return a value to the caller and suspend the coroutine.

 The fibonacci_generator struct also has a constructor and a move_next method to allow the caller to move to the next value in the sequence. The current_value method returns the current value of the generator.

 In the generate_fibonacci_sequence function, we define a loop that generates the Fibonacci sequence using co_yield. In the main function, we create a fibonacci_generator object and call move_next to get the next value in the sequence. We repeat this 10 times and print each value to the console.

 This example shows how coroutines can be used to implement lazy generators in C++.
 */

struct fibonacci_generator {
    struct promise_type {
        int current = 1, next = 1;
        fibonacci_generator get_return_object() { return fibonacci_generator(std::experimental::coroutine_handle<promise_type>::from_promise(*this)); }
        std::experimental::suspend_always initial_suspend() { return {}; }
        std::experimental::suspend_always final_suspend() noexcept { return {}; }
        std::experimental::suspend_always yield_value(int value) { current = value; return {}; }
        void unhandled_exception() { std::terminate(); }
    };
    fibonacci_generator(std::experimental::coroutine_handle<promise_type> handle) : handle(handle) {}
    ~fibonacci_generator() { if (handle) handle.destroy(); }
    fibonacci_generator(const fibonacci_generator&) = delete;
    fibonacci_generator(fibonacci_generator&& other) : handle(other.handle) { other.handle = nullptr; }
    int current_value() const { return handle.promise().current; }
    bool move_next() {
        if (handle.done()) {
            return false;
        } else {
            handle.promise().yield_value(handle.promise().current);
            std::swap(handle.promise().current, handle.promise().next);
            handle.resume();
            return true;
        }
    }
private:
    std::experimental::coroutine_handle<promise_type> handle;
};

fibonacci_generator generate_fibonacci_sequence() {
    int current = 0, next = 1;
    while (true) {
        int value = current;
        current = next;
        next = value + current;
        co_yield value;
    }
}

int main() {
    fibonacci_generator fibonacci = generate_fibonacci_sequence();
    for (int i = 0; i < 10; i++) {
        fibonacci.move_next();
        std::cout << fibonacci.current_value() << std::endl;
    }
    return 0;
}
/*
 0
 1
 1
 2
 3
 5
 8
 13
 21
 34
 Program ended with exit code: 0
 */
