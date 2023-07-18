//
//  main.cpp
//  17_Coroutine_StateMAchine
//
//  Created by Sathya Babu on 11/04/23.
//
/*
#include <iostream>
#include <coroutine>


// std::experimental::coroutine_handle<> handle;
// Define the states of the state machine
enum class State {
    Initial,
    Running,
    Paused,
    Finished
};

// Define the coroutine
struct StateMachine {
    // The coroutine handle
    std::coroutine_handle<> handle;
    // The current state of the state machine
    State state;

    // The constructor initializes the coroutine and sets the state to Initial
    StateMachine(std::coroutine_handle<> h) : handle(h), state(State::Initial) {}

    // The destructor releases the coroutine handle
    ~StateMachine() {
        if (handle) {
            handle.destroy();
        }
    }

    // The coroutine function
    void operator()() {
        // Initialize the state machine
        state = State::Running;

        // Loop until the state machine is finished
        while (state != State::Finished) {
            switch (state) {
                // The initial state, do some initialization
                case State::Initial:
                    std::cout << "Initializing...\n";
                    state = State::Running;
                    break;

                // The running state, do some processing
                case State::Running:
                    std::cout << "Processing...\n";
                    state = State::Paused;
                    // Yield the coroutine
                    co_yield;
                    break;

                // The paused state, wait for user input to resume processing
                case State::Paused:
                    std::cout << "Paused. Press enter to continue...\n";
                    std::cin.get();
                    state = State::Running;
                    break;

                // The finished state, cleanup and exit the coroutine
                case State::Finished:
                    std::cout << "Cleaning up...\n";
                    break;
            }
        }
    }
};

int main() {
    // Create the coroutine and the state machine
    auto coroutine = StateMachine{StateMachine::promise_type().get_return_object()};
    coroutine.handle.resume();

    // Loop until the coroutine is finished
    while (coroutine.state != State::Finished) {
        // Resume the coroutine
        coroutine.handle.resume();

        // Check if the coroutine is done
        if (coroutine.handle.done()) {
            coroutine.state = State::Finished;
        }
    }

    // Release the coroutine handle
    coroutine.handle = nullptr;

    return 0;
}
*/


#include <iostream>
#include<experimental/coroutine>
#include <coroutine>

class StateMachine {
public:
    struct promise_type {
        StateMachine get_return_object() {
            return StateMachine{handle_type::from_promise(*this)};
        }
        
        std::suspend_never initial_suspend() noexcept {
            return {};
        }
        
        std::suspend_never final_suspend() noexcept {
            return {};
        }
        
        void return_void() {}
        void unhandled_exception() {}
        
        std::experimental::coroutine_handle<> get_handle() const noexcept {
            return handle_type::from_promise(*this);
        }
    };
    
    explicit StateMachine(std::coroutine_handle<promise_type> handle)
        : handle_{handle} {}
    
    ~StateMachine() {
        if (handle_) {
            handle_.destroy();
        }
    }
    
    void resume() {
        if (handle_) {
            handle_.resume();
        }
    }
    
private:
    using handle_type = std::coroutine_handle<promise_type>;
    handle_type handle_;
};

StateMachine foo() {
    std::cout << "Start\n";
    co_await std::suspend_always{};
    std::cout << "Middle\n";
    co_await std::suspend_always{};
    std::cout << "End\n";
}

int main() {
    StateMachine sm = foo();
    sm.resume();
    sm.resume();
    return 0;
}

