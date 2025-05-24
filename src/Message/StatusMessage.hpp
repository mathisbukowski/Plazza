/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef STATUSMESSAGE_HPP
#define STATUSMESSAGE_HPP
#include <vector>
#include "plazza.hpp"
#include "Kitchen/Stock.hpp"

namespace Plazza {
    class StatusMessage {
    public:
        StatusMessage() = default;
        ~StatusMessage() = default;
        void serialize(std::vector<char>& buffer) const;
        void deserialize(const std::vector<char>& buffer);
        size_t getPackedSize() const;

        void setType(MessageType type) { _type = type; }
        MessageType getType() const { return _type; }

        void setTotalCooks(int totalCooks) { _totalCooks = totalCooks; }
        int getTotalCooks() const { return _totalCooks; }

        void setBusyCooks(int busyCooks) { _busyCooks = busyCooks; }
        int getBusyCooks() const { return _busyCooks; }

        void setStock(const std::array<int, IngredientCount>& stock) { _stock = stock; }
        const std::array<int, IngredientCount>& getStock() const { return _stock; }
        void setStock(Ingredient ingredient, int quantity) { _stock[ingredient] = quantity; }

        MessageType _type = MessageType::STATUS;
        int _totalCooks = 0;
        int _busyCooks = 0;
        std::array<int, IngredientCount> _stock{};
    };
}


#endif //STATUSMESSAGE_HPP
