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
    /**
     * @class StatusMessageBuilder
     * Builder for creating StatusMessage objects.
     * This class provides methods to set the total cooks, busy cooks, and stock of ingredients.
     */
    class StatusMessageBuilder : public IBuilder<StatusMessage> {
    public:
        /**
         * Sets the total number of cooks in the kitchen.
         * @param total The total number of cooks to set.
         * @return Reference to the builder instance for method chaining.
         */
        StatusMessageBuilder& setTotalCooks(int total);
        /**
         * Sets the number of busy cooks in the kitchen.
         * @param busy The number of busy cooks to set.
         * @return Reference to the builder instance for method chaining.
         */
        StatusMessageBuilder& setBusyCooks(int busy);
        /**
         * Sets the stock of ingredients in the kitchen.
         * @param stock An array containing the quantities of each ingredient.
         * @return Reference to the builder instance for method chaining.
         */
        StatusMessageBuilder& setStock(const std::array<int, IngredientCount>& stock);
        /**
         * Sets the quantity of a specific ingredient in the stock.
         * @param ingredient The ingredient to set the quantity for.
         * @param quantity The quantity of the ingredient to set.
         * @return Reference to the builder instance for method chaining.
         */
        StatusMessage build() override;

    private:
        int _totalCooks = 0; ///> The total number of cooks in the kitchen, default is 0.
        int _busyCooks = 0; ///> The number of busy cooks in the kitchen, default is 0.
        std::array<int, IngredientCount> _stock{}; ///> The stock of ingredients in the kitchen, default is an empty array.
    };
}



#endif //STATUSMESSAGEBUILDER_HPP
