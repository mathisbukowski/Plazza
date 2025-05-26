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

bool Plazza::Stock::hasIngredientsFor(const std::shared_ptr<IPizza> &pizza) const
{
    auto ingredients = pizza->getIngredients();
    for (const auto &ingredientName : ingredients) {
        Ingredient ingredient = this->stringToIngredient(ingredientName);
        if (_ingredients[ingredient] <= 0) {
            return false;
        }
    }
    return true;
}

bool Plazza::Stock::consumeIngredientsFor(const std::shared_ptr<IPizza> &pizza)
{
    if (!this->hasIngredientsFor(pizza)) {
        return false;
    }
    auto ingredients = pizza->getIngredients();
    for (const auto &ingredientName : ingredients) {
        Ingredient ingredient = this->stringToIngredient(ingredientName);
        this->remove(ingredient, 1);
    }
    return true;
}

Plazza::Ingredient Plazza::Stock::stringToIngredient(const std::string &ingredientName) const
{
    if (ingredientName == "dough") return Ingredient::Dough;
    if (ingredientName == "tomato") return Ingredient::Tomato;
    if (ingredientName == "gruyere") return Ingredient::Gruyere;
    if (ingredientName == "ham") return Ingredient::Ham;
    if (ingredientName == "mushrooms") return Ingredient::Mushrooms;
    if (ingredientName == "steak") return Ingredient::Steaks;
    if (ingredientName == "eggplant") return Ingredient::Eggplant;
    if (ingredientName == "goat cheese") return Ingredient::GoatCheese;
    if (ingredientName == "chief love") return Ingredient::ChiefLove;
    return Ingredient::Dough;
}