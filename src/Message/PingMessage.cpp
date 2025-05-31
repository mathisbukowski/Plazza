/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "PingMessage.hpp"

namespace Plazza {
    void PingMessage::serialize(std::vector<char>& buffer) const
    {
        buffer.clear();
        buffer.reserve(sizeof(MessageType) + sizeof(uint64_t));

        MessageType msgType = MessageType::HEARTBEAT;
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&msgType),
                     reinterpret_cast<const char*>(&msgType) + sizeof(MessageType));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_timestamp),
                     reinterpret_cast<const char*>(&_timestamp) + sizeof(uint64_t));

    }
    void PingMessage::deserialize(const std::vector<char>& buffer)
    {
        if (buffer.size() < sizeof(MessageType) + sizeof(uint64_t)) {
            throw std::invalid_argument("Buffer too small for HeartbeatMessage");
        }
        size_t offset = sizeof(MessageType);
        std::memcpy(&_timestamp, buffer.data() + offset, sizeof(uint64_t));

    }

}