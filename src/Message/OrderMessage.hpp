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
         * Initializes the message type to UNDEFINED.
         */
        OrderMessage() = default;
        /**
         * Destructor for OrderMessage.
         */
        ~OrderMessage() = default;
        /**
         * Serializes the OrderMessage into a buffer.
         * @param buffer The buffer to serialize the message into
         * This method converts the message type and pizzas into a binary format for transmission.
         */
        void serialize(std::vector<char>& buffer) const override;
        /**
         * Deserializes the OrderMessage from a buffer.
         * @param buffer The buffer to deserialize the message from
         * This method reconstructs the message type and pizzas from the binary format.
         */
        void deserialize(const std::vector<char>& buffer) override;
        /**
         * Gets the packed size of the OrderMessage.
         * @return The size of the serialized message in bytes
         */
        size_t getPackedSize() const override;
        /**
         * Sets the type of the order message.
         * @param type The type of the message
         */
        void setType(const MessageType& type) { _type = type; }
        /**
         * Sets the pizzas in the order message.
         * @param pizzas The pizzas to set in the message
         */
        void setPizzas(const std::vector<std::shared_ptr<IPizza>> pizzas) { _pizzas = pizzas; }
        /**
         * Gets the pizzas in the order message.
         * @return A vector of shared pointers to the pizzas in the message
         */
        std::vector<std::shared_ptr<IPizza>> getPizzas() const { return _pizzas; }
        /**
         * Gets the type of the order message.
         * @return The type of the message
         */
        MessageType getType() const { return _type; }

        std::vector<std::shared_ptr<IPizza>> _pizzas; ///> The pizzas in the order message
        MessageType _type; ///> The type of the order message
    };
}



#endif //ORDERMESSAGE_HPP
