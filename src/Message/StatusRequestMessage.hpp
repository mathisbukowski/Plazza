/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef STATUSREQUESTMESSAGE_HPP
#define STATUSREQUESTMESSAGE_HPP

#include "IMessage.hpp"

namespace Plazza {
    class StatusRequestMessage : public IMessage {
    public:
        StatusRequestMessage() = default;
        ~StatusRequestMessage() override = default;

        void serialize(std::vector<char>& buffer) const override;

        void deserialize(const std::vector<char>& buffer) override;

        MessageType getType() const override { return MessageType::STATUS_REQUEST; }
    };
}



#endif //STATUSREQUESTMESSAGE_HPP
