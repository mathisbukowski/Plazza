/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef STATUSMESSAGEBUILDER_HPP
#define STATUSMESSAGEBUILDER_HPP

#include "IBuilder.hpp"
#include "Message/StatusMessage.hpp"

namespace Plazza {
    class StatusMessageBuilder : public IBuilder<StatusMessage> {
    public:
        StatusMessageBuilder& setTotalCooks(int total);

        StatusMessageBuilder& setBusyCooks(int busy);

        StatusMessageBuilder& setStock(const std::array<int, IngredientCount>& stock);

        StatusMessage build() override;

    private:
        int _totalCooks = 0;
        int _busyCooks = 0;
        std::array<int, IngredientCount> _stock{};
    };
}



#endif //STATUSMESSAGEBUILDER_HPP
