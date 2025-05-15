/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** PizzaType
*/

#ifndef PIZZATYPE_HPP_
#define PIZZATYPE_HPP_

#include "plazza.hpp"

namespace Plazza
{
    /**
     * @class Pizza
     * Class representing a pizza.
     */
    class Pizza {
        public:
            /**
             * Constructor to initialize a pizza with its type, size, and quantity.
             * @param type The type of the pizza
             * @param size The size of the pizza
             */
            Pizza(PizzaType type, PizzaSize size)
                : _type(type), _size(size) {}
            /**
             * Get the type of the pizza.
             * @return The type of the pizza
             */
            PizzaType getType() const { return _type; }
            /**
             * Get the size of the pizza.
             * @return The size of the pizza
             */
            PizzaSize getSize() const { return _size; }
        private:
            PizzaType _type; ///> Type of the pizza
            PizzaSize _size; ///> Size of the pizza
    };
}

#endif /* !PIZZATYPE_HPP_ */
