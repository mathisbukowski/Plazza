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
        PIZZA_ORDER = 1,        // Reception -> Kitchen: New pizza to cook
        PIZZA_READY = 2,        // Kitchen -> Reception: Pizza is ready
        STATUS_REQUEST = 3,     // Reception -> Kitchen: Request kitchen status
        STATUS_RESPONSE = 4,    // Kitchen -> Reception: Kitchen status info
        KITCHEN_CLOSING = 5,    // Kitchen -> Reception: Kitchen is closing
        HEARTBEAT = 6          // Bidirectional: Keep connection alive
    };
};

#endif /* !PLAZZA_HPP_ */
