/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PINGMESSAGE_HPP
#define PINGMESSAGE_HPP

#include "IMessage.hpp"

namespace Plazza {
    class PingMessage : public IMessage {
    private:
        uint64_t _timestamp;

    public:
        PingMessage(uint64_t timestamp) : _timestamp(timestamp) {}

        ~PingMessage() override = default;

        void serialize(std::vector<char>& buffer) const override;

        void deserialize(const std::vector<char>& buffer) override;

        MessageType getType() const override { return MessageType::HEARTBEAT; }

        uint64_t getTimestamp() const { return _timestamp; }
        void setTimestamp(uint64_t timestamp) { _timestamp = timestamp; }
    };
}


#endif //PINGMESSAGE_HPP
