//
//  main.cpp
//  17_Coroutine_1
// reffer to 17_Coroutine_Basic_1 for error correction
//  Created by Sathya Babu on 18/03/23.
//

#include <iostream>
//#include <coroutine>
#include <experimental/coroutine>
#include <iostream>


// Coroutine generator that yields a sequence of numbers
class NumberGenerator {
public:
  // Coroutine promise type
  class promise_type {
  public:
    promise_type() {}
    ~promise_type() {}

    // Coroutine suspend point
    auto initial_suspend() { return std::experimental::suspend_always{}; }
    auto final_suspend() noexcept { return std::experimental::suspend_always{}; }

    // Coroutine return value
    auto get_return_object() { return NumberGenerator{this}; }
    void return_void() {}

    // Coroutine yield value
    auto yield_value(int value) {
      m_value = value;
      return std::experimental::suspend_always{};
    }

    // Coroutine exception handling
    void unhandled_exception() { std::terminate(); }

    int current_value() const { return m_value; }

  private:
    int m_value;
  };


  // Coroutine handle
  using handle_type = std::experimental::coroutine_handle<promise_type>;

  NumberGenerator() : m_coroutine(nullptr) {}
  NumberGenerator(promise_type* promise) : m_coroutine(handle_type::from_promise(*promise)) {}
  ~NumberGenerator() {
    if (m_coroutine) {
      m_coroutine.destroy();
    }
  }

  // Coroutine iteration
  void next() {
      //m_coroutine.resume();
      
     // std::cout << "m_coroutine = " << m_coroutine.address() << std::endl;
      // std::experimental::coroutines_v1::coroutine_handle<void>::resume()
          m_coroutine.resume();
  }
  bool done() const { return m_coroutine.done(); }
  int value() const { return m_coroutine.promise().current_value(); }

private:
  handle_type m_coroutine;
};

// Coroutine usage
int main() {
    
    NumberGenerator::promise_type promise;
    NumberGenerator generator = promise.get_return_object();

    
 // NumberGenerator generator{};

  for (int i = 0; i < 5; ++i) {
    generator.next();
    std::cout << generator.value() << std::endl;
  }

  return 0;
}
