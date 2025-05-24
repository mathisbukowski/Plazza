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
    class NotificationMessageBuilder : public IBuilder<NotificationMessage> {
    public:
        NotificationMessageBuilder& setType(MessageType type);

        NotificationMessageBuilder& setMessage(const std::string& message);

        NotificationMessage build() override;

    private:
        MessageType _type = MessageType::UNDEFINED;
        std::string _message;
    };
}


#endif //NOTIFICATIONMESSAGEBUILDER_HPP
