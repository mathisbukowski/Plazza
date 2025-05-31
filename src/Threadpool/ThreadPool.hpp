/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** ThreadPool
*/

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include "ICookTask.hpp"

namespace Plazza {
    /**
     * @class ThreadPool
     * Class representing a thread pool for executing cooking tasks concurrently.
     * It manages a pool of worker threads that can execute tasks in parallel.
     */
    class ThreadPool {
        public:
            /**
             * Constructor for ThreadPool.
             * Initializes the thread pool with a specified number of threads.
             * @param threadCount The number of threads in the pool
             */
            explicit ThreadPool(size_t threadCount);
            /**
             * Destructor for ThreadPool.
             * Cleans up the thread pool and stops all worker threads.
             */
            ~ThreadPool();
            /**
             * Enqueues a cooking task to be executed by the thread pool.
             * @param task A shared pointer to the cooking task to be executed
             */
            void enqueueTask(std::shared_ptr<ICookTask> task);
            int getActiveTasks();
        private:
            /**
             * Worker loop function for each thread in the pool.
             * It continuously waits for tasks to be enqueued and executes them.
             */
            void workerLoop();

            std::vector<std::thread> _workers; ///> Vector of worker threads in the pool
            std::queue<std::function<void()>> _tasks; ///> Queue of tasks to be executed by the workers
            std::mutex _queueMutex; ///> Mutex to protect access to the task queue
            std::condition_variable _condition; ///> Condition variable to notify workers when tasks are available
            std::atomic<bool> _stop; ///> Atomic flag to indicate whether the thread pool is stopping
    };
}

#endif //THREADPOOL_HPP
