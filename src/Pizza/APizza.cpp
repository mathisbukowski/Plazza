/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "APizza.hpp"

namespace Plazza {
    APizza::APizza(PizzaType type, PizzaSize size, int bakingTime, std::vector<std::string> ingredients):
    _size(size), _type(type), _bakingTime(bakingTime), _ingredients(std::move(ingredients)) {}

    PizzaSize APizza::getSize() const
    {
        return _size;
    }

    PizzaType APizza::getType() const
    {
        return _type;
    }
    int APizza::getBakingTime() const
    {
        return _bakingTime;
    }
    std::vector<std::string>APizza::getIngredients() const
    {
        return _ingredients;
    }

}