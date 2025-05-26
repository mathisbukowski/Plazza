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
            /**
             * @class KitchenChannel
             * Class representing a channel to communicate with a kitchen.
             */
            class KitchenChannel {
            public:
                std::unique_ptr<ForkEntity> _fork; ///> Unique pointer to the fork entity for process management
                std::shared_ptr<PipeChannel> _pipe; ///> Shared pointer to the pipe channel for communication
                /**
                 * Constructor for KitchenChannel.
                 * @param _fork Unique pointer to the fork entity
                 * @param _pipe Shared pointer to the pipe channel
                 * Initializes the kitchen channel with the provided fork and pipe.
                 */
                KitchenChannel(std::unique_ptr<ForkEntity> _fork, std::shared_ptr<PipeChannel> _pipe):
                _fork(std::move(_fork)), _pipe(std::move(_pipe)) {}
            };
            /**
             * @class KitchenStatus
             * Class representing the status of a kitchen.
             */
            class KitchenStatus {
            public:
                int _totalCooks = 0; ///> Total number of cooks in the kitchen
                int _busyCooks = 0; ///> Number of busy cooks
                std::array<int, IngredientCount> _stock{}; ///> Array to hold stock quantities of ingredients
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
            Reception(const double& multiplier, const int& numberOfCooks, const int& timePerRestock):
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
            double _multiplierCookingTime = 0; ///> Int to represent the multiplier
            int _numberOfCooksPerKitchen = 0; ///> Int to represent the number of cooks
            int _timeToRestockIngredients = 0; ///> time to Restock
            std::vector<KitchenChannel> _kitchens; ///> Vector of kitchen channels
            EventLoop _pollLoop; ///> Event loop for handling events
            std::vector<KitchenStatus> _latestStatuses; ///> Vector to store the latest statuses of kitchens
            void receiveStatusFromKitchen(); ///> Function to receive status from kitchens

    };
}

#endif /* !RECEPTION_HPP_ */
