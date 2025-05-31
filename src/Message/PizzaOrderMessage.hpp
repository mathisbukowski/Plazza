/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PIZZAORDERMESSAGE_HPP
#define PIZZAORDERMESSAGE_HPP

#include <memory>
#include "IMessage.hpp"
#include "Pizza/APizza.hpp"

namespace Plazza {
    class PizzaOrderMessage : public IMessage {
    private:
        std::vector<std::shared_ptr<IPizza>> _pizzas;
        uint32_t _orderId;

    public:
        PizzaOrderMessage(): _pizzas({}), _orderId() {}
        PizzaOrderMessage(std::vector<std::shared_ptr<IPizza>> pizzas, uint32_t orderId)
            : _pizzas(pizzas), _orderId(orderId) {}

        ~PizzaOrderMessage() override = default;

        void serialize(std::vector<char>& buffer) const override;

        void deserialize(const std::vector<char>& buffer) override;

        MessageType getType() const override { return MessageType::PIZZA_ORDER; }

        std::vector<std::shared_ptr<IPizza>> getPizzas() const {return _pizzas;}
        uint32_t getOrderId() const { return _orderId; }
    };
}



#endif //PIZZAORDERMESSAGE_HPP
