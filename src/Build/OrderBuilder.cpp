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
        for (int i = 0; i < _order.numberOfPizzasNeeded; ++i) {
            try {
                auto pizza = PizzaFactory::createPizza(_order.pizzaType, _order.pizzaSize);
                if (!pizza) {
                    std::cerr << "[OrderBuilder] Failed to create pizza (nullptr returned)\n";
                    continue;
                }
                pizzas.push_back(pizza);
            } catch (const std::bad_alloc& e) {
                std::cerr << "[OrderBuilder] std::bad_alloc: " << e.what() << "\n";
                break;
            } catch (const std::exception& e) {
                std::cerr << "[OrderBuilder] Exception: " << e.what() << "\n";
            }
        }
        return pizzas;
    }

}
