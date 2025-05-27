/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** 05
*/

#ifndef RECEIVESTATUS_HPP
#define RECEIVESTATUS_HPP
#include <array>

#include "IMessage.hpp"
#include "Kitchen/Stock.hpp"


namespace Plazza {
    class ReceiveStatusMessage : public IMessage {
    public:
        ReceiveStatusMessage(uint8_t type): _type(type) {}

        ~ReceiveStatusMessage() override = default;

        void deserialize(const std::string& buffer) override;

        void serialize(std::string& buffer) const override;

        uint8_t getType() const override { return _type;}

        uint8_t _type;
        int _totalCooks = 0; ///> The total number of cooks in the kitchen
        int _busyCooks = 0; ///> The number of busy cooks in the kitchen
        std::array<int, IngredientCount> _stock{}; ///> The stock of ingredients in the kitchen
    };
}



#endif //RECEIVESTATUS_HPP
