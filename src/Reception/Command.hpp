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
    /**
     * @class Command
     * Class representing a command for a pizza order.
     * It contains the type, size, and quantity of pizzas needed.
     * @note This class is used to parse and store the command information.
     */
    class Command {
    public:
        /**
         * Default constructor to initialize the command with default values.
         */
        Command() = default;

        /**
         * String to PizzaType conversion function.
         * @param pizzaString The string representation of the pizza type
         * @return The corresponding PizzaType enum value
         */
        PizzaType stringToPizzaType(const std::string& pizzaString);
        /**
         * String to PizzaSize conversion function.
         * @param pizzaString The string representation of the pizza size
         * @return The corresponding PizzaSize enum value
         */
        PizzaSize stringToPizzaSize(const std::string& pizzaString);
        /**
         * String to quantity conversion function.
         * @param quantityStr The string representation of the quantity
         * @return The corresponding integer value of the quantity
         */
        int parseQuantity(const std::string& quantityStr);

        PizzaType pizzaType; ///> Type of the pizza
        PizzaSize pizzaSize; ///> Size of the pizza
        int numberOfPizzasNeeded; ///> Number of pizzas needed
    };
}


#endif //COMMAND_HPP
