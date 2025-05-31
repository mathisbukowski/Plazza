/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "KitchenClosing.hpp"


namespace Plazza {
    void KitchenClosingMessage::serialize(std::vector<char>& buffer) const
    {
        buffer.clear();
        buffer.reserve(sizeof(MessageType) + 2 * sizeof(uint32_t));

        MessageType msgType = MessageType::KITCHEN_CLOSING;
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&msgType),
                     reinterpret_cast<const char*>(&msgType) + sizeof(MessageType));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_kitchenId),
                     reinterpret_cast<const char*>(&_kitchenId) + sizeof(uint32_t));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&_reason),
                     reinterpret_cast<const char*>(&_reason) + sizeof(uint32_t));
    }
    void KitchenClosingMessage::deserialize(const std::vector<char>& buffer)
    {
        if (buffer.size() < sizeof(MessageType) + 2 * sizeof(uint32_t)) {
            throw std::invalid_argument("Buffer too small for KitchenClosingMessage");
        }

        size_t offset = sizeof(MessageType);
        std::memcpy(&_kitchenId, buffer.data() + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t);
        std::memcpy(&_reason, buffer.data() + offset, sizeof(uint32_t));
    }

}