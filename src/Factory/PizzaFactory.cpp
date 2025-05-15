/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "PizzaFactory.hpp"

#include "Build/OrderBuilder.hpp"
#include "Reception/Parser.hpp"
#include "Tools/ResultException.hpp"

namespace Plazza {
    std::vector<Plazza::Pizza> PizzaFactory::createPizzaFromString(const std::string& input)
    {
        Parser parser;

        std::vector<Order> orders;
        auto resultOrders = handleExceptions([&](const std::string& str) {
            return parser.parse(str);
        }, input);
        std::vector<Pizza> queueOfPizzas;

        if (resultOrders.hasValue())
            orders = resultOrders.getValue();
        else
            return queueOfPizzas;
        for (const auto& order : orders) {
            OrderBuilder builder(order);
            std::vector<Pizza> pizzas = builder.build();
            queueOfPizzas.insert(queueOfPizzas.end(), pizzas.begin(), pizzas.end());
        }
        return queueOfPizzas;
    }

}
