/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "StatusResponseMessage.hpp"


namespace Plazza {
    void StatusResponseMessage::serialize(std::vector<char>& buffer) const
    {

        buffer.clear();
        buffer.reserve(sizeof(MessageType) + 4 * sizeof(uint32_t) + STOCK_SIZE * sizeof(int));

        MessageType msgType = MessageType::STATUS_RESPONSE;
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&msgType),
                     reinterpret_cast<const char*>(&msgType) + sizeof(MessageType));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_activeCooks),
                     reinterpret_cast<const char*>(&_activeCooks) + sizeof(uint32_t));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_totalCooks),
                     reinterpret_cast<const char*>(&_totalCooks) + sizeof(uint32_t));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_pizzasInQueue),
                     reinterpret_cast<const char*>(&_pizzasInQueue) + sizeof(uint32_t));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_maxPizzasCapacity),
                     reinterpret_cast<const char*>(&_maxPizzasCapacity) + sizeof(uint32_t));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(_stock.data()),
                     reinterpret_cast<const char*>(_stock.data()) + STOCK_SIZE * sizeof(int));

    }

    void StatusResponseMessage::deserialize(const std::vector<char>& buffer)
    {
        if (buffer.size() < sizeof(MessageType) + 4 * sizeof(uint32_t) + STOCK_SIZE * sizeof(int)) {
            throw std::invalid_argument("Buffer too small for StatusResponseMessage");
        }

        size_t offset = sizeof(MessageType);
        std::memcpy(&_activeCooks, buffer.data() + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t);
        std::memcpy(&_totalCooks, buffer.data() + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t);
        std::memcpy(&_pizzasInQueue, buffer.data() + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t);
        std::memcpy(&_maxPizzasCapacity, buffer.data() + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t);
        std::memcpy(_stock.data(), buffer.data() + offset, STOCK_SIZE * sizeof(int));
    }

}