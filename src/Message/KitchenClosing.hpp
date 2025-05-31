/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef KITCHENCLOSING_HPP
#define KITCHENCLOSING_HPP

#include "IMessage.hpp"

namespace Plazza {
    class KitchenClosingMessage : public IMessage {
    private:
        uint32_t _kitchenId;
        uint32_t _reason;

    public:
        KitchenClosingMessage(): _kitchenId(0), _reason(0) {}
        KitchenClosingMessage(uint32_t kitchenId, uint32_t reason) : _kitchenId(kitchenId), _reason(reason) {}

        ~KitchenClosingMessage() override = default;

        void serialize(std::vector<char>& buffer) const override;

        void deserialize(const std::vector<char>& buffer) override;

        MessageType getType() const override { return MessageType::KITCHEN_CLOSING; }

        uint32_t getKitchenId() const { return _kitchenId; }
        uint32_t getReason() const { return _reason; }
    };
}



#endif //KITCHENCLOSING_HPP
