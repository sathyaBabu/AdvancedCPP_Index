//
//  main.cpp
//  co3_ThreadFuturePromise
//
//  Created by Sathya Babu on 01/12/21.
//

#include <iostream>
#include <future>
using namespace std;


void ThreadFun( promise<int>& prom){
    // Step 1 ... sleeps blocke for 3 sec then it lets you fetch the value
    //    this_thread::sleep_for(chrono::seconds(3)); // block for 3 sec
    
    // Without step 1 you can fetch the value even before thread gets completed..
    
    this_thread::sleep_for(chrono::seconds(3)); // block for 3 sec
    prom.set_value(393);
    //this_thread::sleep_for(chrono::seconds(3)); // block for 3 sec

}
int main(int argc, const char * argv[]) {
    // insert code here...
    promise<int> myPromise;
    future<int> fut = myPromise.get_future();
    
    cout << " Main..." << endl ;
    thread t1 { ThreadFun, ref(myPromise)};
    
    cout << " Main thread --> " << fut.get() << endl;  // live data ( observer )
    
    
    
    t1.join();
    
    
    return 0;
}


