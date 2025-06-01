/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include "Message/StatusMessage.hpp"
#include "Message/OrderMessage.hpp"
#include "Tools/Tools.hpp"
#include "Logger/Logger.hpp"

Plazza::Kitchen::Kitchen(int numberOfCooks, int timeToRestock, int fd, int multiplier)
{
    _numberOfCooks = numberOfCooks;
    _numberOfPizzas = 0;
    _running = true;
    _timeToRestock = timeToRestock;
    _fd = fd;
    _threadPool = std::make_unique<ThreadPool>(numberOfCooks);
    _multiplier = multiplier;
}

Plazza::Kitchen::Kitchen(const Plazza::Kitchen &other)
{
    _numberOfCooks = other._numberOfCooks;
    _numberOfPizzas = other._numberOfPizzas;
    _running = other._running;
    _timeToRestock = other._timeToRestock;
}

Plazza::Kitchen::~Kitchen()
{
    if (_running) {
        this->stop();
    }
    _threadPool.reset();
    LOG_INFO("Kitchen", "Kitchen " + std::to_string(Tools::toolGetPid()) + " stopped.");
}

bool Plazza::Kitchen::handleOrder()
{
    uint32_t size = 0;
    ssize_t bytesRead = Tools::toolRead(_fd, &size, sizeof(size));
    if (bytesRead != sizeof(size))
        return false;
    std::vector<char> buffer(size);
    bytesRead = Tools::toolRead(_fd, buffer.data(), size);
    if (bytesRead != static_cast<ssize_t>(size))
        return false;
    OrderMessage msg;
    msg.deserialize(buffer);
    auto pizzas = msg.getPizzas();

    for (const auto & pizza : pizzas) {
        if (_numberOfPizzas >= 2 * _numberOfCooks) {
            LOG_WARNING("Kitchen", "Kitchen full, cannot accept more pizzas");
            return false;
        }
        auto cookTask = std::make_shared<CookTask>(pizza, _multiplier, _stock);
        _threadPool->enqueueTask(cookTask);
        _numberOfPizzas++;
        LOG_INFO("Kitchen", "Pizza added to cooking queue");
    }
    return true;
}

void Plazza::Kitchen::start()
{
    auto startTime = std::chrono::steady_clock::now();
    auto lastStatusTime = startTime;
    auto lastRestockTime = startTime;

    const int STATUS_INTERVAL_MS = 1000;

    LOG_INFO("Kitchen", "Kitchen PID " + std::to_string(getpid()) + " started with " + std::to_string(_numberOfCooks) + " cooks.");

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
                LOG_ERROR("Kitchen", "Failed to send status.");
                this->stop();
            }
            lastStatusTime = now;
        }
        if (this->handleOrder())
            this->stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


void Plazza::Kitchen::stop()
{
    _running = false;
    LOG_INFO("Kitchen", "Kitchen shutting down");
}

bool Plazza::Kitchen::handleStatus()
{
    StatusMessage statusMessage;
    statusMessage.setType(MessageType::STATUS);
    statusMessage._totalCooks = _numberOfCooks;
    statusMessage._busyCooks = _numberOfPizzas;
    statusMessage.setStock(_stock.getAll());
    std::vector<char> buffer;
    statusMessage.serialize(buffer);
    uint32_t size = buffer.size();
    ssize_t bytesWritten = write(_fd, &size, sizeof(size));
    if (bytesWritten != sizeof(size))
        return false;
    bytesWritten = write(_fd, buffer.data(), size);
    if (bytesWritten != static_cast<ssize_t>(size))
        return false;
    return true;
}