/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Stock.hpp
*/

#ifndef PLAZZA_STOCK_HPP
#define PLAZZA_STOCK_HPP
#include <array>
#include <memory>
#include "../Pizza/IPizza.hpp"

namespace Plazza {
    enum Ingredient {
        Dough = 0,
        Tomato,
        Gruyere,
        Ham,
        Mushrooms,
        Steaks,
        Eggplant,
        GoatCheese,
        ChiefLove,
        IngredientCount
    };
    /**
     * @class Stock
     * Class representing the stock of ingredients in the kitchen.
     * It manages the quantities of various ingredients and provides methods to add or remove them.
     */
    class Stock{
        public:
            /**
             * Default constructor to initialize the stock with default values.
             */
            Stock();
            /**
             * Constructor to initialize the stock with another stock.
             * @param other The stock to copy
             */
            Stock(const Stock &other);
            /**
             * Destructor to clean up the stock.
             */
            ~Stock();
            /**
             * Operator to check if two stocks are equal.
             * @param other The stock to compare with
             * @return True if the stocks are equal, false otherwise
             */
            Stock &operator=(const Stock &other);
            /**
             * Restocks all ingredients to their default values.
             */
            void restockAll();
            /**
             * Adds a specified amount of an ingredient to the stock.
             * @param ing The ingredient to add
             * @param amount The amount to add
             */
            void add(Ingredient ing, int amount);
            /**
             * Removes a specified amount of an ingredient from the stock.
             * @param ing The ingredient to remove
             * @param amount The amount to remove
             */
            void remove(Ingredient ing, int amount);
            /**
             * Checks if the stock has enough of a specified ingredient.
             * @param ing The ingredient to check
             * @param amount The amount to check for
             * @return True if there is enough of the ingredient, false otherwise
             */
            int get(Ingredient ing) const;
            /**
             * Gets the current stock of all ingredients.
             * @return A constant reference to an array containing the quantities of all ingredients
             */
            const std::array<int, IngredientCount> &getAll() const;
            /**
            * Checks if the stock has enough ingredients for a specific pizza.
            * @param pizza The pizza to check ingredients for
            * @return True if there are enough ingredients, false otherwise
            */
            bool hasIngredientsFor(const std::shared_ptr<IPizza>& pizza) const;

            /**
            * Consumes the ingredients needed for a specific pizza.
            * @param pizza The pizza to consume ingredients for
            * @return True if ingredients were consumed successfully, false otherwise
            */
            bool consumeIngredientsFor(const std::shared_ptr<IPizza>& pizza);
            /**
             * Converts a string representation of an ingredient to its enum value.
             * @param ingredientName The name of the ingredient as a string
             * @return The corresponding Ingredient enum value
             */
            Ingredient stringToIngredient(const std::string& ingredientName) const;
    private:
        std::array<int, IngredientCount> _ingredients; ///> Array to hold the quantities of each ingredient
    };
}

#endif //PLAZZA_STOCK_HPP
