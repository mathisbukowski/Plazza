/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "OrderMessage.hpp"

#include <cstring>

#include "Factory/PizzaFactory.hpp"

namespace Plazza {
    void OrderMessage::serialize(std::string& buffer) const
    {
        std::string tmp;
        uint32_t pizzaCount = static_cast<uint32_t>(_pizzas.size());

        const std::size_t totalSize = sizeof(_type) + sizeof(pizzaCount) + (_pizzas.size() * (sizeof(PizzaType) + sizeof(PizzaSize)));
        buffer.resize(totalSize);

        std::size_t offset = 0;

        std::memcpy(&buffer[offset], &_type, sizeof(_type));
        offset += sizeof(_type);

        std::memcpy(&buffer[offset], &pizzaCount, sizeof(pizzaCount));
        offset += sizeof(pizzaCount);

        for (const auto& pizza : _pizzas) {
            PizzaType type = pizza->getType();
            PizzaSize size = pizza->getSize();
            std::memcpy(&buffer[offset], &type, sizeof(type));
            offset += sizeof(type);
            std::memcpy(&buffer[offset], &size, sizeof(size));
            offset += sizeof(size);
        }
    }

    void OrderMessage::deserialize(const std::string& buffer)
    {
        std::size_t offset = 0;
        uint32_t pizzaCount = 0;

        if (buffer.size() < sizeof(_type) + sizeof(pizzaCount)) {
            throw std::runtime_error("Buffer too small for OrderMessage");
        }

        std::memcpy(&_type, &buffer[offset], sizeof(_type));
        offset += sizeof(_type);

        std::memcpy(&pizzaCount, &buffer[offset], sizeof(pizzaCount));
        offset += sizeof(pizzaCount);

        const std::size_t expectedSize = sizeof(_type) + sizeof(pizzaCount) + pizzaCount * (sizeof(PizzaType) + sizeof(PizzaSize));
        if (buffer.size() != expectedSize) {
            throw std::runtime_error("Invalid buffer size for OrderMessage");
        }

        _pizzas.clear();
        for (uint32_t i = 0; i < pizzaCount; ++i) {
            PizzaType type;
            PizzaSize size;
            std::memcpy(&type, &buffer[offset], sizeof(type));
            offset += sizeof(type);
            std::memcpy(&size, &buffer[offset], sizeof(size));
            offset += sizeof(size);
            _pizzas.push_back(PizzaFactory::createPizza(type, size)); // 🍕 Crée la pizza via la factory
        }
    }
}
