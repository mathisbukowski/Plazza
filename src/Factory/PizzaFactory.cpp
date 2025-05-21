/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "PizzaFactory.hpp"

#include "Build/OrderBuilder.hpp"
#include "Pizza/Pizzas.hpp"
#include "Reception/Parser.hpp"
#include "Tools/ResultException.hpp"

namespace Plazza {
    std::unique_ptr<IPizza> PizzaFactory::createPizza(PizzaType type, PizzaSize size)
    {
        switch (type) {
            case PizzaType::Margarita: return std::make_unique<Margarita>(size);
            case PizzaType::Regina: return std::make_unique<Regina>(size);
            case PizzaType::Americana: return std::make_unique<Americana>(size);
            case PizzaType::Fantasia: return std::make_unique<Fantasia>(size);
            default: throw std::invalid_argument("Invalid pizza type");
        }
    }

    std::vector<std::unique_ptr<IPizza>> PizzaFactory::createPizzaFromString(const std::string& input)
    {
        Parser parser;
        std::vector<Order> orders;
        auto resultOrders = handleExceptions([&](const std::string& str) {
            return parser.parse(str);
        }, input);

        std::vector<std::unique_ptr<IPizza>> queueOfPizzas;

        if (!resultOrders.hasValue())
            return queueOfPizzas;

        orders = resultOrders.getValue();
        for (const auto& order : orders) {
            OrderBuilder builder(order);
            auto pizzas = builder.build();
            std::move(pizzas.begin(), pizzas.end(), std::back_inserter(queueOfPizzas));
        }
        return queueOfPizzas;
    }
}
