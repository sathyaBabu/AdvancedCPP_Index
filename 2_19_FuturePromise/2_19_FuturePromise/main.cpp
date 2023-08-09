//
//  main.cpp
//  2_19_FuturePromise
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include <future>
using namespace std;

void ThreadFun( promise<int>&& prom , int x , int y ){
    
    this_thread::sleep_for(chrono::seconds ( 3 )) ;
    
    prom.set_value( x + y );
    
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    
    int a = 10 ;
    int b = 20 ;
    promise< int > myPromise ;
    future< int >  fut = myPromise.get_future();
    
    std::thread t1 { ThreadFun, std::move( myPromise) ,a,b };
    cout << " result " << fut.get();
    
    t1.join();
    
    return 0;
}
// result 30
