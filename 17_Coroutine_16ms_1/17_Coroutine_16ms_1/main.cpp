//
//  main.cpp
//  17_Coroutine_16ms_1
//
//  Created by Sathya Babu on 15/04/23.
//
#include <iostream>
#include <chrono>
#include <thread>
#include <experimental/coroutine>

class sleep_for_16ms {
public:
    struct promise_type {
        sleep_for_16ms get_return_object() {
            return {};
        }
        std::experimental::suspend_never initial_suspend() { return {}; }
        std::experimental::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    sleep_for_16ms() = default;

    void await_suspend(std::experimental::coroutine_handle<promise_type>) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
};

std::experimental::generator<int> generate_numbers() {
    int i = 0;
    while (true) {
        co_yield i++;
        co_await sleep_for_16ms();
    }
}

int main() {
    auto numbers = generate_numbers();
    for (int i = 0; i < 10; i++) {
        std::cout << numbers << std::endl;
    }
    return 0;
}
