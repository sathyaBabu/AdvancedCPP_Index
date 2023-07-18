//
//  main.cpp
//  17_ThreadLockUnlock_1
//
//  Created by Sathya Babu on 28/02/23.
//

// unique_lock::lock/unlock
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock, std::defer_lock

std::mutex mtx;           // mutex for critical section

void print_thread_id (int id) {
  std::unique_lock<std::mutex> lck (mtx,std::defer_lock);
  // critical section (exclusive access to std::cout signaled by locking lck):
  lck.lock();   // Explicitly acquire the lock
    std::cout << "thread #" << id << '\n';
    
    ///************* For the sake of it
   
    
    for (int i = 0; i < 5; ++i) {
            std::cout << i << " ";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << std::endl;
   
    
    ///**************************
    
    
    
     // lck.unlock();  // not required
     // lock is automatically released when it goes out of scope
}

int main ()
{
  std::thread threads[10];
    // spawn 10 threads:
    // automic will solve the problem of racing..
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_thread_id,i+1);

  for (auto& th : threads) th.join();
    
  return 0;
}
/*
 thread #1
 0 1 2 3 4
 thread #2
 0 1 2 3 4
 thread #3
 0 1 2 3 4
 thread #7
 0 1 2 3 4
 thread #5
 0 1 2 3 4
 thread #8
 0 1 2 3 4
 thread #9
 0 1 2 3 4
 thread #4
 0 1 2 3 4
 thread #10
 0 1 2 3 4
 thread #6
 0 1 2 3 4
 Program ended with exit code: 0
 */
