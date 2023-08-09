//
//  main.cpp
//  THreadPolShowPending_Cancel_2
//
//  Created by Sathya Babu on 07/08/23.
//
#include <iostream>
#include <functional>
#include <queue>
#include <map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <future>

enum class TaskStatus { Pending, Completed, Canceled };

class ThreadPool {
private:
    std::mutex queueMutex;
    std::condition_variable condition;
    std::queue<std::packaged_task<void()>> tasks;
    std::map<int, TaskStatus> taskStatus;
    std::vector<std::thread> workers;
    bool running = true;

public:
   // ThreadPool(size_t numThreads) {
    ThreadPool(size_t numThreads = std::thread::hardware_concurrency()) {
         
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::packaged_task<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return !tasks.empty() || !running; });
                        if (!running && tasks.empty()) {
                            return;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        std::packaged_task<decltype(f(args...))()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<decltype(f(args...))> res = task.get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(std::move(task));
        }
        condition.notify_one();
        return res;
    }

//    TaskStatus getTaskStatus(int taskId) const {
////        error:
////        No matching constructor for initialization of 'std::unique_lock<std::mutex>'
//        std::unique_lock<std::mutex> lock(queueMutex);
//        auto it = taskStatus.find(taskId);
//        if (it != taskStatus.end()) {
//            return it->second;
//        }
//        return TaskStatus::Pending;
//    }

    TaskStatus getTaskStatus(int taskId) {
            std::lock_guard<std::mutex> lock(queueMutex);

        auto it = taskStatus.find(taskId);
        if (it != taskStatus.end()) {
                return it->second;
            }
            return TaskStatus::Pending;
        }
    void pause() {
        running = false;
        condition.notify_all();
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    void resume() {
        running = true;
        for (size_t i = 0; i < workers.size(); ++i) {
            workers[i] = std::thread([this] {
                while (true) {
                    std::packaged_task<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return !tasks.empty() || running; });
                        if (!running && tasks.empty()) {
                            return;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        if (running) {
            pause();
        }
    }
};

// Example usage
void longRunningTask(int taskId, int duration) {
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    std::cout << "Task " << taskId << " completed" << std::endl;
}

int main() {
    ThreadPool pool(4);

    std::vector<std::future<void>> futures;
    for (int i = 1; i <= 10; ++i) {
        futures.push_back(pool.enqueue(longRunningTask, i, 2));
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Pause the thread pool
    pool.pause();

    // Check the status of tasks
    for (int i = 1; i <= 10; ++i) {
            TaskStatus status = pool.getTaskStatus(i);
            std::cout << "Task " << i << " Status: ";
            switch (status) {
                case TaskStatus::Pending:
                    std::cout << "Pending";
                    break;
                case TaskStatus::Completed:
                    std::cout << "Completed";
                    break;
                case TaskStatus::Canceled:
                    std::cout << "Canceled";
                    break;
            }
            std::cout << std::endl;
        }

    // Resume the thread pool
    pool.resume();

    // Wait for the remaining tasks to complete
    for (const auto& future : futures) {
        future.wait();
    }

    return 0;
}
