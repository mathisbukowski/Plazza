/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PIZZAS_HPP
#define PIZZAS_HPP
#include "APizza.hpp"

namespace Plazza {
    /**
     * @class Margarita
     * Represents a Margarita pizza.
     * Inherits from APizza and initializes with specific ingredients and size.
     */
    class Margarita : public APizza {
    public:
        /**
         * Constructor for Margarita pizza.
         * @param size The size of the pizza
         */
        Margarita(PizzaSize size): APizza(PizzaType::Margarita, size, 1, {"dough", "tomato", "gruyere"}) {}
    };

    /**
     * @class Regina
     * Represents a Regina pizza.
     * Inherits from APizza and initializes with specific ingredients and size.
     */
    class Regina : public APizza {
    public:
        /**
         * Constructor for Regina pizza.
         * @param size The size of the pizza
         */
        Regina(PizzaSize size)
            : APizza(PizzaType::Regina, size, 2, {"dough", "tomato", "gruyere", "ham", "mushrooms"}) {}
    };

    /**
     * @class Americana
     * Represents an Americana pizza.
     * Inherits from APizza and initializes with specific ingredients and size.
     */
    class Americana : public APizza {
    public:
        /**
         * Constructor for Americana pizza.
         * @param size The size of the pizza
         */
        Americana(PizzaSize size)
            : APizza(PizzaType::Americana, size, 2, {"dough", "tomato", "gruyere", "steak"}) {}
    };

    /**
     * @class Fantasia
     * Represents a Fantasia pizza.
     * Inherits from APizza and initializes with specific ingredients and size.
     */
    class Fantasia : public APizza {
    public:
        /**
         * Constructor for Fantasia pizza.
         * @param size The size of the pizza
         */
        Fantasia(PizzaSize size)
            : APizza(PizzaType::Fantasia, size, 4, {"dough", "tomato", "eggplant", "goat cheese", "chief love"}) {}
    };
}



#endif //PIZZAS_HPP
