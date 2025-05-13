/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "plazza.hpp"

namespace Plazza {
    class Command {
    public:
        Command(const std::string& pizzaType, const std::string& pizzaSize, const std::string& numberOfPizzas);

        PizzaType stringToPizzaType(const std::string& pizzaString);
        PizzaSize stringToPizzaSize(const std::string& pizzaString);
        int parseQuantity(const std::string& quantityStr);

        PizzaType pizzaType;
        PizzaSize pizzaSize;
        int numberOfPizzasNeeded;
    };
}


#endif //COMMAND_HPP
