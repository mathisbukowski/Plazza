/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include "Message/StatusMessage.hpp"
#include "Message/OrderMessage.hpp"
#include "Message/NotificationMessage.hpp"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

Plazza::Kitchen::Kitchen(int numberOfCooks, int timeToRestock, int fd, int multiplier)
{
    _numberOfCooks = numberOfCooks;
    _numberOfPizzas = 0;
    _running = true;
    _timeToRestock = timeToRestock;
    _fd = fd;
    _threadPool = std::make_unique<ThreadPool>(numberOfCooks);
    _multiplier = multiplier;

    int flags = fcntl(_fd, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "Failed to get file descriptor flags\n";
    } else if (fcntl(_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "Failed to set file descriptor to non-blocking\n";
    }
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
    std::cout << "[Kitchen " << getpid() << "] stopped." << std::endl;
}

bool Plazza::Kitchen::handleOrder()
{
    uint32_t size = 0;
    ssize_t bytesRead = read(_fd, &size, sizeof(size));
    if (bytesRead == 0) {
        return false;
    }
    if (bytesRead != sizeof(size)) {
        if (bytesRead == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            return false;
        }
        std::cerr << "Failed to read message size\n";
        return false;
    }

    std::vector<char> buffer(size);
    bytesRead = read(_fd, buffer.data(), size);
    if (bytesRead != static_cast<ssize_t>(size)) {
        std::cerr << "Failed to read complete message\n";
        return false;
    }
    
    OrderMessage msg;
    msg.deserialize(buffer);
    
    if (msg.getType() == MessageType::STATUS) {
        return this->handleStatus();
    }

    auto pizzas = msg.getPizzas();
    bool ordersProcessed = false;
    for (const auto & pizza : pizzas) {
        if (_numberOfPizzas >= 2 * _numberOfCooks) {
            std::cout << "Kitchen full, cannot accept more pizzas\n";
            break;
        }
        auto cookTask = std::make_shared<CookTask>(pizza, _multiplier, _stock, [this, pizza]() {
            _numberOfPizzas--;
            NotificationMessage readyMsg(MessageType::PIZZA_READY, 
                "Pizza ready: type " + std::to_string(static_cast<int>(pizza->getType())) + 
                " size " + std::to_string(static_cast<int>(pizza->getSize())));
            std::vector<char> buffer;
            readyMsg.serialize(buffer);
            uint32_t size = buffer.size();
            write(_fd, &size, sizeof(size));
            write(_fd, buffer.data(), size);
        });
        _threadPool->enqueueTask(cookTask);
        _numberOfPizzas++;
        ordersProcessed = true;
        std::cout << "Pizza added to cooking queue\n";
    }
    return ordersProcessed;
}

void Plazza::Kitchen::start()
{
    auto startTime = std::chrono::steady_clock::now();
    auto lastRestockTime = startTime;
    auto lastActivityTime = startTime;

    std::cout << "[Kitchen PID " << getpid() << "] started with " << _numberOfCooks << " cooks." << std::endl;

    while (_running) {
        auto now = std::chrono::steady_clock::now();

        auto elapsedTimeSec = std::chrono::duration_cast<std::chrono::seconds>(now - lastActivityTime).count();
        if (elapsedTimeSec >= 5 && _numberOfPizzas == 0)
            this->stop();

        auto elapsedRestockMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRestockTime).count();
        if (elapsedRestockMs >= _timeToRestock) {
            _stock.restockAll();
            lastRestockTime = now;
        }
        if (handleOrder()) {
            lastActivityTime = now;
        }
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
