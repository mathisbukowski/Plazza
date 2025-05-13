/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** plazza
*/

#ifndef PLAZZA_HPP_
#define PLAZZA_HPP_

#include <iostream>

namespace Plazza {
    class Tools;

    enum class PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };
    enum class PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
};

#endif /* !PLAZZA_HPP_ */
