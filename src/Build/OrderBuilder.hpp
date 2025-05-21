/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef ORDERBUILDER_HPP
#define ORDERBUILDER_HPP
#include <memory>
#include "IBuilder.hpp"
#include <vector>
#include "Pizza/IPizza.hpp"
#include "Reception/Order.hpp"

namespace Plazza {
    class OrderBuilder : IBuilder<std::vector<std::shared_ptr<IPizza>>> {
    public:
        explicit OrderBuilder(const Order& order):
        _order(order) {}

        std::vector<std::shared_ptr<IPizza>> build() override;
    private:
        Order _order;
    };
}


#endif //ORDERBUILDER_HPP
