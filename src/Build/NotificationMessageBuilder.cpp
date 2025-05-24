/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "NotificationMessageBuilder.hpp"

namespace Plazza {
    NotificationMessageBuilder& NotificationMessageBuilder::setType(MessageType type)
    {
        _type = type;
        return *this;
    }

    NotificationMessageBuilder& NotificationMessageBuilder::setMessage(const std::string& message)
    {
        _message = message;
        return *this;
    }

    NotificationMessage NotificationMessageBuilder::build()
    {
        return NotificationMessage(_type, _message);
    }
}