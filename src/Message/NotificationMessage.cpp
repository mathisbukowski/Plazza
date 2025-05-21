/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "NotificationMessage.hpp"
#include <cstring>

namespace Plazza {
    NotificationMessage::NotificationMessage(MessageType type, const std::string& content)
        : _type(type), _message(content) {}

    void NotificationMessage::serialize(std::vector<char>& buffer) const
    {
        size_t len = _message.size();
        size_t totalSize = sizeof(MessageType) + sizeof(size_t) + len;

        buffer.resize(totalSize);
        char* ptr = buffer.data();
        std::memcpy(ptr, &_type, sizeof(MessageType));
        ptr += sizeof(MessageType);
        std::memcpy(ptr, &len, sizeof(size_t));
        ptr += sizeof(size_t);
        if (len > 0)
            std::memcpy(ptr, _message.data(), len);
    }

    void NotificationMessage::deserialize(const std::vector<char>& buffer)
    {
        const char* ptr = buffer.data();

        std::memcpy(&_type, ptr, sizeof(MessageType));
        ptr += sizeof(MessageType);
        size_t len;
        std::memcpy(&len, ptr, sizeof(size_t));
        ptr += sizeof(size_t);
        _message.assign(ptr, len);
    }

    size_t NotificationMessage::getPackedSize() const
    {
        return sizeof(MessageType) + sizeof(size_t) + _message.size();
    }

}