/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Stock.cpp
*/

#include "Stock.hpp"

Plazza::Stock::Stock()
{
    _ingredients.fill(5);
}

Plazza::Stock::Stock(const Plazza::Stock &other)
{
    _ingredients = other._ingredients;
}

Plazza::Stock::~Stock()
{
}

Plazza::Stock &Plazza::Stock::operator=(const Plazza::Stock &other)
{
    if (this != &other)
        _ingredients = other._ingredients;
    return *this;
}


void Plazza::Stock::restockAll()
{
    for (auto &i : _ingredients)
        i++;
}

void Plazza::Stock::add(Ingredient ing, int amount)
{
    _ingredients[ing] += amount;
}

void Plazza::Stock::remove(Ingredient ing, int amount)
{
    _ingredients[ing] = std::max(0, _ingredients[ing] - amount);
}

int Plazza::Stock::get(Ingredient ing) const
{
    return _ingredients[ing];
}

const std::array<int, Plazza::IngredientCount>& Plazza::Stock::getAll() const
{
    return _ingredients;
}
