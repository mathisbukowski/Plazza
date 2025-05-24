/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "StatusMessageBuilder.hpp"

namespace Plazza {
    StatusMessageBuilder& StatusMessageBuilder::setTotalCooks(int total)
    {
        _totalCooks = total;
        return *this;
    }

    StatusMessageBuilder& StatusMessageBuilder::setBusyCooks(int busy)
    {
        _busyCooks = busy;
        return *this;
    }

    StatusMessageBuilder& StatusMessageBuilder::setStock(const std::array<int, IngredientCount>& stock)
    {
        _stock = stock;
        return *this;
    }

    StatusMessage StatusMessageBuilder::build()
    {
        StatusMessage message;
        message._totalCooks = _totalCooks;
        message._busyCooks = _busyCooks;
        message._stock = _stock;
        return message;
    }


}