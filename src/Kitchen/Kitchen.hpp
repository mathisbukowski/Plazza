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
#include "Stock.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(const Kitchen &other);
            Kitchen(int numberOfCooks, int timeToRestock);
            ~Kitchen();
            void start();
            void stop();
        private:
            int _numberOfCooks;
            int _numberOfPizzas;
            Stock _stock;
            bool _running;
            int _timeToRestock;
    };
}

#endif //PLAZZA_KITCHEN_HPP
