/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

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

bool Plazza::Kitchen::handleOrder()
{
    uint32_t size = 0;
    ssize_t bytesRead = read(_fd, &size, sizeof(size));
    if (bytesRead != sizeof(size)) {
        std::cerr << "Failed to read size\n";
        return true;
    }

    std::vector<char> buffer(size);
    bytesRead = read(_fd, buffer.data(), size);
    if (bytesRead != static_cast<ssize_t>(size)) {
        std::cerr << "Failed to read full message\n";
        return true;
    }

    OrderMessage msg;
    msg.deserialize(buffer);
    auto pizzas = msg.getPizzas();
    for (auto pizza : pizzas) {
        std::cout << "Pizza " << static_cast<int>(pizza->getType()) << "Size : " << static_cast<int>(pizza->getSize()) << std::endl;
    }
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
    }
}

void Plazza::Kitchen::stop()
{
    _running = false;
    std::cout << "Kitchen shutting down" << std::endl;
}