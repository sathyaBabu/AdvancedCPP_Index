//
//  main.cpp
//  17_CoroutineBasics_1_cpp
//
//  Created by Sathya Babu on 17/02/23.
//

/*
 
 Coroutines are a new feature introduced in C++20 that allow a function to be suspended and resumed later, allowing for more efficient and readable asynchronous code. Here is an example of a simple coroutine in C++20:
 In this example, we define a coroutine function called coroutine_example(), which returns a coroutine_return_type object. The coroutine_return_type struct has a promise_type struct nested inside it, which provides the implementation details for the coroutine.

 The promise_type struct provides the co_return value for the coroutine, and also provides functions for the initial and final suspends, handling exceptions, and returning a value from the coroutine.

 In the main() function, we create a coroutine_return_type object by calling coroutine_example(). We then print out the value member of the promise_type object inside the coroutine, which is set to 42. We then set the value member to 0 and resume the coroutine, which returns the 42 value as the result.

 This is a simple example of a coroutine in C++20, demonstrating how the coroutine_handle and promise_type classes can be used to create a coroutine and manage its execution.
 */

#include <iostream>
#include <experimental/coroutine>

struct coroutine_return_type {
    struct promise_type {
        int value;

        coroutine_return_type get_return_object() {
            return std::experimental::coroutine_handle<promise_type>::from_promise(*this);
        }
        std::experimental::suspend_never initial_suspend() { return {}; }
        std::experimental::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::terminate(); }
        void return_value(int value_) { value = value_; }
    };

    std::experimental::coroutine_handle<promise_type> handle;

    coroutine_return_type(std::experimental::coroutine_handle<promise_type> handle_) : handle(handle_) {}
    ~coroutine_return_type() {
        if (handle) {
            handle.destroy();
        }
    };
};

coroutine_return_type coroutine_example() {
    co_return 42;
}

int main() {
    coroutine_return_type coroutine = coroutine_example();
    std::cout << "start : "<< coroutine.handle.promise().value << std::endl;
    coroutine.handle.promise().value = 123;
   // coroutine.resume();
    coroutine.handle.resume();
    std::cout <<  "After set data to value  : "<<coroutine.handle.promise().value << std::endl;
    coroutine.handle.resume();
    return 0;
}
