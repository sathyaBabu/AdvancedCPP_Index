//
//  main.cpp
//  17_Coroutine_Generator_1
//
//  Created by Sathya Babu on 12/04/23.
//  https://www.modernescpp.com/index.php/an-infinite-data-stream-with-coroutines-in-c-20

// infiniteDataStreamComments.cpp
//#include <experimental/coroutine>

/*
 
 Let's analyze the control flow.

 The call getNext() (line 1) triggers the creation of the Generator<int>. First, promise_type (line 2) is created, and the following get_return_object call (line 3) creates the generator (line 4) and stores it in a local variable. The result of this call is returned to the caller when the coroutine is suspended the first time. The initial suspension happens immediately (line 5). Because the member function call initial_suspend returns an Awaitable std::suspend_always (line 6), the control flow continues with the coroutine getNext until the instruction co_yield value (line 7). This call is mapped to the call yield_value(int value) (line 8), and the current value is prepared current_value = value (line 9). The member function yield_value(int value) returns the Awaitable std::suspend_always (line 10). Consequently, the execution of the coroutine pauses, the control flow goes back to the main function, and the for loop starts (line 11). The call gen.getNextValue() (line 12) starts the execution of the coroutine by resuming the coroutine using coro.resume() (line 13). Further, the function getNextValue() returns the current value prepared using the previously invoked member function yield_value(int value) (line 8). Finally, the generated number is displayed in line 14 and the for loop continues. In the end, the generator and the promise are destroyed.

 After this detailed analysis, I want first to modify the control flow.
 
 initial_suspend Never Suspends
 In the program, the member function initial_suspend returns the Awaitable std::suspend_always (line 5). As its name suggests, the Awaitable std::suspends_always causes the coroutine to pause immediately. Let me return std::suspend_never instead of std::suspend_always.

 std::suspend_never initial_suspend() {
     std::cout << "            promise_type::initial_suspend" << '\n';
     return {};
 }
 In this case, the coroutine runs immediately and pauses when the function yield_value (line 8) is invoked. A subsequent call gen.getNextValue() (line 12) resumes the coroutine and triggers the execution of the member function yield_value once more. The start value 10 is ignored, and the coroutine returns 20, 30, and 40.
  
 infiniteDataStreamInitialSuspendSuspendsNever
  
 yield_value Never Suspends
  
 The call triggers the member function (line 8) co_yield value and prepares the current_value (line 9). The function returns the Awaitable std::suspend_always (line 10) and pauses the coroutine. Consequently, a subsequent call gen.getNextValue (line 12) has to resume the coroutine. When I change the return value of the member function yield_value to std::suspend_never, let me see what happens.
  
  
 std::suspend_never yield_value(int value) {
     std::cout << "            promise_type::yield_value" << '\n';
     current_value = value;
     return {};
 }
  
 As you may guess, the while loop (line 1) runs forever, and the coroutine returns nothing.
  
 infiniteDataStreamCommentsYieldValueSuspendsNever
 */
#include <coroutine>
#include <memory>
#include <iostream>

template<typename T>
struct  Generator {
    
    struct  promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    
    Generator(handle_type h): coro(h) {
        std::cout << "        Generator::Generator" << '\n';
    }

    handle_type coro;
    
    ~Generator() {
        std::cout << "        Generator::~Generator" << '\n';
        if ( coro ) coro.destroy();
    }
    Generator(const Generator&) = delete;
    Generator& operator = (const Generator&) = delete;
    Generator(Generator&& oth): coro(oth.coro) {
        oth.coro = nullptr;
    }
    Generator& operator = (Generator&& oth) {
        coro = oth.coro;
        oth.coro = nullptr;
        return *this;
    }
    // line 13). Further, the function getNextValue() returns the current value prepared using the previously invoked member function yield_value(int value)
    T getNextValue() {
        std::cout << "        Generator::getNextValue" << '\n';
        coro.resume();                                                  // (13)
        return coro.promise().current_value;
        //  The result of this call is returned to the caller when the coroutine is suspended the first time. The initial suspension happens immediately (line 5). Because the member function call initial_suspend returns an Awaitable std::suspend_always
    }
    struct promise_type {
        promise_type() {   // (2)  promise_type (line 2) is created,
            std::cout << "            promise_type::promise_type" << '\n';
        }
          
        ~promise_type() {
            std::cout << "            promise_type::~promise_type" << '\n';
        }
        
        std::suspend_always initial_suspend() {                         // (5)
            std::cout << "            promise_type::initial_suspend" << '\n';
            return {};                                                  // (6)
        }
        std::suspend_always final_suspend() noexcept {
            std::cout << "            promise_type::final_suspend" << '\n';
            return {};
        }
        auto get_return_object() {                                       // (3)
            std::cout << "            promise_type::get_return_object" << '\n';
            return Generator{handle_type::from_promise(*this)};          // (4)
        }
      
        //  (line 8), and the current value is prepared current_value = value
        //  ( line 9 ) The member function yield_value(int value) returns the Awaitable std::suspend_always
        
        std::suspend_always yield_value(int value) {                     // (8)
            std::cout << "            promise_type::yield_value" << '\n';
            current_value = value;                                       // (9)
            //  (line 10). Consequently, the execution of the coroutine pauses, the control flow goes back to the main function, and the for loop starts
            return {};                                                   // (10)
        }
        void return_void() {}
        void unhandled_exception() {
            std::exit(1);
        }

        T current_value;
    };

};

Generator<int> getNext(int start = 10, int step = 10) {
    std::cout << "    getNext: start" << '\n';
    auto value = start;
//    for (true) {
    // (line 11). The call gen.getNextValue()
    while (true) {   // (11)
        std::cout << "    getNext: before co_yield" << '\n';
        //  This call is mapped to the call yield_value(int value) -> at (8)
        co_yield value;                                                  // (7)
        std::cout << "    getNext: after co_yield" << '\n';
        value += step;
    }
}

int main() {
  
    // The call getNext() (line 1) triggers the creation of the Generator<int>. First,
    auto gen = getNext();                                                // (1)
    for (int i = 0; i <= 2; ++i) {
        
        // (line 12) starts the execution of the coroutine by resuming the coroutine using coro.resume()
        
        // The Coroutine is Not Resumed when we comment following two lines
    //        When I disable the coroutine (gen.getNextValue() ) and the display of its value , the coroutine immediately pauses.
        
        auto val = gen.getNextValue();   //  coro.resume();  coroutine is not called  (12)
        // the generated number is displayed
        std::cout << "main: " << val << '\n';                            // (14)
        /*
         When we comment line 134 and 135 following line we will get to see..
         
         promise_type::promise_type
         promise_type::get_return_object
     Generator::Generator
         promise_type::initial_suspend
     Generator::~Generator
         promise_type::~promise_type
         */
    }
    
} // In the end, the generator and the promise are destroyed.
/*
 promise_type::promise_type
 promise_type::get_return_object
Generator::Generator
 promise_type::initial_suspend
Generator::getNextValue
getNext: start
getNext: before co_yield
 promise_type::yield_value
main: 10
Generator::getNextValue
getNext: after co_yield
getNext: before co_yield
 promise_type::yield_value
main: 20
Generator::getNextValue
getNext: after co_yield
getNext: before co_yield
 promise_type::yield_value
main: 30
Generator::~Generator
 promise_type::~promise_type
Program ended with exit code: 0
 
 
 */
