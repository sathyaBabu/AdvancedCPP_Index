//
//  main.cpp
//  CoRoutineGenerate_1
//
//  Created by Sathya Babu on 11/07/23.
//
#include <iostream>
#include <coroutine>

template<typename T>
struct generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    
    struct promise_type {
        T current_value;
        
        auto get_return_object() {
            return generator{handle_type::from_promise(*this)};
        }
        
        auto initial_suspend() {
            return std::suspend_always{};
        }
        
        auto final_suspend() noexcept {
            return std::suspend_always{};
        }
        
        void return_void() {}
        
        void unhandled_exception() {
            std::terminate();
        }
        
        auto yield_value(T value) {
            current_value = value;
            return std::suspend_always{};
        }
    };
    
    handle_type coro;
    
    explicit generator(handle_type h) : coro(h) {}
    
    ~generator() {
        if (coro)
            coro.destroy();
    }
    
    // Iterator support
    struct iterator {
        handle_type coro;
        bool done;
        
        iterator& operator++() {
            coro.resume();
            done = coro.done();
            return *this;
        }
        
        bool operator!=(const iterator& other) const {
            return done != other.done;
        }
        
        const T& operator*() const {
            return coro.promise().current_value;
        }
    };
    
    iterator begin() {
        coro.resume();
        return { coro, coro.done() };
    }
    
    iterator end() {
        return { nullptr, true };
    }
};

generator<int> range(int start, int end) {
    while (start < end) {
        co_yield start;
        start++;
    }
}

int main() {
    for (int n : range(0, 10)) {
        std::cout << n << std::endl;
    }
    
    return 0;
}
/*
 0
 1
 2
 3
 4
 5
 6
 7
 8
 9
 Program ended with exit code: 0
 */
