/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "MessageFactory.hpp"

#include "Message/KitchenClosing.hpp"
#include "Message/PingMessage.hpp"
#include "Message/PizzaOrderMessage.hpp"
#include "Message/PizzaReadyMessage.hpp"
#include "Message/StatusRequestMessage.hpp"
#include "Message/StatusResponseMessage.hpp"

namespace Plazza {
    std::unique_ptr<IMessage> MessageFactory::createMessage(const std::vector<char>& buffer)
    {
        if (buffer.size() < sizeof(MessageType)) {
            throw std::invalid_argument("Buffer too small to contain message type");
        }

        MessageType type;
        std::memcpy(&type, buffer.data(), sizeof(MessageType));

        std::unique_ptr<IMessage> message;

        switch (type) {
        case MessageType::PIZZA_ORDER:
            message = std::make_unique<PizzaOrderMessage>();
            break;
        case MessageType::PIZZA_READY:
            message = std::make_unique<PizzaReadyMessage>();
            break;
        case MessageType::STATUS_REQUEST:
            message = std::make_unique<StatusRequestMessage>();
            break;
        case MessageType::STATUS_RESPONSE:
            message = std::make_unique<StatusResponseMessage>();
            break;
        case MessageType::KITCHEN_CLOSING:
            message = std::make_unique<KitchenClosingMessage>();
            break;
        case MessageType::HEARTBEAT:
            message = std::make_unique<PingMessage>();
            break;
        default:
            throw std::invalid_argument("Unknown message type: " + std::to_string(static_cast<int>(type)));
        }

        try {
            message->deserialize(buffer);
        } catch (const std::exception& e) {
            throw std::runtime_error("Failed to deserialize message of type " +
                                   std::to_string(static_cast<int>(type)) + ": " + e.what());
        }

        return message;
    }

}
