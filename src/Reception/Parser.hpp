/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include "plazza.hpp"
#include <vector>
#include "Command.hpp"

namespace Plazza {
    class Parser {
    public:
        class ParserException : public std::exception {
        public:
            ParserException(const std::string &what) : _message(what) {}
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
        };

        Parser() = default;
        std::vector<Command> parse(const std::string& input);
        Command parseCommand(const std::string& line);

    };
}



#endif //PARSER_HPP
