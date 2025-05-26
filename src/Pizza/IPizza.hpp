/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** PizzaType
*/

#ifndef PIZZATYPE_HPP_
#define PIZZATYPE_HPP_

#include "plazza.hpp"
#include <vector>

namespace Plazza
{
    /**
     * @class Pizza
     * Class representing a pizza.
     */
    class IPizza {
        public:
            /**
             * Default destructor
             */
            virtual ~IPizza() = default;
            /**
             * Get the type of the pizza.
             * @return The type of the pizza
             */
            virtual PizzaType getType() const = 0;
            /**
             * Get the size of the pizza.
             * @return The size of the pizza
             */
            virtual PizzaSize getSize() const = 0;
            /**
             * Gets the baking time
             * @return baking time
             */
            virtual int getBakingTime() const = 0;
            /**
             * Gets all the ingredients with these quantities
             * @return a vector of ingredients
             */
            virtual std::vector<std::string> getIngredients() const = 0;
    };
}

#endif /* !PIZZATYPE_HPP_ */
