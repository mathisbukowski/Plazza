/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <utility>
#include <vector>
#include <memory>

#include "Parser.hpp"
#include "Event/EventLoop.hpp"
#include "Kitchen/Stock.hpp"
#include "Pizza/IPizza.hpp"
#include "Tools/ForkEntity.hpp"
#include "Tools/Pipe.hpp"

namespace Plazza
{
    class PosixQueue;
    /**
     * @class Reception
     * Class responsible for managing the reception of orders and interacting with kitchens.
     */
    class Reception
    {
        public:
            class KitchenChannel {
            public:
                std::unique_ptr<ForkEntity> _fork;
                std::shared_ptr<PipeChannel> _pipe;
                KitchenChannel(std::unique_ptr<ForkEntity> _fork, std::shared_ptr<PipeChannel> _pipe):
                _fork(std::move(_fork)), _pipe(std::move(_pipe)) {}
            };

            class KitchenStatus {
            public:
                int _totalCooks = 0;
                int _busyCooks = 0;
                std::array<int, IngredientCount> _stock{};
            };
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
            Reception(const int& multiplier, const int& numberOfCooks, const int& timePerRestock):
            _multiplierCookingTime(multiplier), _numberOfCooksPerKitchen(numberOfCooks), _timeToRestockIngredients(timePerRestock) {}
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
            /**
             * dispatch commands to all kitchen
             * @param pizzas: array of commands to dispatch
             */
            void dispatchCommandsToKitchen(std::vector<std::shared_ptr<IPizza>> pizzas);

        private:
            bool _running = false; ///> Flag to indicate if the reception is running
            std::unique_ptr<int> _status = nullptr; ///> Pointer to the status of the kitchens
            std::shared_ptr<Parser> _parser = std::make_shared<Parser>(); ///> Shared pointer to the parser
            int _multiplierCookingTime = 0; ///> Int to represent the multiplier
            int _numberOfCooksPerKitchen = 0; ///> Int to represent the number of cooks
            int _timeToRestockIngredients = 0; ///> time to Restock
            std::vector<KitchenChannel> _kitchens;
            EventLoop _pollLoop;
            std::vector<KitchenStatus> _latestStatuses;
            void receiveStatusFromKitchen();

    };
}

#endif /* !RECEPTION_HPP_ */
