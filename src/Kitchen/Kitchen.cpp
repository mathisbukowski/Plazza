/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include "Message/KitchenClosingMessage.hpp"
#include "Message/StatusMessage.hpp"
#include "Message/OrderMessage.hpp"
#include "Message/ReceiveStatusMessage.hpp"
#include "Tools/Pipe.hpp"

Plazza::Kitchen::Kitchen(int numberOfCooks, int timeToRestock, int readFd, int writeFd, double multiplier, int kitchenId)
{
    _numberOfCooks = numberOfCooks;
    _numberOfPizzas = 0;
    _running = true;
    _timeToRestock = timeToRestock;
    _readFd = readFd;
    _writeFd = writeFd;
    _threadPool = std::make_unique<ThreadPool>(numberOfCooks);
    _multiplier = multiplier;
    _kitchenId = kitchenId;
}

Plazza::Kitchen::Kitchen(const Kitchen &other)
{
    _numberOfCooks = other._numberOfCooks;
    _numberOfPizzas = other._numberOfPizzas;
    _running = other._running;
    _timeToRestock = other._timeToRestock;
    _readFd = other._readFd;
    _writeFd = other._writeFd;
    _threadPool = std::make_unique<ThreadPool>(_numberOfCooks);
    _multiplier = other._multiplier;
    _kitchenId = other._kitchenId;
}

Plazza::Kitchen::~Kitchen()
{
}

bool Plazza::Kitchen::handleOrder()
{
    auto message = PipeChannel::receive(_readFd);

    if (!message)
        return false;

    switch (message->getType()) {
    case static_cast<uint8_t>(MessageType::ORDER): {
            auto orderMsg = std::dynamic_pointer_cast<OrderMessage>(message);
            if (!orderMsg)
                return false;
            for (const auto & pizza : orderMsg->getPizzas()) {
                if (_numberOfPizzas >= 2 * _numberOfCooks) {
                    std::cout << "Kitchen full, cannot accept more pizzas\n";
                    return false;
                }
                std::cout << "Pizza: " << "Size=" << static_cast<int>(pizza->getSize()) << "Type=" << static_cast<int>(pizza->getType()) << std::endl;
                auto cookTask = std::make_shared<CookTask>(pizza, _multiplier, _stock);
                _threadPool->enqueueTask(cookTask);
                _numberOfPizzas++;
                std::cout << "Pizza added to cooking queue\n";
            }
            break;
    }
    case static_cast<uint8_t>(MessageType::RECEIVE_STATUS):
            return this->handleStatus();
    default:
        std::cerr << "[Kitchen] Unknown message type received." << std::endl;
        return false;
    }
    return true;
}

void Plazza::Kitchen::start()
{
    auto startTime = std::chrono::steady_clock::now();
    auto lastRestockTime = startTime;

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
        if (!handleOrder())
            this->stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


void Plazza::Kitchen::stop()
{
    _running = false;
    std::cout << "Kitchen shutting down" << std::endl;
    KitchenClosing msg(static_cast<uint8_t>(MessageType::KITCHEN_CLOSING));
    PipeChannel::send(_writeFd, msg);
}

bool Plazza::Kitchen::handleStatus() 
{
    ReceiveStatusMessage message(static_cast<uint8_t>(MessageType::RECEIVE_STATUS));
    message._totalCooks = _numberOfCooks;
    message._busyCooks = _numberOfPizzas;
    message._stock = _stock.getAll();

    return PipeChannel::send(_writeFd, message);
}