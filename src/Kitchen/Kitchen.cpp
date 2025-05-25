/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include "Message/StatusMessage.hpp"
#include "Message/OrderMessage.hpp"

Plazza::Kitchen::Kitchen(int numberOfCooks, int timeToRestock, int fd)
{
    _numberOfCooks = numberOfCooks;
    _numberOfPizzas = 0;
    _running = true;
    _timeToRestock = timeToRestock;
    _fd = fd;
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
}

bool Plazza::Kitchen::handleOrder(const std::vector<char>& buffer)
{
    uint32_t size = 0;
    ssize_t bytesRead = read(_fd, &size, sizeof(size));
    if (bytesRead != sizeof(size))
        return true;
    std::vector<char> buffer(size);
    bytesRead = read(_fd, buffer.data(), size);
    if (bytesRead != static_cast<ssize_t>(size))
        return true;
    OrderMessage msg;
    msg.deserialize(buffer);
    auto pizzas = msg.getPizzas();
    return false;
}

void Plazza::Kitchen::start()
{
    auto startTime = std::chrono::steady_clock::now();

    std::cout << "[Kitchen PID " << getpid() << "] started with " << _numberOfCooks << " cooks." << std::endl;
    while (_running) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        auto elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

        if (elapsedTime >= 5)
            this->stop();
        if (elapsedTimeMs >= _timeToRestock)
            _stock.restockAll();
        if (this->handleOrder())
            this->stop();
        if (!this->handleStatus()) {
            std::cerr << "Failed to handle status" << std::endl;
        }
    }
}

void Plazza::Kitchen::stop()
{
    _running = false;
    std::cout << "Kitchen shutting down" << std::endl;
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