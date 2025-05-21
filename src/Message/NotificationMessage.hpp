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

namespace Plazza {
    class NotificationMessage {
    public:
        NotificationMessage() = default;
        NotificationMessage(MessageType type, const std::string& content);

        void serialize(std::vector<char>& buffer) const;
        void deserialize(const std::vector<char>& buffer);
        size_t getPackedSize() const;

        MessageType _type = MessageType::UNDEFINED;
        std::string _message;
    };
}



#endif //NOTIFICATIONMESSAGE_HPP
