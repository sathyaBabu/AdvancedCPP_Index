//
//  main.cpp
//  17_Coroutines__2
//
//  Created by Sathya Babu on 20/10/22.
//  https://www.scs.stanford.edu/~dm/blog/c++-coroutines.html
// https://stackoverflow.com/questions/67306337/a-coroutines-promise-must-declare-either-return-value-or-return-void-erro

#include <concepts>
#include <experimental/coroutine>
#include <exception>
#include <iostream>
struct ReturnObject {
    struct promise_type {
        ReturnObject get_return_object() { return {}; }
        std::experimental::suspend_never initial_suspend() { return {}; }
        std::experimental::suspend_never final_suspend() noexcept { return{}; }
        void unhandled_exception() {}
        
        void return_void() noexcept {}
        
    };
};

struct Awaiter {
    std::experimental::coroutine_handle<>* hp_;
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend( std::experimental::coroutine_handle<> h) { *hp_ = h; }
    constexpr void await_resume() const noexcept {}
};

ReturnObject
counter( std::experimental::coroutine_handle<>* continuation_out)
{
    Awaiter a{ continuation_out };
    for (unsigned i = 0;; ++i) {
        co_await a;
        std::cout << "counter: " << i << std::endl;
    }
}

// coroutine will be in suspend state to start with has to be resumed to get going
int
main()
{
    std::experimental::coroutine_handle<> h;
    counter(&h);
    for (int i = 0; i < 100; ++i) {
        std::cout << "In main1 function\n";
        h();
    }
    h.destroy();
    return 1 ;
}
/*
 
 In main1 function
 counter: 0
 In main1 function
 counter: 1
 In main1 function
 counter: 2
 In main1 function
 counter: 3
 In main1 function
 counter: .. 99
 */

