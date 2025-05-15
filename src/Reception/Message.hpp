/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>
#include <string>
#include <cstring>
#include <cstddef>
#include "../Pizza/PizzaType.hpp"

namespace Plazza {

    /**
     * @class MessageType
     * Enum class representing the different types of messages that can be sent and received.
     */
    enum class MessageType {
        UNDEFINED, ///> Undefined message type
        COMMAND, ///> Order/Command message type
        STATUS_REQUEST, ///> Status request message type
        STATUS_RESPONSE, ///> Status response message type
        PIZZA_READY, ///> Pizza ready message type
        KITCHEN_FULL, ///> Kitchen full message type
        KITCHEN_CLOSING ///> Kitchen closing message type
    };

    /**
     * @class Message
     * Base class for all messages.
     * This class provides a common interface for all message types.
     */
    class Message {
        public:
            /**
             * Constructor to initialize a message with a specific type.
             * @param type The type of the message
             */
            explicit Message(MessageType type = MessageType::UNDEFINED) : _type(type) {}
            /**
             * Destructor for the Message class.
             */
            virtual ~Message() = default;

            /**
             * Get the type of the message.
             * @return The type of the message
             */
            MessageType getType() const { return _type; }

            /**
             * Serialize the message into a buffer.
             * @param buffer The buffer to serialize the message into
             * @param size The size of the buffer
             */
            virtual void serialize(const std::string& buffer, size_t& size) const = 0;
            /**
             * Deserialize the message from a buffer.
             * @param buffer The buffer to deserialize the message from
             * @param size The size of the buffer
             */
            virtual void deserialize(const std::string& buffer, size_t size) = 0;
            /**
             * Get the packed size of the message.
             * @return The packed size of the message
             */
            virtual size_t getPackedSize() const = 0;

        protected:
            MessageType _type; ///> Type of the message
    };


    /**
     * @class OrderMessage
     * Class representing an order message.
     * This class contains the details of the pizzas ordered.
     */
    class OrderMessage : public Message {
    public:
        /**
         * Constructor to initialize an order message with a specific type.
         * @param type The type of the message
         */
        OrderMessage() : Message(MessageType::COMMAND) {}
        /**
         * Constructor to initialize an order message with a list of pizzas.
         * @param pizzas The list of pizzas ordered
         */
        explicit OrderMessage(const std::vector<Pizza>& pizzas) : Message(MessageType::COMMAND), _pizzas(pizzas) {}

        /**
         * Get the list of pizzas ordered.
         * @return The list of pizzas ordered
         */
        const std::vector<Pizza>& getPizzas() const { return _pizzas; }
        /**
         * Set the list of pizzas ordered.
         * @param pizzas The list of pizzas ordered
         */
        void setPizzas(const std::vector<Pizza>& pizzas) { _pizzas = pizzas; }
        /**
         * Serialize the order message into a buffer.
         * @param buffer The buffer to serialize the message into
         * @param size The size of the buffer
         */
        void serialize(const std::string& buffer, size_t& size) const override;
        /**
         * Deserialize the order message from a buffer.
         * @param buffer The buffer to deserialize the message from
         * @param size The size of the buffer
         */
        void deserialize(const std::string& buffer, size_t size) override;
        /**
         * Get the packed size of the order message.
         * @return The packed size of the order message
         */
        size_t getPackedSize() const override;

    private:
        std::vector<Pizza> _pizzas; ///> List of pizzas ordered
    };

    /**
     * @class StatusMessage
     * Class representing a status message.
     * This class contains the status of the kitchen.
     */
    class StatusMessage : public Message {
    public:
        /**
         * Constructor to initialize a status message with a specific type.
         * @param type The type of the message
         */
        StatusMessage() : Message(MessageType::STATUS_RESPONSE), _active(0), _total(0), _queued(0) {}
        /**
         * Constructor to initialize a status message with the number of active cooks, total cooks, and queued pizzas.
         * @param active The number of active cooks
         * @param total The total number of cooks
         * @param queued The number of queued pizzas
         */
        StatusMessage(int active, int total, int queued)
            : Message(MessageType::STATUS_RESPONSE), _active(active), _total(total), _queued(queued) {}

        /**
         * Get the number of active cooks.
         * @return The number of active cooks
         */
        int getActiveCooks() const { return _active; }
        /**
         * Get the total number of cooks.
         * @return The total number of cooks
         */
        int getTotalCooks() const { return _total; }
        /**
         * Get the number of queued pizzas.
         * @return The number of queued pizzas
         */
        int getQueuedPizzas() const { return _queued; }

        /**
         * Serialize the status message into a buffer.
         * @param buffer The buffer to serialize the message into
         * @param size The size of the buffer
         */
        void serialize(const std::string& buffer, size_t& size) const override;
        /**
         * Deserialize the status message from a buffer.
         * @param buffer The buffer to deserialize the message from
         * @param size The size of the buffer
         */
        void deserialize(const std::string& buffer, size_t size) override;
        /**
         * Get the packed size of the status message.
         * @return The packed size of the status message
         */
        size_t getPackedSize() const override { return sizeof(MessageType) + 3 * sizeof(int); }

    private:
        int _active; ///> Number of active cooks
        int _total; ///> Total number of cooks
        int _queued; ///> Number of queued pizzas
    };

    /**
     * @class NotificationMessage
     * Class representing a notification message.
     * This class contains a notification message.
     */
    class NotificationMessage : public Message {
    public:
        /**
         * Constructor to initialize a notification message with a specific type.
         * @param type The type of the message
         */
        NotificationMessage() : Message(MessageType::UNDEFINED) {}
        /**
         * Constructor to initialize a notification message with a specific type and message.
         * @param type The type of the message
         * @param msg The notification message
         */
        NotificationMessage(MessageType type, const std::string& msg)
            : Message(type), _message(msg) {}

        /**
         * Get the notification message.
         * @return The notification message
         */
        const std::string& getMessage() const { return _message; }
        /**
         * Set the notification message.
         * @param msg The notification message
         */
        void setMessage(const std::string& msg) { _message = msg; }
        /**
         * Serialize the notification message into a buffer.
         * @param buffer The buffer to serialize the message into
         * @param size The size of the buffer
         */
        void serialize(const std::string& buffer, size_t& size) const override;
        /**
         * Deserialize the notification message from a buffer.
         * @param buffer The buffer to deserialize the message from
         * @param size The size of the buffer
         */
        void deserialize(const std::string& buffer, size_t size) override;
        /**
         * Get the packed size of the notification message.
         * @return The packed size of the notification message
         */
        size_t getPackedSize() const override { return sizeof(MessageType) + sizeof(size_t) + _message.size(); }

    private:
        std::string _message; ///> Notification message
    };

}

#endif //MESSAGE_HPP
