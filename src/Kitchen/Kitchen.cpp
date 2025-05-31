/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include "Message/StatusMessage.hpp"
#include "Message/OrderMessage.hpp"
#include "Message/StatusResponseMessage.hpp"
#include <sys/select.h>
#include <unistd.h>

namespace Plazza {

Kitchen::Kitchen(int numberOfCooks, int timeToRestock, int fd, int multiplier)
{
    _numberOfCooks = numberOfCooks;
    _numberOfPizzas = 0;
    _running = true;
    _timeToRestock = timeToRestock;
    _fd = fd;
    _threadPool = std::make_unique<ThreadPool>(numberOfCooks);
    _multiplier = multiplier;
}

Kitchen::~Kitchen()
{
    if (_running) {
        this->stop();
    }
    _threadPool.reset();
    std::cout << "[Kitchen " << getpid() << "] stopped." << std::endl;
}

void Kitchen::start()
{
    auto startTime = std::chrono::steady_clock::now();
    auto lastRestockTime = startTime;
    auto lastStatusTime = startTime;
    const int STATUS_INTERVAL_MS = 1000;

    std::cout << "[Kitchen PID " << getpid() << "] started with " << _numberOfCooks << " cooks." << std::endl;

    while (_running) {
        auto now = std::chrono::steady_clock::now();

        // Restock ingredients periodically
        auto elapsedRestockMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRestockTime).count();
        if (elapsedRestockMs >= _timeToRestock) {
            _stock.restockAll();
            lastRestockTime = now;
        }

        // Use select to check if data is available on _fd
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(_fd, &readfds);

        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 10000; // 10 ms timeout

        int ret = select(_fd + 1, &readfds, nullptr, nullptr, &timeout);
        if (ret < 0) {
            std::cerr << "select error" << std::endl;
            this->stop();
            break;
        } else if (ret > 0 && FD_ISSET(_fd, &readfds)) {
            // Data available, handle incoming message
            if (!this->handleIncomingMessage()) {
                std::cerr << "Error handling incoming message, shutting down kitchen." << std::endl;
                this->stop();
                break;
            }
        }

        // Periodically send status (if you want to push status unsolicited, else can remove)
        auto elapsedStatusMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastStatusTime).count();
        if (elapsedStatusMs >= STATUS_INTERVAL_MS) {
            // Optional: you may want to send unsolicited status here,
            // but in your design reception sends STATUS_REQUEST to get status,
            // so maybe no need to send periodic status here.
            lastStatusTime = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

bool Kitchen::handleIncomingMessage()
{
    // Read message size first (4 bytes)
    uint32_t size = 0;
    ssize_t bytesRead = read(_fd, &size, sizeof(size));
    if (bytesRead == 0) {
        std::cerr << "Pipe closed, kitchen shutting down." << std::endl;
        return false;
    }
    if (bytesRead != sizeof(size)) {
        std::cerr << "Failed to read message size." << std::endl;
        return false;
    }

    std::vector<char> buffer(size);
    bytesRead = read(_fd, buffer.data(), size);
    if (bytesRead != static_cast<ssize_t>(size)) {
        std::cerr << "Failed to read full message data." << std::endl;
        return false;
    }

    // Determine message type from buffer (need to deserialize)
    // Let's assume we can check type with OrderMessage and StatusRequestMessage

    // Try OrderMessage
    OrderMessage orderMsg;
    try {
        orderMsg.deserialize(buffer);
    } catch (...) {
        // Ignore, maybe it's not an order message
    }

    if (orderMsg.getType() == MessageType::COMMAND) {
        return handleOrder(orderMsg);
    }

    // Try StatusRequest
    // Assume StatusRequestMessage is similar or use message type directly
    // For simplicity, let's just parse message type manually:
    if (!buffer.empty()) {
        MessageType type = static_cast<MessageType>(buffer[0]); // assuming first byte = message type
        if (type == MessageType::STATUS_REQUEST) {
            return sendStatusResponse();
        }
    }

    std::cerr << "Unknown or unsupported message type received." << std::endl;
    return false;
}

    bool Kitchen::handleOrder(const OrderMessage &orderMsg)
{
    auto pizzas = orderMsg.getPizzas();

    for (const auto &pizza : pizzas) {
        if (_numberOfPizzas >= 2 * _numberOfCooks) {
            std::cout << "Kitchen full, cannot accept more pizzas\n";
            return false;
        }
        auto cookTask = std::make_shared<CookTask>(pizza, _multiplier, _stock);
        _threadPool->enqueueTask(cookTask);
        _numberOfPizzas++;
        std::cout << "Pizza added to cooking queue\n";
    }
    return true;
}

bool Kitchen::sendStatusResponse()
{
    StatusResponseMessage statusResponse(MessageType::STATUS_RESPONSE, _numberOfCooks, _numberOfPizzas, _numberOfCooks , _stock.getAll());

}

void Kitchen::stop()
{
    _running = false;
    std::cout << "Kitchen shutting down" << std::endl;
}

} // namespace Plazza
