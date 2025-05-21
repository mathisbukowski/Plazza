/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef APIZZA_HPP
#define APIZZA_HPP
#include <vector>

#include "IPizza.hpp"

namespace Plazza {
    /**
     * @class APizza
     * Abstract of pizza
     */
    class APizza : public IPizza {
    public:
        /**
         * Constructor of Abstract for Pizza
         * @param type : type of the pizza
         * @param size : size of the pizza
         * @param bakingTime : baking time of a pizza
         * @param ingredients : ingredients of a pizza with quantity
         */
        APizza(PizzaType type, PizzaSize size, int bakingTime, std::vector<std::string> ingredients);
        /**
         * Gets the size of the pizza
         * @return the pizza size
         */
        PizzaSize getSize() const override;
        /**
         * Gets the type of the pizza
         * @return the pizza type
         */
        PizzaType getType() const override;
        /**
         * Gets the baking time
         * @return baking time
         */
        int getBakingTime() const override;
        /**
         * Gets all ingredients
         * @return ingredients with quantity
         */
        std::vector<std::string> getIngredients() const override;
    private:
        PizzaSize _size; ///> Size of the pizza
        PizzaType _type; ///> Type of the pizza
        int _bakingTime; ///> Baking time of a pizza
        std::vector<std::string> _ingredients; ///> Ingredients of a pizza
    };
}



#endif //APIZZA_HPP
