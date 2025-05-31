/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "StatusRequestMessage.hpp"

namespace Plazza {
    void StatusRequestMessage::deserialize(const std::vector<char>& buffer)
    {
        if (buffer.size() < sizeof(MessageType)) {
            throw std::invalid_argument("Buffer too small for StatusRequestMessage");
        }
    }

    void StatusRequestMessage::serialize(std::vector<char>& buffer) const
    {
        buffer.clear();
        buffer.reserve(sizeof(MessageType));

        MessageType msgType = MessageType::STATUS_REQUEST;
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&msgType),
                     reinterpret_cast<const char*>(&msgType) + sizeof(MessageType));
    }


}