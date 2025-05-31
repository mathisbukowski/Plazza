/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include "Message/StatusMessage.hpp"
#include "Message/OrderMessage.hpp"

Plazza::Kitchen::Kitchen(int numberOfCooks, int timeToRestock, std::shared_ptr<PipeChannel> pipe, int multiplier)
{
    _numberOfCooks = numberOfCooks;
    _numberOfPizzas = 0;
    _running = true;
    _timeToRestock = timeToRestock;
    _pipe = pipe;
    _threadPool = std::make_unique<ThreadPool>(numberOfCooks);
    _multiplier = multiplier;
}

Plazza::Kitchen::Kitchen(const Plazza::Kitchen &other)
{
    _numberOfCooks = other._numberOfCooks;
    _numberOfPizzas = other._numberOfPizzas;
    _running = other._running;
    _timeToRestock = other._timeToRestock;
    _pipe = other._pipe;
    _multiplier = other._multiplier;
}

Plazza::Kitchen::~Kitchen()
{
    if (_running) {
        this->stop();
    }
    _threadPool.reset();
    std::cout << "[Kitchen " << getpid() << "] stopped." << std::endl;
}

bool Plazza::Kitchen::handleOrder()
{
    try {
        auto msg = _pipe->receive<OrderMessage>(_pipe->getReadFd());
        if (!msg) {
            return false;
        }
        if (msg->getType() == MessageType::STATUS) {
            return this->handleStatusRequest();
        } else if (msg->getType() == MessageType::COMMAND) {
            auto pizzas = msg->getPizzas();
            for (const auto& pizza : pizzas) {
                if (_numberOfPizzas >= 2 * _numberOfCooks) {
                    std::cout << "Kitchen full, cannot accept more pizzas\n";
                    return false;
                }
                auto cookTask = std::make_shared<CookTask>(pizza, _multiplier, _stock);
                _threadPool->enqueueTask(cookTask);
                _numberOfPizzas++;
                std::cout << "Pizza added to cooking queue\n";
            }
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error handling order: " << e.what() << std::endl;
        return false;
    }
}

void Plazza::Kitchen::start()
{
    auto startTime = std::chrono::steady_clock::now();
    auto lastActivityTime = startTime;
    auto lastRestockTime = startTime;

    const int ACTIVITY_TIMEOUT_SEC = 5;

    std::cout << "[Kitchen PID " << getpid() << "] started with " << _numberOfCooks << " cooks." << std::endl;

    while (_running) {
        auto now = std::chrono::steady_clock::now();
        bool hasActivity = this->handleOrder();
        if (hasActivity) {
            lastActivityTime = now;
        }
        auto elapsedInactivitySec = std::chrono::duration_cast<std::chrono::seconds>(now - lastActivityTime).count();
        if (elapsedInactivitySec >= ACTIVITY_TIMEOUT_SEC) {
            std::cout << "[Kitchen] No activity for " << ACTIVITY_TIMEOUT_SEC << " seconds, shutting down." << std::endl;
            this->stop();
            break;
        }
        auto elapsedRestockMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRestockTime).count();
        if (elapsedRestockMs >= _timeToRestock) {
            _stock.restockAll();
            lastRestockTime = now;
        }
        _numberOfPizzas = _threadPool->getActiveTasks();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


void Plazza::Kitchen::stop()
{
    _running = false;
    std::cout << "Kitchen shutting down" << std::endl;
}

bool Plazza::Kitchen::handleStatusRequest()
{
    try {
        StatusMessage statusMessage;
        statusMessage.setType(MessageType::STATUS);
        statusMessage.setTotalCooks(_numberOfCooks);
        statusMessage.setBusyCooks(_numberOfPizzas);
        statusMessage.setStock(_stock.getAll());
        _pipe->send(_pipe->getWriteFd(), statusMessage);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to send status: " << e.what() << std::endl;
        return false;
    }
}

bool Plazza::Kitchen::handleStatus()
{
    return this->handleStatusRequest();
}