/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** 05
*/

#ifndef KITCHENCLOSINGMESSAGE_HPP
#define KITCHENCLOSINGMESSAGE_HPP
#include "IMessage.hpp"

namespace Plazza {
    class KitchenClosing : public IMessage {
    public:
        KitchenClosing(uint8_t type): _type(type) {};

        ~KitchenClosing() override = default;

        void serialize(std::string& buffer) const override;

        void deserialize(const std::string& buffer) override;

        uint8_t getType() const override { return _type; }

        uint8_t _type;
        uint8_t _id = 0;
    };
}


#endif //KITCHENCLOSINGMESSAGE_HPP
