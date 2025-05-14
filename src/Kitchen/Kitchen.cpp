/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(int numberOfCooks, int timeToRestock)
{
    _numberOfCooks = numberOfCooks;
    _numberOfPizzas = 0;
    _running = true;
    _timeToRestock = timeToRestock;
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

void Plazza::Kitchen::start()
{
    auto startTime = std::chrono::steady_clock::now();

    while (_running) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        auto elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

        if (elapsedTime >= 5)
            this->stop();
        if (elapsedTimeMs >= _timeToRestock)
            _stock.restockAll();
    }
}

void Plazza::Kitchen::stop()
{
    _running = false;
    std::cout << "Kitchen shutting down" << std::endl;
}