/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "Parser.hpp"
#include <sstream>

#include "Command.hpp"

// Example of parsing = regina XXL x2; fantasia M x3; margarita S x1

namespace Plazza {
    std::vector<Command> Parser::parse(const std::string& input)
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
        std::vector<Command> commands;
        for (const auto& line : lines) {
            auto command = this->parseCommand(line);
            commands.push_back(command);
        }
        return commands;
    }

    Command Parser::parseCommand(const std::string& line)
    {
        std::stringstream ss(line);
        std::string pizzaType, pizzaSize, pizzaCount;

        ss >> pizzaType >> pizzaSize >> pizzaCount;

        if (pizzaType.empty() || pizzaSize.empty() || pizzaCount.empty())
            throw ParserException("Invalid command format");
        Command command;

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