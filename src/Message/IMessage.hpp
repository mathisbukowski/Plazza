/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** IMessage
*/

#ifndef IMESSAGE_HPP_
#define IMESSAGE_HPP_

#include <vector>
#include <cstddef>
#include "plazza.hpp"

namespace Plazza {
    /**
     * @class IMessage
     * Interface for a message in the Plazza system.
     * It defines the contract for serializing and deserializing messages.
     */
    class IMessage {
    public:
        /**
         * Virtual destructor for IMessage.
         * Ensures proper cleanup of derived classes.
         */
        virtual ~IMessage() = default;

        /**
         * Serializes the message into a buffer.
         * @param buffer The buffer to serialize the message into
         */
        virtual void serialize(std::vector<char>& buffer) const = 0;

        /**
         * Deserializes the message from a buffer.
         * @param buffer The buffer to deserialize the message from
         */
        virtual void deserialize(const std::vector<char>& buffer) = 0;

        /**
         * Gets the type of the message.
         * @return The type of the serialized message
         */
        virtual MessageType getType() const = 0;
    };
}

#endif /* !IMESSAGE_HPP_ */
