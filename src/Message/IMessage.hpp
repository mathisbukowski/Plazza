/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef IMESSAGE_HPP
#define IMESSAGE_HPP
#include <string>

namespace Plazza {
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
         */
        virtual void serialize(std::vector<char>& buffer) const = 0;
        /**
         * Deserialize the message from a buffer.
         * @param buffer The buffer to deserialize the message from
         */
        virtual void deserialize(const std::vector<char>& buffer) = 0;
        /**
         * Get the packed size of the message.
         * @return The packed size of the message
         */
        virtual size_t getPackedSize() const = 0;

    protected:
        MessageType _type; ///> Type of the message
    };
}

#endif //IMESSAGE_HPP
