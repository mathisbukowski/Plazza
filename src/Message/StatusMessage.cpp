/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "StatusMessage.hpp"

#include <cstring>

namespace Plazza {
    void StatusMessage::serialize(std::vector<char>& buffer) const
    {
        std::size_t totalSize = this->getPackedSize();
        buffer.resize(totalSize);
        char* ptr = buffer.data();

        std::memcpy(ptr, &_type, sizeof(MessageType));
        ptr += sizeof(MessageType);
        std::memcpy(ptr, &_totalCooks, sizeof(int));
        ptr += sizeof(int);
        std::memcpy(ptr, &_busyCooks, sizeof(int));
        ptr += sizeof(int);
        for (int amount : _stock) {
            std::memcpy(ptr, &amount, sizeof(int));
            ptr += sizeof(int);
        }
    }

    void StatusMessage::deserialize(const std::vector<char>& buffer)
    {
        const char* ptr = buffer.data();

        std::memcpy(&_type, ptr, sizeof(MessageType));
        ptr += sizeof(MessageType);
        std::memcpy(&_totalCooks, ptr, sizeof(int));
        ptr += sizeof(int);
        std::memcpy(&_busyCooks, ptr, sizeof(int));
        ptr += sizeof(int);
        for (int &amount : _stock) {
            std::memcpy(&amount, ptr, sizeof(int));
            ptr += sizeof(int);
        }
    }

    std::size_t StatusMessage::getPackedSize() const
    {
        return sizeof(MessageType) + 2 * sizeof(int) + IngredientCount * sizeof(int);
    }
}
