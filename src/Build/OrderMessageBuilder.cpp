/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "OrderMessageBuilder.hpp"

namespace Plazza {
    OrderMessageBuilder& OrderMessageBuilder::setType(MessageType type)
    {
        _type = type;
        return *this;
    }

    OrderMessageBuilder& OrderMessageBuilder::setPizzas(const std::vector<std::shared_ptr<IPizza>>& pizzas)
    {
        _pizzas = pizzas;
        return *this;
    }

    OrderMessage OrderMessageBuilder::build()
    {
        OrderMessage message;
        message.setType(_type);
        message.setPizzas(_pizzas);
        return message;
    }
}