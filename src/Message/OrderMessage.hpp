/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef ORDERMESSAGE_HPP
#define ORDERMESSAGE_HPP
#include <memory>
#include <vector>
#include "Pizza/IPizza.hpp"
#include "IMessage.hpp"


namespace Plazza {
    /**
     * @class OrderMessage
     * Class representing an order message in the Plazza system.
     */
    class OrderMessage : public IMessage {
    public:
        /**
         * Default constructor for OrderMessage.
         */
        explicit OrderMessage(uint8_t type): _type(type) {}
        /**
         * Destructor for OrderMessage.
         */
        ~OrderMessage() override = default;
        /**
         * Serializes the OrderMessage into a buffer.
         * @param buffer The buffer to serialize the message into
         * This method converts the message type and pizzas into a binary format for transmission.
         */
        void serialize(std::string& buffer) const override;
        /**
         * Deserializes the OrderMessage from a buffer.
         * @param buffer The buffer to deserialize the message from
         * This method reconstructs the message type and pizzas from the binary format.
         */
        void deserialize(const std::string& buffer) override;
        /**
         * Gets the pizzas in the order message.
         * @return A vector of shared pointers to the pizzas in the message
         */
        [[nodiscard]] std::vector<std::shared_ptr<IPizza>> getPizzas() const { return _pizzas; }
        /**
         * Gets the type of the order message.
         * @return The type of the message
         */
        [[nodiscard]] uint8_t getType() const override { return _type; }

        std::vector<std::shared_ptr<IPizza>> _pizzas; ///> The pizzas in the order message
        uint8_t _type; ///> The type of the order message
    };
}



#endif //ORDERMESSAGE_HPP
