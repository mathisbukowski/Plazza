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
        Regina = 1, ///> Regina pizza type
        Margarita = 2, ///> Margarita pizza type
        Americana = 4, ///> Americana pizza type
        Fantasia = 8 ///> Fantasia pizza type
    };
    enum class PizzaSize
    {
        S = 1, ///> Small pizza size
        M = 2, ///> Medium pizza size
        L = 4, ///> Large pizza size
        XL = 8, ///> Extra Large pizza size
        XXL = 16 ///> Extra Extra Large pizza size
    };
    enum class MessageType {
        UNDEFINED, ///> Undefined message type
        COMMAND, ///> Order/Command message type
        STATUS, ///> Status response message type
        PIZZA_READY, ///> Pizza ready message type
        KITCHEN_FULL, ///> Kitchen full message type
        KITCHEN_CLOSING ///> Kitchen closing message type
    };
};

#endif /* !PLAZZA_HPP_ */
