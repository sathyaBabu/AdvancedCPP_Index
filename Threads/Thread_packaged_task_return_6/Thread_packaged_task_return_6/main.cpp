//
//  main.cpp
//  Thread_packaged_task_return_6
//
//  Created by Sathya Babu on 07/08/23.
//
/*
 
 
 Meaning for the following line :
 
 std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<Func>
 
 This line of code is creating a std::shared_ptr to a std::packaged_task that encapsulates a callable object. This is often used in conjunction with a thread pool or asynchronous tasks to manage the execution of functions asynchronously.

 Let's break down the components:

 std::make_shared<std::packaged_task<ReturnType()>>: This part creates a std::shared_ptr to a std::packaged_task specialized for a function returning ReturnType.

 std::bind(std::forward<Func>(func), std::forward<Args>(args)...): This part creates a std::function that binds the provided callable func with the given arguments args.

 auto task = ...: The whole expression combines the above two steps to create a std::shared_ptr to a std::packaged_task that wraps the callable object and its arguments.

 In other words, this line creates a task that can be executed asynchronously. The std::packaged_task encapsulates the callable object (function or function object) along with its arguments. This task can be scheduled to run in a thread or asynchronously, and its result can be obtained later if needed.

 Here's a simplified example of how this can be used:
 
 In this example, the make_task function creates a packaged task with a callable function that adds two numbers. The task is then executed in a detached thread, and the result is obtained using the std::future. Please note that this is a simplified example, and in real scenarios, you might want to manage threads and tasks more carefully.




 */
 #include <iostream>
 #include <functional>
 #include <future>
 #include <memory>

 template <typename Func, typename... Args>
 auto make_task(Func&& func, Args&&... args) {
     using ReturnType = std::invoke_result_t<Func, Args...>;
     auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
     return task;
 }

 int main() {
     auto task = make_task([](int a, int b) { return a + b; }, 10, 20);

     std::future<int> result = task->get_future();

     std::thread([task]() {
         (*task)();
     }).detach();

     std::cout << "Result: " << result.get() << std::endl;

     return 0;
 }
 


 
 
