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
