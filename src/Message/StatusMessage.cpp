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
        if (buffer.empty())
            throw std::invalid_argument("buffer must be at least 1 byte");
        _type = static_cast<char>(buffer[0]);
    }
}
