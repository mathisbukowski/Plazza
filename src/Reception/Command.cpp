/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "Command.hpp"
#include <algorithm>

namespace Plazza {

    PizzaType Command::stringToPizzaType(const std::string& pizzaString)
    {
        std::string t = pizzaString;
        std::transform(t.begin(), t.end(), t.begin(), ::tolower);

        if (t == "regina")
            return PizzaType::Regina;
        if (t == "margarita")
            return PizzaType::Margarita;
        if (t == "americana")
            return PizzaType::Americana;
        if (t == "fantasia")
            return PizzaType::Fantasia;
        throw std::invalid_argument("Invalid pizza type: " + pizzaString);
    }

    PizzaSize Command::stringToPizzaSize(const std::string& pizzaString)
    {
        std::string s = pizzaString;
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);

        if (s == "S")
            return PizzaSize::S;
        if (s == "M")
            return PizzaSize::M;
        if (s == "L")
            return PizzaSize::L;
        if (s == "XL")
            return PizzaSize::XL;
        if (s == "XXL")
            return PizzaSize::XXL;
        throw std::invalid_argument("Invalid pizza size: " + pizzaString);
    }

    int Command::parseQuantity(const std::string& quantityStr)
    {
        if (quantityStr.size() < 2 || quantityStr[0] != 'x')
            throw std::invalid_argument("Invalid quantity format: " + quantityStr);

        std::string numPart = quantityStr.substr(1);
        if (!std::all_of(numPart.begin(), numPart.end(), ::isdigit))
            throw std::invalid_argument("Quantity is not a valid number: " + quantityStr);

        int quantity = std::stoi(numPart);
        if (quantity <= 0)
            throw std::invalid_argument("Quantity must be greater than zero");

        return quantity;
    }
}
