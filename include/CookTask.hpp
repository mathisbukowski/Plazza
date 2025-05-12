/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** CookTask
*/

#ifndef COOKTASK_HPP_
#define COOKTASK_HPP_

#include "../src/Pizza/PizzaType.hpp"

namespace Plazza {
    class CookTask {
        public:
            CookTask(const Pizza& pizza, double multiplier);
            void operator()() const;

        private:
            const Pizza& _pizza;
            double _multiplier;

            int getBaseCookTime(PizzaType type) const;
    };
}

#endif // COOKTASK_HPP_
