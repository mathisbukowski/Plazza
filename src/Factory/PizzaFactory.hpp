/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PIZZAFACTORY_HPP
#define PIZZAFACTORY_HPP

#include <memory>
#include <vector>
#include "Pizza/IPizza.hpp"

namespace Plazza {
    class PizzaFactory {
    public:
        static std::unique_ptr<IPizza> createPizza(PizzaType type, PizzaSize size);
        static std::vector<std::unique_ptr<IPizza>> createPizzaFromString(const std::string& input);
    };
}



#endif //PIZZAFACTORY_HPP
