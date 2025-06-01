/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"
#include "Logger/Logger.hpp"
#include <mutex>

namespace Plazza {

    ThreadPool::ThreadPool(std::size_t threadCount) : _stop(false) {
        for (std::size_t i = 0; i < threadCount; ++i)
            _workers.emplace_back(&ThreadPool::workerLoop, this);
        LOG_DEBUG("ThreadPool", "ThreadPool created with " + std::to_string(threadCount) + " threads");
    }

    ThreadPool::~ThreadPool()
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _stop = true;
        _condition.notify_all();
        for (auto &worker : _workers) {
            if (worker.joinable())
                worker.join();
        }
        LOG_DEBUG("ThreadPool", "ThreadPool destroyed");
    }

    void ThreadPool::enqueueTask(std::shared_ptr<ICookTask> task) {
        {
            std::lock_guard<std::mutex> lock(_queueMutex);
            _tasks.push([task]() {
                task->execute();
            });
        }
        _condition.notify_one();
        LOG_DEBUG("ThreadPool", "Task enqueued");
    }

    void ThreadPool::workerLoop() {
        LOG_DEBUG("ThreadPool", "Worker thread started");
        while (!_stop) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(_queueMutex);
                _condition.wait(lock, [this] { return _stop || !_tasks.empty(); });
                if (_stop) {
                    LOG_DEBUG("ThreadPool", "Worker thread stopping");
                    return;
                }
                task = _tasks.front();
                _tasks.pop();
            }
            task();
        }
    }

}
