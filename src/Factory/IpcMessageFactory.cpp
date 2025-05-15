/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "IpcMessageFactory.hpp"

#include <cstring>

#include "Reception/Message.hpp"

namespace Plazza {
    std::unique_ptr<Message> IpcMessageFactory::create(MessageType type)
    {
        switch (type) {
            case MessageType::COMMAND:
                return std::make_unique<OrderMessage>();
            case MessageType::STATUS_RESPONSE:
                return std::make_unique<StatusMessage>();
            case MessageType::PIZZA_READY:
            case MessageType::KITCHEN_FULL:
            case MessageType::KITCHEN_CLOSING:
                return std::make_unique<NotificationMessage>();
            default:
                return nullptr;
        }

    }

}
