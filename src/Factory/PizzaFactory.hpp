/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PIZZAFACTORY_HPP
#define PIZZAFACTORY_HPP

#include <memory>
#include <vector>
#include "Pizza/IPizza.hpp"

namespace Plazza {
    /**
     * @class PizzaFactory
     * Factory class for creating pizza objects.
     * This class provides methods to create pizzas based on type and size, and to create pizzas from a string input.
     */
    class PizzaFactory {
    public:
        /**
         * Creates a pizza of the specified type and size.
         * @param type The type of pizza to create.
         * @param size The size of the pizza to create.
         * @return A shared pointer to the created IPizza object.
         */
        static std::shared_ptr<IPizza> createPizza(PizzaType type, PizzaSize size);
        /**
         * Creates a pizza from a string input.
         * The string should contain the type and size of the pizza in a specific format.
         * @param input The string input containing the pizza specifications.
         * @return A vector of shared pointers to IPizza objects created from the input.
         */
        static std::vector<std::shared_ptr<IPizza>> createPizzaFromString(const std::string& input);
    };
}



#endif //PIZZAFACTORY_HPP
