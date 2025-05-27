/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** 05
*/

#include "ReceiveStatusMessage.hpp"

#include <cstring>

namespace Plazza {
    void ReceiveStatusMessage::serialize(std::string& buffer) const
    {
        constexpr std::size_t stockSize = _stock.size();
        constexpr std::size_t totalSize = sizeof(_type) + sizeof(_totalCooks) + sizeof(_busyCooks) + sizeof(int) * stockSize;

        buffer.resize(totalSize);
        std::size_t offset = 0;

        std::memcpy(&buffer[offset], &_type, sizeof(_type));
        offset += sizeof(_type);

        std::memcpy(&buffer[offset], &_totalCooks, sizeof(_totalCooks));
        offset += sizeof(_totalCooks);

        std::memcpy(&buffer[offset], &_busyCooks, sizeof(_busyCooks));
        offset += sizeof(_busyCooks);

        std::memcpy(&buffer[offset], _stock.data(), sizeof(int) * stockSize);
    }

    void ReceiveStatusMessage::deserialize(const std::string& buffer)
    {
        constexpr std::size_t stockSize = _stock.size();
        constexpr std::size_t expectedSize = sizeof(_type) + sizeof(_totalCooks) + sizeof(_busyCooks) + sizeof(int) * stockSize;

        if (buffer.size() != expectedSize) {
            std::cerr << "Received message with wrong size!" << std::endl;
            return;
        }
        std::size_t offset = 0;
        std::memcpy(&_type, &buffer[offset], sizeof(_type));
        offset += sizeof(_type);
        std::memcpy(&_totalCooks, &buffer[offset], sizeof(_totalCooks));
        offset += sizeof(_totalCooks);
        std::memcpy(&_busyCooks, &buffer[offset], sizeof(_busyCooks));
        offset += sizeof(_busyCooks);
        std::memcpy(_stock.data(), &buffer[offset], sizeof(int) * stockSize);
    }
}
