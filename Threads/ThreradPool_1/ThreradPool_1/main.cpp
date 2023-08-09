//
//  main.cpp
//  ThreradPool_1
//
//  Created by Sathya Babu on 07/08/23.
//
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>
#include <type_traits>
#include <map> // Needed for keeping track of tasks and their IDs
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
 In this example, the make_task function creates a packaged task with a callable function that adds two numbers. The task is then executed in a detached thread, and the result is obtained using the std::future. Please note that this is a simplified example, and in real scenarios, you might want to manage threads and tasks more carefully.






 
 */
class ThreadPool {
public:
    ThreadPool(size_t numThreads) : running(true) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (running) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return !running || !taskQueue.empty(); });
                        if (!running && taskQueue.empty()) {
                            return;
                        }
                        task = std::move(taskQueue.front());
                        taskQueue.pop();
                    }
                    task();
                }
            });
        }
    }

    template<typename Func, typename... Args>
    auto enqueue(Func&& func, Args&&... args) -> std::future<std::invoke_result_t<Func, Args...>> {
        using ReturnType = std::invoke_result_t<Func, Args...>;
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        std::future<ReturnType> future = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            taskQueue.emplace([task] { (*task)(); });
            // Save the future associated with the task ID
            int taskId = taskIDCounter++;
            taskFutures[taskId] = std::move(future);
        }
        condition.notify_one();
        return future;
    }

    void terminateTask(int taskId) {
        std::unique_lock<std::mutex> lock(queueMutex);
        auto it = taskFutures.find(taskId);
        if (it != taskFutures.end()) {
            it->second.wait(); // Wait for the task to finish before erasing
            taskFutures.erase(it);
        }
        
        std::cout << std::endl << taskId << " Completed and terminated the task... " << std::endl;
    }

    void stop() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            running = false;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic_bool running;
    std::map<int, std::future<void>> taskFutures;
    int taskIDCounter = 0;
};

// Example long-running task with argument
void longRunningTask(int taskId) {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Task " << taskId << " running, step " << i + 1 << std::endl;
    }
}

int main() {
    ThreadPool threadPool(4);

    // Enqueue some long-running tasks with arguments
    for (int i = 1; i <= 10; ++i) {
        threadPool.enqueue(longRunningTask, i);
    }

    // Wait for a while to see the tasks running
    std::this_thread::sleep_for(std::chrono::seconds(6));

    // Terminate task with ID 3
    threadPool.terminateTask(3);

    // Pause for a moment to let the tasks complete
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Stop the thread pool and wait for all tasks to finish
    threadPool.stop();

    return 0;
}
/*
 Task 1 running, step Task Task 1Task
 4 running, step 1
 2 running, step 1
 3 running, step 1
 Task 1 running, step 2
 Task 2 running, step 2
 Task 3 running, step 2
 Task 4 running, step 2
 Task 1 running, step Task Task 4 running, step 3
 Task 3 running, step 3
 3
 2 running, step 3
 Task 1 running, step 4
 Task 4 running, step 4Task 2 running, step 4

 Task 3 running, step 4
 Task 3 running, step 5
 Task Task 12 running, step 5
  running, step 5
 Task 4 running, step 5

 3 Completed and terminated the task...
 Task 7 running, step 1
 Task 5 running, step 1
 Task 6 running, step 1
 Task 8 running, step 1
 Task 7 running, step 2
 Task 5 running, step 2
 Task 6 running, step 2
 Task 8 running, step 2
 Task 7 running, step 3
 Task 5 running, step 3
 Task 6 running, step 3
 Task 8 running, step 3
 Task 5 running, step 4
 Task 7 running, step 4
 Task 6 running, step 4
 Task 8 running, step 4
 Task 7 running, step 5
 Task 5 running, step 5
 Task 6 running, step 5
 Task 8 running, step 5
 Task 9 running, step 1
 Task 10 running, step 1
 Task 9 running, step 2
 Task 10 running, step 2
 Task 9 running, step 3
 Task 10 running, step 3
 Task 9 running, step 4
 Task 10 running, step 4
 Task 9 running, step 5
 Task 10 running, step 5
 Program ended with exit code: 0
 */
