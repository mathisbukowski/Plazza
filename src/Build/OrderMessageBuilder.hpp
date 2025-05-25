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
    /**
     * @class OrderMessageBuilder
     * Builder for creating OrderMessage objects.
     * This class provides methods to set the type and pizzas of the order message.
     */
    class OrderMessageBuilder : public IBuilder<OrderMessage> {
    public:
        /**
         * Sets the type of the order message.
         * @param type The type of the message to set.
         * @return Reference to the builder instance for method chaining.
         */
        OrderMessageBuilder& setType(MessageType type);
        /**
         * Sets the pizzas for the order message.
         * @param pizzas A vector of shared pointers to IPizza objects representing the pizzas in the order.
         * @return Reference to the builder instance for method chaining.
         */
        OrderMessageBuilder& setPizzas(const std::vector<std::shared_ptr<IPizza>>& pizzas);
        /**
         * Builds the OrderMessage object with the specified type and pizzas.
         * @return An OrderMessage object with the set properties.
         */
        OrderMessage build() override;

    private:
        MessageType _type = MessageType::UNDEFINED; ///> The type of the order message, default is UNDEFINED.
        std::vector<std::shared_ptr<IPizza>> _pizzas; ///> The pizzas in the order, default is an empty vector.
    };
}

#endif //ORDERMESSAGEBUILDER_HPP
