/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include "Message/StatusMessage.hpp"
#include "Message/OrderMessage.hpp"

Plazza::Kitchen::Kitchen(int numberOfCooks, int timeToRestock, int fd, int multiplier, int kitchenId)
{
    _numberOfCooks = numberOfCooks;
    _numberOfPizzas = 0;
    _running = true;
    _timeToRestock = timeToRestock;
    _fd = fd;
    _threadPool = std::make_unique<ThreadPool>(numberOfCooks);
    _multiplier = multiplier;
    _kitchenId = kitchenId;
}

Plazza::Kitchen::Kitchen(const Plazza::Kitchen &other)
{
    _numberOfCooks = other._numberOfCooks;
    _numberOfPizzas = other._numberOfPizzas;
    _running = other._running;
    _timeToRestock = other._timeToRestock;
    _fd = other._fd;
    _threadPool = std::make_unique<ThreadPool>(_numberOfCooks);
    _multiplier = other._multiplier;
    _kitchenId = other._kitchenId;
}

Plazza::Kitchen::~Kitchen()
{
}

bool Plazza::Kitchen::handleOrder()
{
    return true;
}

void Plazza::Kitchen::start()
{
    auto startTime = std::chrono::steady_clock::now();
    auto lastStatusTime = startTime;
    auto lastRestockTime = startTime;

    const int STATUS_INTERVAL_MS = 1000;

    std::cout << "[Kitchen PID " << getpid() << "] started with " << _numberOfCooks << " cooks." << std::endl;

    while (_running) {
        auto now = std::chrono::steady_clock::now();

        auto elapsedTimeSec = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
        if (elapsedTimeSec >= 5)
            this->stop();

        auto elapsedRestockMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRestockTime).count();
        if (elapsedRestockMs >= _timeToRestock) {
            _stock.restockAll();
            lastRestockTime = now;
        }
        auto elapsedStatusMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastStatusTime).count();
        if (elapsedStatusMs >= STATUS_INTERVAL_MS) {
            if (!this->handleStatus()) {
                std::cerr << "Failed to send status." << std::endl;
                this->stop();
            }
            lastStatusTime = now;
        }
        if (handleOrder())
            this->stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


void Plazza::Kitchen::stop()
{
    _running = false;
    std::cout << "Kitchen shutting down" << std::endl;
}

bool Plazza::Kitchen::handleStatus() 
{
    return true;
}