/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "OrderBuilder.hpp"

#include "Factory/PizzaFactory.hpp"

namespace Plazza {
    std::vector<std::shared_ptr<IPizza>> OrderBuilder::build()
    {
        std::vector<std::shared_ptr<IPizza>> pizzas;
        for (int i = 0; i < _order.numberOfPizzasNeeded; ++i)
            pizzas.push_back(PizzaFactory::createPizza(_order.pizzaType, _order.pizzaSize));
        return pizzas;
    }

}
