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
    void OrderMessage::serialize(std::vector<char>& buffer) const
    {
        size_t totalSize = this->getPackedSize();
        buffer.resize(totalSize);

        char *new_ptr = buffer.data();
        std::memcpy(new_ptr, &_type, sizeof(MessageType));
        new_ptr += sizeof(MessageType);
        size_t count = _pizzas.size();
        std::memcpy(new_ptr, &count, sizeof(size_t));
        new_ptr += sizeof(size_t);
        for (const auto& pizza : _pizzas) {
            PizzaType type = pizza->getType();
            PizzaSize size = pizza->getSize();

            std::memcpy(new_ptr, &type, sizeof(PizzaType));
            new_ptr += sizeof(PizzaType);
            std::memcpy(new_ptr, &size, sizeof(PizzaSize));
            new_ptr += sizeof(PizzaSize);
        }
    }

    void OrderMessage::deserialize(const std::vector<char>& buffer)
    {
        const char *new_ptr = buffer.data();

        std::memcpy(&_type, new_ptr, sizeof(MessageType));
        new_ptr += sizeof(MessageType);
        size_t count;
        std::memcpy(&count, new_ptr, sizeof(size_t));
        new_ptr += sizeof(size_t);
        _pizzas.clear();
        for (size_t i = 0; i < count; i++) {
            PizzaType type;
            PizzaSize size;
            std::memcpy(&type, new_ptr, sizeof(PizzaType));
            new_ptr += sizeof(PizzaType);
            std::memcpy(&size, new_ptr, sizeof(PizzaSize));
            new_ptr += sizeof(PizzaSize);
            _pizzas.push_back(PizzaFactory::createPizza(type, size));
        }
    }

    size_t OrderMessage::getPackedSize() const
    {
        return sizeof(MessageType) + sizeof(size_t) + _pizzas.size() * (sizeof(PizzaType) + sizeof(PizzaSize));
    }


}
