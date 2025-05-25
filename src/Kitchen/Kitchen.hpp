/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.hpp
*/

#ifndef PLAZZA_KITCHEN_HPP
#define PLAZZA_KITCHEN_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

#include "Stock.hpp"

namespace Plazza {
    /**
     * @class Kitchen
     * Class representing a kitchen that manages the stock and cooks pizzas.
     * It handles the number of cooks, the number of pizzas, and the restocking process.
     */
    class Kitchen {
        public:
            /**
             * Constructor to initialize the kitchen with another kitchen.
             * @param other The kitchen to copy
             */
            Kitchen(const Kitchen &other);
            /**
             * Constructor to initialize the kitchen with a number of cooks and restock time.
             * @param numberOfCooks The number of cooks in the kitchen
             * @param timeToRestock The time to restock the kitchen
             */
            Kitchen(int numberOfCooks, int timeToRestock, int fd);
            /**
             * Default destructor for the kitchen.
             */
            ~Kitchen();
            bool handleOrder(const std::vector<char>& buffer);
            /**
             * Start the kitchen and begin the restocking process.
             */
            void start();
            /**
             * Stop the kitchen and end the restocking process.
             */
            void stop();

            bool handleStatus();

            bool handleMessage();
        private:
            int _numberOfCooks; ///> Number of cooks in the kitchen
            int _numberOfPizzas; ///> Number of pizzas in the kitchen
            Stock _stock; ///> Stock of ingredients in the kitchen
            bool _running; ///> Flag to indicate if the kitchen is running
            int _timeToRestock; ///> Time to restock the kitchen
            int _fd; ///> Fd of the kitchen for communication
    };
}

#endif //PLAZZA_KITCHEN_HPP
