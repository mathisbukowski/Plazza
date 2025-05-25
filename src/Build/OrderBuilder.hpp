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
    /**
     * @class OrderBuilder
     * Builder for creating an order of pizzas.
     * This class takes an Order object and builds a vector of shared pointers to IPizza objects.
     */
    class OrderBuilder : IBuilder<std::vector<std::shared_ptr<IPizza>>> {
    public:
        /**
         * Default constructor for OrderBuilder.
         * Initializes the builder with an empty order.
         */
        explicit OrderBuilder(const Order& order):
        _order(order) {}
        /**
         * Builds a vector of shared pointers to IPizza objects based on the order.
         * This method creates pizzas according to the specifications in the order.
         * @return A vector of shared pointers to IPizza objects representing the order.
         */   
        std::vector<std::shared_ptr<IPizza>> build() override;
    private:
        Order _order; ///> The order containing the specifications for the pizzas to be built.
    };
}


#endif //ORDERBUILDER_HPP
