/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "OrderBuilder.hpp"

namespace Plazza {
    std::vector<Pizza> OrderBuilder::build()
    {
        std::vector<Pizza> pizzas;
        for (int i = 0; i < _order.numberOfPizzasNeeded; i++) {
            pizzas.emplace_back(_order.pizzaType, _order.pizzaSize);
        }
        return pizzas;
    }

}