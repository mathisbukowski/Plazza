/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef ORDERMESSAGEBUILDER_HPP
#define ORDERMESSAGEBUILDER_HPP

#include "IBuilder.hpp"
#include "Message/OrderMessage.hpp"

namespace Plazza {
    class OrderMessageBuilder : public IBuilder<OrderMessage> {
    public:
        OrderMessageBuilder& setType(MessageType type);

        OrderMessageBuilder& setPizzas(const std::vector<std::shared_ptr<IPizza>>& pizzas);

        OrderMessage build() override;

    private:
        MessageType _type = MessageType::UNDEFINED;
        std::vector<std::shared_ptr<IPizza>> _pizzas;
    };
}

#endif //ORDERMESSAGEBUILDER_HPP
