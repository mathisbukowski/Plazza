/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PIZZAREADYMESSAGE_HPP
#define PIZZAREADYMESSAGE_HPP

#include "IMessage.hpp"

namespace Plazza {
    class PizzaReadyMessage : public IMessage {
    private:
        PizzaType _pizzaType;
        PizzaSize _pizzaSize;
        uint32_t _orderId;
        uint32_t _cookingTime;

    public:
        PizzaReadyMessage(): _pizzaType(PizzaType::Margarita), _pizzaSize(PizzaSize::S), _orderId(0), _cookingTime(0) {}
        PizzaReadyMessage(PizzaType type, PizzaSize size, uint32_t orderId, uint32_t cookingTime)
            : _pizzaType(type), _pizzaSize(size), _orderId(orderId), _cookingTime(cookingTime) {}

        ~PizzaReadyMessage() override = default;

        void serialize(std::vector<char>& buffer) const override;

        void deserialize(const std::vector<char>& buffer) override;

        MessageType getType() const override { return MessageType::PIZZA_READY; }

        PizzaType getPizzaType() const { return _pizzaType; }
        PizzaSize getPizzaSize() const { return _pizzaSize; }
        uint32_t getOrderId() const { return _orderId; }
        uint32_t getCookingTime() const { return _cookingTime; }
    };
}



#endif //PIZZAREADYMESSAGE_HPP
