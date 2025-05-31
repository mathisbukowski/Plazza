/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Kitchen.hpp
*/

#ifndef PLAZZA_KITCHEN_HPP
#define PLAZZA_KITCHEN_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include <chrono>
#include "../Threadpool/ThreadPool.hpp"
#include "../Threadpool/CookTask.hpp"
#include "../Tools/Pipe.hpp"

#include "Stock.hpp"

namespace Plazza {
    /**
     * @class Kitchen
     * Class representing a kitchen that manages the stock and cooks pizzas.
     * It handles the number of cooks, the number of pizzas, and the restocking process.
     */
    class Kitchen {
    public:
        /**
         * Constructor to initialize the kitchen with another kitchen.
         * @param other The kitchen to copy
         */
        Kitchen(const Kitchen &other);
        /**
         * Constructor to initialize the kitchen with a number of cooks, restock time, and pipe channel.
         * @param numberOfCooks The number of cooks in the kitchen
         * @param timeToRestock The time to restock the kitchen
         * @param pipe Shared pointer to the pipe channel for communication
         * @param multiplier The cooking time multiplier
         */
        Kitchen(int numberOfCooks, int timeToRestock, std::shared_ptr<PipeChannel> pipe, int multiplier = 1);
        /**
         * Default destructor for the kitchen.
         */
        ~Kitchen();
        /**
         * Handle order messages
         * @return true if ok
         */
        bool handleOrder();
        /**
         * Start the kitchen and begin the restocking process.
         */
        void start();
        /**
         * Stop the kitchen and end the restocking process.
         */
        void stop();
        /**
         * Handle status requests from the reception.
         * This method sends the current status of the kitchen, including the number of cooks
         * and the stock of ingredients.
         * @return True if the status was handled successfully, false otherwise.
         */
        bool handleStatus();
        /**
         * Handle status request and send response back to reception.
         * @return True if the status request was handled successfully, false otherwise.
         */
        bool handleStatusRequest();

    private:
        int _numberOfCooks; ///> Number of cooks in the kitchen
        int _numberOfPizzas; ///> Number of pizzas in the kitchen
        Stock _stock; ///> Stock of ingredients in the kitchen
        bool _running; ///> Flag to indicate if the kitchen is running
        int _timeToRestock; ///> Time to restock the kitchen
        std::shared_ptr<PipeChannel> _pipe; ///> Shared pointer to pipe channel for communication
        std::unique_ptr<ThreadPool> _threadPool; ///> Thread pool for managing cooking tasks
        double _multiplier; ///> Cooking time multiplier
        static constexpr int STATUS_INTERVAL_MS = 1000; ///> Interval of status sending
    };
}

#endif //PLAZZA_KITCHEN_HPP
