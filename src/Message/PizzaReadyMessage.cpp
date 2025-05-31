/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "PizzaReadyMessage.hpp"

namespace Plazza {
    void PizzaReadyMessage::serialize(std::vector<char>& buffer) const
    {
        buffer.clear();
        buffer.reserve(sizeof(MessageType) + sizeof(PizzaType) + sizeof(PizzaSize) +
                      sizeof(uint32_t) + sizeof(uint32_t));

        MessageType msgType = MessageType::PIZZA_READY;
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&msgType),
                     reinterpret_cast<const char*>(&msgType) + sizeof(MessageType));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_pizzaType),
                     reinterpret_cast<const char*>(&_pizzaType) + sizeof(PizzaType));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_pizzaSize),
                     reinterpret_cast<const char*>(&_pizzaSize) + sizeof(PizzaSize));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_orderId),
                     reinterpret_cast<const char*>(&_orderId) + sizeof(uint32_t));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_cookingTime),
                     reinterpret_cast<const char*>(&_cookingTime) + sizeof(uint32_t));
    }

    void PizzaReadyMessage::deserialize(const std::vector<char>& buffer)
    {
        if (buffer.size() < sizeof(MessageType) + sizeof(PizzaType) + sizeof(PizzaSize) +
                sizeof(uint32_t) + sizeof(uint32_t)) {
            throw std::invalid_argument("Buffer too small for PizzaReadyMessage");
                }

        size_t offset = sizeof(MessageType);
        std::memcpy(&_pizzaType, buffer.data() + offset, sizeof(PizzaType));
        offset += sizeof(PizzaType);
        std::memcpy(&_pizzaSize, buffer.data() + offset, sizeof(PizzaSize));
        offset += sizeof(PizzaSize);
        std::memcpy(&_orderId, buffer.data() + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t);
        std::memcpy(&_cookingTime, buffer.data() + offset, sizeof(uint32_t));
    }

}