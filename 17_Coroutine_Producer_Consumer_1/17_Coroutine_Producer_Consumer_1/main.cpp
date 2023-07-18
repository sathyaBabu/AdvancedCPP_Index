//
//  main.cpp
//  17_Coroutine_Producer_Consumer_1
//
//  Created by Sathya Babu on 16/04/23.
//
#include <iostream>
#include <coroutine>
#include <chrono>
#include <thread>
/*
 In this code, we define a coroutine generator NumberGenerator that produces a sequence of integers. The generator has a promise type that defines the behavior of the coroutine, and a handle type that provides access to the coroutine's state. The generator can be used by a receiver to retrieve the sequence of integers.

 We then define a producer Producer that sends values to the receiver by moving the generator to
 
 
 */
 // Define the coroutine generator that produces integers
class NumberGenerator {
public:
    // Define the coroutine promise type
    struct promise_type {
        NumberGenerator get_return_object() {
            return NumberGenerator{Handle::from_promise(*this)};
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }
        int current_value;
    };

    // Define the coroutine handle type
    using Handle = std::coroutine_handle<promise_type>;

    // Define the constructors and destructors
    NumberGenerator() : coroutine_handle(nullptr) {}
    explicit NumberGenerator(Handle h) : coroutine_handle(h) {}
    NumberGenerator(const NumberGenerator&) = delete;
    NumberGenerator(NumberGenerator&& other) noexcept : coroutine_handle(other.coroutine_handle) {
        other.coroutine_handle = nullptr;
    }
    ~NumberGenerator() {
        if (coroutine_handle)
            coroutine_handle.destroy();
    }

    // Define the operations that the receiver can perform on the generator
    bool move_next() {
        coroutine_handle.resume();
        return !coroutine_handle.done();
    }
    int current_value() const { return coroutine_handle.promise().current_value; }

private:
    // Define the coroutine handle
    Handle coroutine_handle;
};

// Define the producer that sends values to the receiver
class Producer {
public:
    Producer(NumberGenerator& g) : generator(g) {}

    // Define the operation that the producer can perform
    void produce() {
        for (int i = 0; i < 10; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Wait for 100 ms
            generator.move_next();
            std::cout << "Produced value: " << generator.current_value() << std::endl;
        }
    }

private:
    // Define the generator that the producer sends values to
    NumberGenerator& generator;
};

// Define the receiver that receives values from the producer
class Receiver {
public:
    Receiver(NumberGenerator& g) : generator(g) {}

    // Define the operation that the receiver can perform
    void receive() {
        for (int i = 0; i < 10; i++) {
            while (!generator.move_next())
                std::this_thread::yield();
            std::cout << "Received value: " << generator.current_value() << std::endl;
        }
    }

private:
    // Define the generator that the receiver receives values from
    NumberGenerator& generator;
};

int main() {
    // Create the generator
    NumberGenerator generator;

    // Create the producer and receiver
    Producer producer(generator);
    Receiver receiver(generator);

    // Start the producer and receiver in separate threads
    std::thread producer_thread(&Producer::produce, &producer);
    std::thread receiver_thread(&Receiver::receive, &receiver);

    // Wait for the threads to finish
    producer_thread.join();
    receiver_thread.join();

    return 0;
}
