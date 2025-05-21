/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Stock.hpp
*/

#ifndef PLAZZA_STOCK_HPP
#define PLAZZA_STOCK_HPP
#include <array>

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

            void restockAll();
            void add(Ingredient ing, int amount);
            void remove(Ingredient ing, int amount);
            int get(Ingredient ing) const;

            const std::array<int, IngredientCount> &getAll() const;
    private:
        std::array<int, IngredientCount> _ingredients;
    };
}

#endif //PLAZZA_STOCK_HPP
