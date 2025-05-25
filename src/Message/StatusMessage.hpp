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
        StatusMessage() = default;
        /**
         * Default destructor for StatusMessage.
         */
        ~StatusMessage() = default;
        /**
         * Serializes the StatusMessage into a buffer.
         * @param buffer The buffer to serialize the message into
         * This method converts the message type, total cooks, busy cooks, and stock into a binary format for transmission.
         */
        void serialize(std::vector<char>& buffer) const override;
        /**
         * Deserializes the StatusMessage from a buffer.
         * @param buffer The buffer to deserialize the message from
         * This method reconstructs the message type, total cooks, busy cooks, and stock from the binary format.
         */
        void deserialize(const std::vector<char>& buffer) override;
        /**
         * Gets the packed size of the StatusMessage.
         * @return The size of the serialized message in bytes
         * This method calculates the total size required to store the message type, total cooks, busy cooks, and stock.
         */
        size_t getPackedSize() const override;
        /**
         * Sets the type of the status message.
         * @param type The type of the message
         */
        void setType(MessageType type) { _type = type; }
        /**
         * Gets the type of the status message.
         * @return The type of the message
         */
        MessageType getType() const { return _type; }
        /**
         * Sets the total number of cooks in the kitchen.
         * @param totalCooks The total number of cooks
         */
        void setTotalCooks(int totalCooks) { _totalCooks = totalCooks; }
        /**
         * Gets the total number of cooks in the kitchen.
         * @return The total number of cooks
         */
        int getTotalCooks() const { return _totalCooks; }
        /**
         * Sets the number of busy cooks in the kitchen.
         * @param busyCooks The number of busy cooks
         */
        void setBusyCooks(int busyCooks) { _busyCooks = busyCooks; }
        /**
         * Gets the number of busy cooks in the kitchen.
         * @return The number of busy cooks
         */
        int getBusyCooks() const { return _busyCooks; }
        /**
         * Sets the stock of ingredients in the kitchen.
         * @param stock An array containing the quantities of each ingredient
         */
        void setStock(const std::array<int, IngredientCount>& stock) { _stock = stock; }
        /**
         * Gets the stock of ingredients in the kitchen.
         * @return A constant reference to an array containing the quantities of each ingredient
         */
        const std::array<int, IngredientCount>& getStock() const { return _stock; }
        /**
         * Sets the quantity of a specific ingredient in the stock.
         * @param ingredient The ingredient to set
         * @param quantity The quantity to set for the ingredient
         * This method updates the stock for a specific ingredient to the given quantity.
         */
        void setStock(Ingredient ingredient, int quantity) { _stock[ingredient] = quantity; }

        MessageType _type = MessageType::STATUS; ///> The type of the status message
        int _totalCooks = 0; ///> The total number of cooks in the kitchen
        int _busyCooks = 0; ///> The number of busy cooks in the kitchen
        std::array<int, IngredientCount> _stock{}; ///> The stock of ingredients in the kitchen
    };
}


#endif //STATUSMESSAGE_HPP
