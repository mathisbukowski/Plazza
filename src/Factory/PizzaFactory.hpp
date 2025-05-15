/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PIZZAFACTORY_HPP
#define PIZZAFACTORY_HPP

#include <vector>

#include "Pizza/PizzaType.hpp"

namespace Plazza {
    class PizzaFactory {
    public:
        std::vector<Plazza::Pizza> createPizzaFromString(const std::string& input);
    };
}



#endif //PIZZAFACTORY_HPP
