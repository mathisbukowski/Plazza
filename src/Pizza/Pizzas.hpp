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
    class Margarita : public APizza {
    public:
        Margarita(PizzaSize size): APizza(PizzaType::MARGARITA, size, 1, {"dough", "tomato", "gruyere"}) {}
    };

    class Regina : public APizza {
    public:
        Regina(PizzaSize size)
            : APizza(PizzaType::Regina, size, 2, {"dough", "tomato", "gruyere", "ham", "mushrooms"}) {}
    };

    class Americana : public APizza {
    public:
        Americana(PizzaSize size)
            : APizza(PizzaType::Americana, size, 2, {"dough", "tomato", "gruyere", "steak"}) {}
    };

    class Fantasia : public APizza {
    public:
        Fantasia(PizzaSize size)
            : APizza(PizzaType::Fantasia, size, 4, {"dough", "tomato", "eggplant", "goat cheese", "chief love"}) {}
    };
}



#endif //PIZZAS_HPP
