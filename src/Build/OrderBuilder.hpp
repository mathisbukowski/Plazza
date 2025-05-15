/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef ORDERBUILDER_HPP
#define ORDERBUILDER_HPP
#include "IBuilder.hpp"
#include <vector>

#include "Pizza/PizzaType.hpp"
#include "Reception/Order.hpp"

namespace Plazza {
    class OrderBuilder : IBuilder<std::vector<Pizza>> {
    public:
        explicit OrderBuilder(const Order& order):
        _order(order) {}

        std::vector<Pizza> build() override;
    private:
        Order _order;
    };
}


#endif //ORDERBUILDER_HPP
