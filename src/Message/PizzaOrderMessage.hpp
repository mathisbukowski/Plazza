/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PIZZAORDERMESSAGE_HPP
#define PIZZAORDERMESSAGE_HPP

#include "IMessage.hpp"

namespace Plazza {
    class PizzaOrderMessage : public IMessage {
    private:
        PizzaType _pizzaType;
        PizzaSize _pizzaSize;
        uint32_t _orderId;

    public:
        PizzaOrderMessage(): _pizzaType(), _pizzaSize(), _orderId() {}
        PizzaOrderMessage(PizzaType type, PizzaSize size, uint32_t orderId)
            : _pizzaType(type), _pizzaSize(size), _orderId(orderId) {}

        ~PizzaOrderMessage() override = default;

        void serialize(std::vector<char>& buffer) const override;

        void deserialize(const std::vector<char>& buffer) override;

        MessageType getType() const override { return MessageType::PIZZA_ORDER; }

        PizzaType getPizzaType() const { return _pizzaType; }
        PizzaSize getPizzaSize() const { return _pizzaSize; }
        uint32_t getOrderId() const { return _orderId; }
    };
}



#endif //PIZZAORDERMESSAGE_HPP
