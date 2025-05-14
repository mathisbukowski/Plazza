/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "plazza.hpp"
#include <vector>
#include <memory>

#include "Parser.hpp"
#include "Tools/ForkEntity.hpp"

namespace Plazza
{
    /**
     * @class Reception
     * Class responsible for managing the reception of orders and interacting with kitchens.
     */
    class Reception
    {
        public:
            /**
             * @class ReceptionException
             * Exception class for handling reception errors.
             * Inherits from std::exception.
             */
            class ReceptionException : public std::exception {
                public:
                /**
                 * Constructor to initialize the exception with a message.
                 * @param what The error message
                 */
                ReceptionException(const std::string &what) : message(what) {}
                /**
                 * Destructor for the exception.
                 */
                virtual ~ReceptionException() = default;
                /**
                 * Get the error message.
                 * @return The error message
                 */
                const char *what() const noexcept override { return message.c_str(); }
                private:
                    std::string message; ///> Error message
            };
            /**
             * Reception constructor.
             * Initializes the reception with default values.
             */
            Reception() = default;
            /**
             * Reception Destructor.
             */
            ~Reception();
            /**
             * Start the reception process.
             * @return 0 on success, -1 on failure
             */
            int run();
            /**
             * Add a kitchen to the reception.
             * @param entity The kitchen entity to add
             */
            void addKitchen(std::unique_ptr<ForkEntity> entity);
            /**
             * create a new kitchen.
             */
            void createKitchen();
            /**
             * handle input from the user.
             * @param input The input string to handle
             */
            void handleInput(const std::string& input);
            /**
             * handle the status of the kitchens.
             */
            void handleStatus();

        private:
            bool _running = false; ///> Flag to indicate if the reception is running
            std::vector<std::unique_ptr<ForkEntity>> _kitchens; ///> Vector of kitchen entities
            std::unique_ptr<int> _status = nullptr; ///> Pointer to the status of the kitchens
            std::shared_ptr<Parser> _parser = std::make_shared<Parser>(); ///> Shared pointer to the parser
    };
}

#endif /* !RECEPTION_HPP_ */
