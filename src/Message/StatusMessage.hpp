/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef STATUSMESSAGE_HPP
#define STATUSMESSAGE_HPP
#include <vector>

#include "IMessage.hpp"
#include "plazza.hpp"
#include "Kitchen/Stock.hpp"

namespace Plazza {
    class StatusMessage : {
    public:
        StatusMessage() = default;
        ~StatusMessage() = default;
        void serialize(std::vector<char>& buffer) const;
        void deserialize(const std::vector<char>& buffer);
        size_t getPackedSize() const;

        MessageType _type = MessageType::STATUS;
        int _totalCooks = 0;
        int _busyCooks = 0;
        std::array<int, IngredientCount> _stock{};
    };
}


#endif //STATUSMESSAGE_HPP
