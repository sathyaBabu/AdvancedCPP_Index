//
//  main.cpp
//  17_CoroutineAsyncFLOW_1
//
//  Created by Sathya Babu on 23/03/23.
//
/*
#include <iostream>
#include <experimental/coroutine>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

class AsyncStream {
public:
  AsyncStream() : data_{} {}
  
  // Awaitable type that will be used to wait for the next value in the stream
  struct awaiter {
    AsyncStream& stream_;
    bool ready_;
    int value_;
    
    awaiter(AsyncStream& stream) : stream_{stream}, ready_{false} {}
    
    bool await_ready() {
      return stream_.data_.size() > 0;
    }
    
    void await_suspend(std::experimental::coroutine_handle<> handle) {
      // Start a new thread to generate the next value in the stream
      std::thread([this, handle]() {
        std::this_thread::sleep_for(1s);
        value_ = stream_.data_.back();
        stream_.data_.pop_back();
        ready_ = true;
       // handle.resume();
      }).detach();
    }
    
    int await_resume() {
      return value_;
    }
  };
  
  // Producer method that will be used to add values to the stream
  void add(int value) {
    data_.push_back(value);
  }
  
  // Coroutine type that will be used to iterate over the stream
  struct iterator {
    AsyncStream& stream_;
    
    std::experimental::coroutine_handle<> coro_;
    
    bool operator!=(std::default_sentinel_t) const {
      return !coro_.done();
    }
    
    iterator& operator++() {
      coro_.resume();
      return *this;
    }
    
    awaiter operator*() {
      return awaiter{stream_};
    }
  };
  
  iterator begin() {
    return iterator{*this, std::experimental::coroutine_handle<>::from_address(nullptr)};
  }
  
  std::default_sentinel_t end() {
    return std::default_sentinel;
  }
  
private:
  std::vector<int> data_;
};

int main() {
  AsyncStream stream;
  stream.add(1);
  stream.add(2);
  stream.add(3);
  
  for co_await(auto value : stream) {
    std::cout << "Received value: " << value << std::endl;
  }
  
  return 0;
}

*/
/*
#include <iostream>
#include <experimental/coroutine>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

class AsyncStream {
public:
  AsyncStream() : data_{} {}
  
  // Awaitable type that will be used to wait for the next value in the stream
  struct awaiter {
    AsyncStream& stream_;
    bool ready_;
    int value_;
    
    awaiter(AsyncStream& stream) : stream_{stream}, ready_{false} {}
    
    bool await_ready() {
      return stream_.data_.size() > 0;
    }
    
    void await_suspend(std::experimental::coroutine_handle<> handle) {
      // Start a new thread to generate the next value in the stream
      std::thread([this, handle]() {
        std::this_thread::sleep_for(1s);
        value_ = stream_.data_.back();
        stream_.data_.pop_back();
        ready_ = true;
        handle.resume();
      }).detach();
    }
    
    int await_resume() {
      return value_;
    }
  };
  
  // Producer method that will be used to add values to the stream
  void add(int value) {
    data_.push_back(value);
  }
  
  // Coroutine type that will be used to iterate over the stream
  struct iterator {
    AsyncStream& stream_;
    
    std::experimental::coroutine_handle<> coro_;
    
    bool operator!=(std::default_sentinel_t) const {
      return !coro_.done();
    }
    
    iterator& operator++() {
      coro_.resume();
      return *this;
    }
    
    awaiter operator*() {
      return awaiter{stream_};
    }
  };
  
  iterator begin() {
    return iterator{*this, std::experimental::coroutine_handle<>::from_address(nullptr)};
  }
  
  std::default_sentinel_t end() {
    return std::default_sentinel;
  }
  
private:
  std::vector<int> data_;
};

// Coroutine function that will consume the asynchronous stream
std::experimental::coroutine_handle<> consumeStream(AsyncStream& stream) {
  for co_await(auto value : stream) {
    std::cout << "Received value: " << value << std::endl;
  }
  co_return;
}

int main() {
  AsyncStream stream;
  stream.add(1);
  stream.add(2);
  stream.add(3);
  
  auto handle = consumeStream(stream);
  handle.resume();
  while(!handle.done()) {
    // Do other work here
  }
  
  return 0;
}

*/
#include <iostream>
#include <experimental/coroutine>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

class AsyncStream {
public:
  AsyncStream() : data_{} {}
  
  // Awaitable type that will be used to wait for the next value in the stream
  struct awaiter {
    AsyncStream& stream_;
    bool ready_;
    int value_;
    
    awaiter(AsyncStream& stream) : stream_{stream}, ready_{false} {}
    
    bool await_ready() {
      return stream_.data_.size() > 0;
    }
    
    void await_suspend(std::experimental::coroutine_handle<> handle) {
      // Start a new thread to generate the next value in the stream
      std::thread([this, handle]() {
        std::this_thread::sleep_for(1s);
        value_ = stream_.data_.back();
        stream_.data_.pop_back();
        ready_ = true;
        handle.resume();
      }).detach();
    }
    
    int await_resume() {
      return value_;
    }
  };
  
  // Producer method that will be used to add values to the stream
  void add(int value) {
    data_.push_back(value);
  }
  
  // Coroutine type that will be used to iterate over the stream
  struct iterator {
    AsyncStream& stream_;
    
    std::experimental::coroutine_handle<> coro_;
    
    bool operator!=(std::default_sentinel_t) const {
      return !coro_.done();
    }
    
    iterator& operator++() {
      coro_.resume();
      return *this;
    }
    
    awaiter operator*() {
      return awaiter{stream_};
    }
  };
  
  iterator begin() {
    return iterator{*this, std::experimental::coroutine_handle<>::from_address(nullptr)};
  }
  
  std::default_sentinel_t end() {
    return std::default_sentinel;
  }
  
private:
  std::vector<int> data_;
};

// Coroutine function that will consume the asynchronous stream
std::experimental::coroutine_handle<> consumeStream(AsyncStream& stream) {
  for co_await(auto value : stream) {
    std::cout << "Received value: " << value << std::endl;
  }
  co_return;
}

int main() {
  AsyncStream stream;
  stream.add(1);
  stream.add(2);
  stream.add(3);
  
  auto handle = consumeStream(stream);
  handle.resume();
  while(!handle.done()) {
    // Do other work here
  }
  
  return 0;
}

