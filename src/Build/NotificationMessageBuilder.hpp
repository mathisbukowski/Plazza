/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef NOTIFICATIONMESSAGEBUILDER_HPP
#define NOTIFICATIONMESSAGEBUILDER_HPP

#include "IBuilder.hpp"
#include "../Message/NotificationMessage.hpp"

namespace Plazza {
    /**
     * @class NotificationMessageBuilder
     * Builder for creating NotificationMessage objects.
     * This class provides methods to set the type and message content of the notification.
     */
    class NotificationMessageBuilder : public IBuilder<NotificationMessage> {
    public:
        /**
         * Sets the type of the notification message.
         * @param type The type of the message to set.
         * @return Reference to the builder instance for method chaining.
         */
        NotificationMessageBuilder& setType(MessageType type);
        /**
         * Sets the content of the notification message.
         * @param message The content of the message to set.
         * @return Reference to the builder instance for method chaining.
         */
        NotificationMessageBuilder& setMessage(const std::string& message);
        /**
         * Builds the NotificationMessage object with the specified type and message.
         * @return A NotificationMessage object with the set properties.
         */
        NotificationMessage build() override;

    private:
        MessageType _type = MessageType::UNDEFINED; ///> The type of the notification message, default is UNDEFINED.
        std::string _message; ///> The content of the notification message, default is an empty string.
    };
}


#endif //NOTIFICATIONMESSAGEBUILDER_HPP
