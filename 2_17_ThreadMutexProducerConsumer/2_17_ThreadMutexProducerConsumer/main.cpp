//
//  main.cpp
//  2_17_ThreadMutexProducerConsumer
//
//  Created by Sathya Babu on 02/08/23.
//



#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

std::mutex g_mutex;
bool g_ready = false;
int  g_data = 0;

int produceData() {
  int randomNumber = rand() % 1000;
  std::cout << "produce data: " << randomNumber << "\n";
  return randomNumber;
}

void consumeData(int data) { std::cout << "receive data: " << data << "\n"; }

void consumer() {
    
    while( true ) {
        while( !g_ready){
            std::this_thread::sleep_for( std::chrono::seconds( 3 ));
        }
        std::unique_lock<std::mutex> ul( g_mutex);
        consumeData( g_data );
        g_ready = false ;
        ul.unlock();
    }
    
}

void producer()
{
    while( true ){
        std::unique_lock<std::mutex> ul( g_mutex);
        g_data = produceData();
        g_ready = true ;
        ul.unlock();
        while( g_ready){
            std::this_thread::sleep_for( std::chrono::seconds( 1 ));
        }
    }
}

void consumerThread() { consumer() ; }
void producerThread() { producer(); }


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::thread t1( consumerThread  );
    std::thread t2( producerThread  );
    
    t1.join();
    t2.join();
    
    return 0;
}
