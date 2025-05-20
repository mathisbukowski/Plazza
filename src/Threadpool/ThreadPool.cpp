/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"
#include <mutex>
#include <functional>

namespace Plazza {

    ThreadPool::ThreadPool(size_t threadCount) : _stop(false) {
        for (size_t i = 0; i < threadCount; ++i)
            _workers.emplace_back(&ThreadPool::workerLoop, this);
    }

    ThreadPool::~ThreadPool() {
        stop();
        for (auto &worker : _workers) {
            if (worker.joinable())
                worker.join();
        }
    }

    void ThreadPool::stop() {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _stop = true;
        _condition.notify_all();
    }

    void ThreadPool::enqueueTask(std::shared_ptr<ICookTask> task) {
        {
            std::lock_guard<std::mutex> lock(_queueMutex);
            _tasks.push([task]() {
                task->execute();
            });
        }
        _condition.notify_one();
    }

    void ThreadPool::workerLoop() {
        while (!_stop) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(_queueMutex);
                _condition.wait(lock, [this] { return _stop || !_tasks.empty(); });
                if (_stop)
                    return;
                task = _tasks.front();
                _tasks.pop();
            }
            task();
        }
    }

}
