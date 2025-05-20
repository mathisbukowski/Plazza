/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "Parser.hpp"
#include <sstream>

#include "Order.hpp"
#include "Tools/ResultException.hpp"

// Example of parsing = regina XXL x2; fantasia M x3; margarita S x1

namespace Plazza {
    std::vector<Order> Parser::parse(const std::string& input)
    {
        if (input.empty())
            throw ParserException("Empty input string");

        std::vector<std::string> lines;
        std::stringstream ss(input);
        std::string command;

        while (std::getline(ss, command, ';')) {
            if (!command.empty())
                lines.push_back(command);
        }
        std::vector<Order> commands;
        for (const auto& line : lines) {
            auto command = handleExceptions([&](const std::string& str) {
                return this->parseCommand(str);
            }, line);
            if (command.hasValue())
                commands.push_back(command.getValue());
            else
                throw ParserException(command.getErrorMessage());
        }
        return commands;
    }

    Order Parser::parseCommand(const std::string& line)
    {
        std::stringstream ss(line);
        std::string pizzaType, pizzaSize, pizzaCount;

        ss >> pizzaType >> pizzaSize >> pizzaCount;

        if (pizzaType.empty() || pizzaSize.empty() || pizzaCount.empty())
            throw ParserException("Invalid command format");
        Order command;

        try {
            command.pizzaSize = command.stringToPizzaSize(pizzaSize);
            command.pizzaType = command.stringToPizzaType(pizzaType);
            command.numberOfPizzasNeeded = command.parseQuantity(pizzaCount);
        } catch (const std::invalid_argument& e) {
            throw ParserException(e.what());
        }
        return command;
    }


}