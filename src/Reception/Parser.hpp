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
#include "Order.hpp"

namespace Plazza {
    /**
     * @class Parser
     * Class responsible for parsing commands from the input.
     */
    class Parser {
    public:
        /**
         * @class ParserException
         * Exception class for handling parsing errors.
         * Inherits from std::exception.
         */
        class ParserException : public std::exception {
        public:
            /**
             * Constructor to initialize the exception with a message.
             * @param what The error message
             */
            ParserException(const std::string &what) : _message(what) {}
            /**
             * Get the error message.
             * @return The error message
             */
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message; ///> Error message
        };
        /**
         * Parser constructor.
         * Initializes the parser with default values.
         */
        Parser() = default;
        /**
         * Parse function
         * @param input The input string to parse
         * @return A vector of Command objects
         */
        std::vector<Order> parse(const std::string& input);
        /**
         * Parse a command from a line.
         * @param line The line to parse
         * @return A Command object
         */
        Order parseCommand(const std::string& line);

    };
}



#endif //PARSER_HPP
