//
//  main.cpp
//  17_Coroutine_AllInOne_1
//
//  Created by Sathya Babu on 06/04/23.
//
// https://www.scs.stanford.edu/~dm/blog/c++-coroutines.html

#include <concepts>
//#include <coroutine>
#include <exception>
#include <iostream>

#include <experimental/coroutine>
// experimental::

//  Phase I
/*
 
 
 Roughly speaking, coroutines are functions that can invoke each other but do not share a stack, so can flexibly suspend their execution at any point to enter a different coroutine.
 
 future and promise. These terms have nothing to do with the types std::future and std::promise available in the C++ <future> header
 
 “co_await a;” does the following:

 1.  Ensures all local variables in the current function—which must be a coroutine—are saved to a heap-allocated object.
 2.  Creates a callable object that, when invoked, will resume execution of the coroutine at the point immediately following evaluation of the co_await expression.
 3.  Calls (or more accurately jumps to) a method of co_await’s target object a, passing that method the callable object from step 2.
 
 Note that the method in step 3, when it returns, does not return control to the coroutine. The coroutine only resumes execution if and when the callable from step 2 is invoked.
 
 Compiling using GCC, Clang
 
 g++ -fcoroutines -std=c++20
 Clang’s support is less far along. You need to install llvm libc++ and compile with:

 clang++ -std=c++20 -stdlib=libc++ -fcoroutines-ts
 Unfortunately, with clang you also need to include the coroutine header as <experimental/coroutine> rather than <coroutine>. Moreover, a number of types are named std::experimental::xxx instead of std::xxx. Hence, as of this writing, the examples below won’t compile out-of-the box with clang, but ideally should with a future release.
 
 
 // Lets dig seep in Phase I
 
 Coroutine handles
 As previously mentioned, the new co_await operator ensures the current state of a function is bundled up somewhere on the heap and creates a callable object whose invocation continues execution of the current function. The callable object is of type std::coroutine_handle<>.

 A coroutine handle behaves a lot like a C pointer. It can be easily copied, but it doesn’t have a destructor to free the memory associated with coroutine state. To avoid leaking memory, you must generally destroy coroutine state by calling the coroutine_handle::destroy method
 
 
 Now let’s look more specifically at what co_await does. When you evaluate the expression co_await a, the compiler creates a coroutine handle and passes it to the method a.await_suspend(coroutine_handle).1 The type of a must support certain methods, and is sometimes referred to as an “awaitable” object or an “awaiter.”


 we call counter with a std::coroutine_handle<>*, which we stick into our Awaiter type. In its await_suspend method, this type stores the coroutine handle produced by co_await into main1’s coroutine handle. Each time main1 invokes the coroutine handle, it triggers one more iteration of the loop in counter, which then suspends execution again at the co_await statement.
 
 we store the coroutine handle every time await_suspend is called, but the handle does not change across invocations.
 
 
 The <coroutine> header provides two pre-defined awaiters, std::suspend_always and std::suspend_never. As their names imply,
     suspend_always::await_ready always returns false,
     while suspend_never::await_ready always returns true.

       The other methods on these classes are empty and do nothing.
 
 
 */


struct ReturnObject {
  struct promise_type {
    ReturnObject get_return_object() { return {}; }
    std::experimental::suspend_never initial_suspend() { return {}; }
    std::experimental::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
  };
};

struct Awaiter {
  std::experimental::coroutine_handle<> *hp_;
    
    //await_ready is an optimization. If it returns true, then co_await does not suspend the function.
  constexpr bool await_ready() const noexcept { return false; }// always returns true.
    
    // you could achieve the same effect in await_suspend, by resuming (or not suspending) the current coroutine, but before calling await_suspend, the compiler must bundle all state into the heap object referenced by the coroutine handle, which is potentially expensive.
    
  void await_suspend(std::experimental::coroutine_handle<> h) { *hp_ = h; }
    
    //  await_resume here returns void, but if instead it returned a value, this value would be the value of the co_await expression.
    
  constexpr void await_resume() const noexcept {}
};

ReturnObject
Await_counter(std::experimental::coroutine_handle<> *continuation_out)
{
  Awaiter a{continuation_out};
  for (unsigned i = 0;; ++i) {
    co_await a;
    std::cout << "Await_ counter :" << i << std::endl;
  }
}


//      ***************   Phase II  ***************
/*
 The coroutine return object
 
 R::promise_type must include a method R get_return_object() that returns an instance of the outer type R. The result of get_return_object() is the return value of the coroutine function, in this case counter(). Note that in many discussions of coroutines, the return type R is referred to as a future,
 
 Instead of passing a coroutine_handle<>* into counter, it would be nicer if we could just return the handle from counter(). We can do that if we put the coroutine handle inside the return object. Since promise_type::get_return_object computes the return object, we simply need that method to stick the coroutine handle into the return object. How can we get a coroutine handle from within get_return_object? As it happens, the coroutine state referenced by a coroutine_handle contains an instance of promise_type at a known offset, and so std::coroutine_handle allows us to compute a coroutine handle from the promise object.
 
 
 */
struct ReturnObject2 {
  struct promise_type {
    ReturnObject2 get_return_object() {
      return {
        // Uses C++20 designated initializer syntax
          // following is a static method..  returns the coroutine state!!!
        .h_ = std::experimental::coroutine_handle<promise_type>::from_promise(*this)
      };
    }
    std::experimental::suspend_never initial_suspend() { return {}; }
    std::experimental::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
  };

  std::experimental::coroutine_handle<promise_type> h_;
  operator std::experimental::coroutine_handle<promise_type>() const { return h_; }
  // A coroutine_handle<promise_type> converts to coroutine_handle<>
  operator std::experimental::coroutine_handle<>() const { return h_; }
};

ReturnObject2
counter2()
{
  for (unsigned i = 0;; ++i) {
    co_await std::experimental::suspend_always{};
     std::cout << " Entred  counter2: " << i << std::endl;
      std::cout << "counter2 has some business to deal with..: " << i << std::endl;
  }
}

void coRoutineReturnHandle(){
    std::experimental::coroutine_handle<> h = counter2();
      for (int i = 0; i < 3; ++i) {
          std::cout << "In coRoutineReturnHandle Main I'm busy now.. \n ";
          std::cout << "In coRoutineReturnHandle Main I'm busy now.. \n ";
          std::cout << "In coRoutineReturnHandle Main I'm busy now.. \n";
        h();
      }
      h.destroy();
}
//  ******************  Phase III  Promise  *********************************
// The promise object -
//  It would be great if our counter function, instead of writing to standard output, just returned values to main,


//Since we know the coroutine state includes an instance of promise_type, we can add a field value_ to this type and use that field to transmit values from the coroutine to our main function. How do we get access to the promise type? In the main function, this isn’t too hard. Instead of converting our coroutine handle to a std::coroutine_handle<>, we can keep it as a std::coroutine_handle<ReturnObject3::promise_type>. The method promise() on this coroutine handle will return the promise_type& that we need.


// struct GetPromise -> explained in detail below :

// We thus define a new awaiter type GetPromise that contains a field promise_type *p_. We have its await_suspend method store the address of the promise object in p_, but then return false to avoid actually suspending the coroutine. Until now, we have only seen co_await expressions of type void. This time, we want our co_await to return the address of the promise object, so we also add an await_resume function returning p_.


template<typename PromiseType>
struct GetPromise {
  PromiseType *p_;
  bool await_ready() { return false; } // says yes call await_suspend
  bool await_suspend(std::experimental::coroutine_handle<PromiseType> h) {
    p_ = &h.promise();
    return false;     // says no don't suspend coroutine after all
  }
  PromiseType *await_resume() { return p_; }
};

struct ReturnObject3 {
  struct promise_type {
    unsigned value_;

    ReturnObject3 get_return_object() {
      return ReturnObject3 {
        .h_ = std::experimental::coroutine_handle<promise_type>::from_promise(*this)
      };
    }
    std::experimental::suspend_never initial_suspend() { return {}; }
    std::experimental::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
  };

  std::experimental::coroutine_handle<promise_type> h_;
  operator std::experimental::coroutine_handle<promise_type>() const { return h_; }
};

ReturnObject3
counter3()
{
  auto pp = co_await GetPromise<ReturnObject3::promise_type>{};

  for (unsigned i = 0;; ++i) {
    pp->value_ = i;
    co_await std::experimental::suspend_always{};
  }
}

void
coRoutineReturnHandleGetPromise()
{
  std::experimental::coroutine_handle<ReturnObject3::promise_type> h = counter3();
  ReturnObject3::promise_type &promise = h.promise();
  for (int i = 0; i < 3; ++i) {
    std::cout << "counter3: " << promise.value_ << std::endl;
    h();
  }
  h.destroy();
}

//  ************************* Phase IV co_yeild *************************

struct ReturnObject4 {
  struct promise_type {
    unsigned value_;

    ReturnObject4 get_return_object() {
      return {
        .h_ = std::experimental::coroutine_handle<promise_type>::from_promise(*this)
      };
    }
    std::experimental::suspend_never initial_suspend() { return {}; }
    std::experimental::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
    std::experimental::suspend_always yield_value(unsigned value) {
      value_ = value;
      return {};
    }
  };

  std::experimental::coroutine_handle<promise_type> h_;
};

ReturnObject4
counter4()
{
  for (unsigned i = 0;; ++i)
    co_yield i;       // co yield i => co_await promise.yield_value(i)
}

void
Coroutine_co_yeild()
{
  auto h = counter4().h_;
  auto &promise = h.promise();
  for (int i = 0; i < 3; ++i) {
    std::cout << "counter4: " << promise.value_ << std::endl;
    h();
  }
  h.destroy();
}

//  ************************* Phase IV co_return_Operator *************************

struct ReturnObject5 {
  struct promise_type {
    unsigned value_;

    ~promise_type() {
      std::cout << "promise_type destroyed" << std::endl;
    }
    ReturnObject5 get_return_object() {
      return {
        .h_ = std::experimental::coroutine_handle<promise_type>::from_promise(*this)
      };
    }
    std::experimental::suspend_never initial_suspend() { return {}; }
    std::experimental::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
    std::experimental::suspend_always yield_value(unsigned value) {
      value_ = value;
      return {};
    }
    void return_void() {}
  };

  std::experimental::coroutine_handle<promise_type> h_;
};

ReturnObject5
counter5()
{
  for (unsigned i = 0; i < 3; ++i)
    co_yield i;
  // falling off end of function or co_return; => promise.return_void();
  // (co_return value; => promise.return_value(value);)
}

void
CoReturn_Operator()
{
  auto h = counter5().h_;
  auto &promise = h.promise();
  while (!h.done()) { // Do NOT use while(h) (which checks h non-NULL)
    std::cout << "counter5 Co return Object : " << promise.value_ << std::endl;
    h();
  }
  h.destroy();
}



//  *************************   Phase IV Generic_Generator   *************************


template<typename T>
struct Generator {
  struct promise_type;
  using handle_type = std::experimental::coroutine_handle<promise_type>;

  struct promise_type {
    T value_;
    std::exception_ptr exception_;

    Generator get_return_object() {
      return Generator(handle_type::from_promise(*this));
    }
    std::experimental::suspend_always initial_suspend() { return {}; }
    std::experimental::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() { exception_ = std::current_exception(); }
    template<std::convertible_to<T> From> // C++20 concept
    std::experimental::suspend_always yield_value(From &&from) {
      value_ = std::forward<From>(from);
      return {};
    }
    void return_void() {}
  };

  handle_type h_;

  Generator(handle_type h) : h_(h) {}
  ~Generator() { h_.destroy(); }
  explicit operator bool() {
    fill();
    return !h_.done();
  }
  T operator()() {
    fill();
    full_ = false;
    return std::move(h_.promise().value_);
  }

private:
  bool full_ = false;

  void fill() {
    if (!full_) {
      h_();
      if (h_.promise().exception_)
        std::rethrow_exception(h_.promise().exception_);
      full_ = true;
    }
  }
};

Generator<unsigned>
counter6()
{
  for (unsigned i = 0; i < 3;)
    co_yield i++;
}

void
Generic_Generator()
{
  auto gen = counter6();
  while (gen)
    std::cout << "counter6: Generic_Generator  " << gen() << std::endl;
}
// ***********************************************************************************
int
main()
{
    
    //  Phase I
    
  std::experimental::coroutine_handle<> h;
  Await_counter(&h);
  for (int i = 0; i < 3; ++i) {
    std::cout << "In main1 function\n";
    h();
  }
  h.destroy();
    // Phasse II
    coRoutineReturnHandle();
    // Phasse III
    coRoutineReturnHandleGetPromise();
    // Phasse IV
    Coroutine_co_yeild();
    
    // Phase V
    CoReturn_Operator();
    
    // Phase VI
    
    Generic_Generator();
    
    return 0 ;
}

/*
 Phase I
 
 In main1 function
 counter: Await_ 0
 In main1 function
 counter: Await_ 1
 In main1 function
 counter: Await_ 2
 
 Program ended with exit code: 0
 
 Phase II
 
 In main2 function
 counter2: 0
 In main2 function
 counter2: 1
 In main2 function
 counter2: 2
 Program ended with exit code: 0
 
 
 Phase III
 
 counter3: 0
 counter3: 1
 counter3: 2
 
 
 Phase IV
 
 counter4: 0
 counter4: 1
 counter4: 2
 
 // Phase V
 
 counter5 Co return Object : 0
 counter5 Co return Object : 1
 counter5 Co return Object : 2
 promise_type destroyed
 
 // Phase V
 
 counter6: Generic_Generator  0
 counter6: Generic_Generator  1
 counter6: Generic_Generator  2
 
 
 
 */
