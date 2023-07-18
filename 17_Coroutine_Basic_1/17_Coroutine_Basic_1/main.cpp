//
//  main.cpp
//  17_Coroutine_Basic_1
//  co_yield 1
//  Created by Sathya Babu on 17/02/23.
//

#include <iostream>
//#include <coroutine>
#include <experimental/coroutine>
using namespace std;
/*
 n this example, we define a coroutine generator class CoroutineGenerator with a nested promise_type struct. The promise_type struct defines the promise object that is used to communicate with the coroutine function.

 The CoroutineGenerator class defines a move_next method to resume the coroutine and a current_value method to get the current value of the coroutine.

 We then define a coroutine function that uses the co_yield keyword to suspend the coroutine and return a value. When the coroutine is resumed, it resumes execution from the point where it was suspended.

 Finally, in the main function, we create a CoroutineGenerator object and call the move_next method to resume the coroutine and the current_value method to get the current value of the coroutine. The loop terminates when the coroutine is complete and the move_next method returns false.

 This example demonstrates the basic use of coroutines in C++. Coroutines provide a powerful tool for writing asynchronous and event-driven code. They can be used to simplify the implementation of generators, iterators, and state machines, and can be used in a wide variety of applications, such as networking, graphics, and game development.


////////// diffrence between Coroutines and threads 
 
 Coroutines and threads are both mechanisms for achieving concurrency in C++, but they have different approaches and use cases.

 A coroutine is a cooperative multitasking mechanism that allows a function to be suspended and resumed at specific points in its execution. Coroutines are lightweight, meaning they can be created and destroyed quickly and have minimal overhead. They are designed to be used for tasks that involve waiting for I/O operations or other blocking operations.

 Threads, on the other hand, are a preemptive multitasking mechanism that allow multiple threads of execution to run concurrently. Threads are heavyweight, meaning they have significant overhead and require more resources to create and manage. They are designed to be used for tasks that involve intensive computation or other CPU-bound operations.

 The main difference between coroutines and threads is in how they handle concurrency. Coroutines are cooperative, meaning that they rely on the programmer to explicitly yield control of execution when waiting for an operation to complete. This allows for more efficient use of system resources, as only one coroutine can be active at a time. Threads, on the other hand, are preemptive, meaning that the system scheduler determines when to switch between threads. This allows multiple threads to run concurrently, but also requires more resources to manage and can lead to inefficiencies in some cases.

 In summary, coroutines are a lightweight and efficient mechanism for achieving concurrency in tasks that involve waiting for I/O or other blocking operations, while threads are a heavyweight mechanism for achieving concurrency in tasks that involve intensive computation or other CPU-bound operations. Both mechanisms have their place in modern software development and can be used together in some cases to achieve optimal performance and efficiency.



 Regenerate response



 */

// Coroutine generator
class CoroutineGenerator {
public:
    struct promise_type {
        int current_value;

        CoroutineGenerator get_return_object() {
            return CoroutineGenerator(std::experimental::coroutine_handle<promise_type>::from_promise(*this));
        }
        std::experimental::suspend_always initial_suspend() { return {}; }
        std::experimental::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::terminate(); }
        void return_void() {}
        std::experimental::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }
    };

    CoroutineGenerator(std::experimental::coroutine_handle<promise_type> handle) : handle_(handle) {}
    ~CoroutineGenerator() { if (handle_) handle_.destroy(); }

    bool move_next() {
        if (not handle_.done()) {
            handle_.resume();
            return true;
        }
        return false;
    }

    int current_value() const { return handle_.promise().current_value; }

private:
    std::experimental::coroutine_handle<promise_type> handle_;
};

// Coroutine function
CoroutineGenerator coroutine() {
    co_yield 1;
    co_yield 2;
    co_yield 3;
}

// Main function
int main() {
    CoroutineGenerator generator = coroutine();

    while (generator.move_next()) {
        std::cout << generator.current_value() << std::endl;
    }

    return 0;
}

/*
 1
 2
 3
 3
 Program ended with exit code: 0
 */
