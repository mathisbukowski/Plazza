/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef STATUSRESPONSEMESSAGE_HPP
#define STATUSRESPONSEMESSAGE_HPP

#include "IMessage.hpp"
#include <array>

#include "Kitchen/Stock.hpp"

namespace Plazza {
    class StatusResponseMessage : public IMessage {
    private:
        static constexpr size_t STOCK_SIZE = IngredientCount;
        uint32_t _activeCooks;
        uint32_t _totalCooks;
        uint32_t _pizzasInQueue;
        uint32_t _maxPizzasCapacity;
        std::array<int, IngredientCount> _stock;

    public:
        StatusResponseMessage(): _activeCooks(0), _totalCooks(0), _pizzasInQueue(0), _maxPizzasCapacity(0)
        {
            _stock.fill(5);
        }
        StatusResponseMessage(uint32_t activeCooks, uint32_t totalCooks, uint32_t pizzasInQueue, uint32_t maxPizzasCapacity, std::array<int, IngredientCount> stock):
        _activeCooks(activeCooks), _totalCooks(totalCooks), _pizzasInQueue(pizzasInQueue), _maxPizzasCapacity(maxPizzasCapacity), _stock(stock) {}

        ~StatusResponseMessage() override = default;

        void serialize(std::vector<char>& buffer) const override;

        void deserialize(const std::vector<char>& buffer) override;

        MessageType getType() const override { return MessageType::STATUS_RESPONSE; }
        void setActiveCooks(uint32_t active) { _activeCooks = active; }
        void setTotalCooks(uint32_t total) { _totalCooks = total; }
        void setPizzasInQueue(uint32_t pizzas) { _pizzasInQueue = pizzas; }
        void setMaxPizzasCapacity(uint32_t capacity) { _maxPizzasCapacity = capacity; }
        void setStock(const std::array<int, STOCK_SIZE>& stock) { _stock = stock; }
        void setIngredientStock(size_t index, int quantity) {
            if (index < STOCK_SIZE) _stock[index] = quantity;
        }

        uint32_t getActiveCooks() const { return _activeCooks; }
        uint32_t getTotalCooks() const { return _totalCooks; }
        uint32_t getPizzasInQueue() const { return _pizzasInQueue; }
        uint32_t getMaxPizzasCapacity() const { return _maxPizzasCapacity; }
        const std::array<int, STOCK_SIZE>& getStock() const { return _stock; }
        int getIngredientStock(size_t index) const {
            return (index < STOCK_SIZE) ? _stock[index] : 0;
        }
    };
}


#endif //STATUSRESPONSEMESSAGE_HPP
