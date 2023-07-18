//
//  main.cpp
//  17_Coroutine_1_ContextSwitching
//
//  Created by Sathya Babu on 18/09/22.
//  Phase I corotine how it evolved
//#include <stdio.h>
//#include <ucontext.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <iostream>
//
//int main( ) {
//    ucontext_t ctx = {0};
//
//    getcontext(&ctx);   // Loop start
//    puts("Hello world");
//    sleep(1);
//    setcontext(&ctx);   // Loop end
//
//    return EXIT_SUCCESS;
//}

// PHASE II ERROR at  #include <coroutine>
#include <coroutine>
#include <iostream>

struct HelloWorldCoro {
    struct promise_type { // compiler looks for `promise_type`
        HelloWorldCoro get_return_object() { return this; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() { return {}; }
    };

    HelloWorldCoro(promise_type* p) : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}
    ~HelloWorldCoro() { m_handle.destroy(); }

    std::coroutine_handle<promise_type>      m_handle;
};

HelloWorldCoro print_hello_world() {
    std::cout << "Hello ";
    co_await std::suspend_always{};
    std::cout << "World!" << std::endl;
}

int main() {
    HelloWorldCoro mycoro = print_hello_world();

    mycoro.m_handle.resume();
    mycoro.m_handle(); // Equal to mycoro.m_handle.resume();
    return EXIT_SUCCESS;
}
// g++-10 -std=c++20 -fcoroutines -fno-exceptions -o myapp Main.cpp

