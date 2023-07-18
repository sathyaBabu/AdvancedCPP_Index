//
//  main.cpp
//  co3_ThreadFuturePAckagesTask
//
//  Created by Sathya Babu on 01/12/21.
//

#include <iostream>
#include <thread>
#include <future>
int main() {

// we use extra std::packaged_task, which can be used to wrap any target that can be called
 //for asynchronous calls.

    std::packaged_task<int()> task(   [](){return 7;}   );
    
// get the future of task
        std::future<int> result = task.get_future();  // super seeds mutex wait
        std::thread(std::move(task)).detach();   // thread is not waiting for the result..

        std::cout << "waiting...";
        result.wait(); // block until future has arrived
        // output result
        std::cout << "done!" << std:: endl << "future result is " << result.get() << std::endl; return 0;
}
