/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef NOTIFICATIONMESSAGE_HPP
#define NOTIFICATIONMESSAGE_HPP
#include <vector>

#include "plazza.hpp"
#include "IMessage.hpp"

namespace Plazza {
    /**
     * @class NotificationMessage
     * Class representing a notification message in the Plazza system.
     */
    class NotificationMessage : public IMessage {
    public:
        /**
         * Default constructor for NotificationMessage.
         * Initializes the message type to UNDEFINED.
         */
        NotificationMessage() = default;
        /**
         * Constructor for NotificationMessage with specified type and content.
         * @param type The type of the message
         * @param content The content of the message
         * Initializes the message type and content.
         */
        NotificationMessage(MessageType type, const std::string& content);
        /**
         * Serializes the NotificationMessage into a buffer.
         * @param buffer The buffer to serialize the message into
         * This method converts the message type and content into a binary format for transmission.
         */
        void serialize(std::vector<char>& buffer) const override;
        /**
         * Deserializes the NotificationMessage from a buffer.
         * @param buffer The buffer to deserialize the message from
         * This method reconstructs the message type and content from the binary format.
         */
        void deserialize(const std::vector<char>& buffer) override;
        /**
         * Gets the packed size of the NotificationMessage.
         * @return The size of the serialized message in bytes
         */
        size_t getPackedSize() const override;

        MessageType _type = MessageType::UNDEFINED; ///> The type of the notification message
        std::string _message; ///> The content of the notification message
    };
}



#endif //NOTIFICATIONMESSAGE_HPP
