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
    class ThreadPool {
        public:
            explicit ThreadPool(size_t threadCount);
            ~ThreadPool();

            void enqueueTask(std::shared_ptr<ICookTask> task);
            void stop();
        private:
            void workerLoop();

            std::vector<std::thread> _workers;
            std::queue<std::function<void()>> _tasks;
            std::mutex _queueMutex;
            std::condition_variable _condition;
            std::atomic<bool> _stop;
    };
}

#endif //THREADPOOL_HPP
