//
//  main.cpp
//  Thread_ConditonLockGuard_myCash_4
//
//  Created by Sathya Babu on 07/08/23.
// https://www.youtube.com/watch?v=zUy66Bats5c

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

std::mutex mtx;
std::condition_variable condition;
double balance = 0 ;

void addCash( int cash ) {
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate some work
    {
        std::lock_guard<std::mutex> lock(mtx);
        balance += cash ;
        std::cout << " Cash added to the bank balance : " << balance << std::endl;
    }
    condition.notify_one(); // Notify waiting thread
}

// 1/4th ms keeps calling
void withDrawCash(int cash ) {
    std::unique_lock<std::mutex> lock(mtx);
   
    condition.wait(lock, [] {
        
                                cout << " waiting for lock to open .."<< endl;
        
                                return  (balance !=0  ) ? true : false ;
        
                             }
                   ); // Wait until data is ready
    
    if( balance > cash )
    {
        balance -= cash ;
        std::cout << "cash withdrawn  : " << cash << std::endl;
        
    }else {
        balance -= cash ;
        std::cout << "Requested cash is less than the balance.  " << cash << std::endl;
    }
    
    
    std::cout << "current balance is : " << balance << std::endl;
}

int main() {
    std::thread t2(withDrawCash, 500);
    std::thread t1(addCash, 900 );
  

    t1.     join();
    t2.     join();

    return 0;
}
/*
 waiting for notification to deliver..
 Cash added to the bank balance : 900
 waiting for notification to deliver..
cash withdrawn  : 500
current balance is : 400
Program ended with exit code: 0
 */
