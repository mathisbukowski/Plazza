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
#include "IMessage.hpp"

namespace Plazza {
    /**
     * @class StatusMessage
     * Class representing a status message in the Plazza system.
     * It contains information about the kitchen's status, including the number of cooks and stock levels.
     */
    class StatusMessage : public IMessage {
    public:
        /**
         * Default constructor for StatusMessage.
         * Initializes the message type to STATUS and sets default values for total cooks, busy cooks, and stock.
         */
        StatusMessage(uint8_t type): _type(type) {}
        /**
         * Default destructor for StatusMessage.
         */
        ~StatusMessage() = default;
        /**
         * Serializes the StatusMessage into a buffer.
         * @param buffer The buffer to serialize the message into
         * This method converts the message type, total cooks, busy cooks, and stock into a binary format for transmission.
         */
        void serialize(std::string& buffer) const override;
        /**
         * Deserializes the StatusMessage from a buffer.
         * @param buffer The buffer to deserialize the message from
         * This method reconstructs the message type, total cooks, busy cooks, and stock from the binary format.
         */
        void deserialize(const std::string& buffer) override;
        /**
         * Gets the type of the status message.
         * @return The type of the message
         */
        uint8_t getType() const override { return _type; }

        uint8_t _type; ///> The type of the status message
    };
}


#endif //STATUSMESSAGE_HPP
