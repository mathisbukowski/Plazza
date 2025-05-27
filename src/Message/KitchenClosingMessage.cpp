/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** 05
*/

#include "KitchenClosingMessage.hpp"

namespace Plazza {
    void KitchenClosing::serialize(std::string& buffer) const
    {
        buffer.clear();
        buffer.push_back(static_cast<char>(_type));
        buffer.push_back(static_cast<char>(_id));
    }

    void KitchenClosing::deserialize(const std::string& buffer)
    {
        if (buffer.size() < 2) {
            throw std::invalid_argument("buffer too small");
        }
        _type = static_cast<char>(buffer[0]);
        _id = static_cast<char>(buffer[1]);
    }
}