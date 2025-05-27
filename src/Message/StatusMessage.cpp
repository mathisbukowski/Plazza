/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "StatusMessage.hpp"

#include <cstring>

namespace Plazza {
    void StatusMessage::serialize(std::string& buffer) const
    {
        buffer.clear();
        buffer.push_back(static_cast<char>(_type));
    }

    void StatusMessage::deserialize(const std::string& buffer)
    {
        if (buffer.size() < 1) {
            std::cerr << "Buffer is too small" << std::endl;
            return;
        }
        _type = static_cast<char>(buffer[0]);
    }
}
