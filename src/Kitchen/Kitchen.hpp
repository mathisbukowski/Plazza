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


namespace Plazza {
    class Kitchen {
        public:
            Kitchen();
            ~Kitchen();
            void start();
            void stop();
        private:
            std::mutex _mutex;
            std::thread _thread;
    };
}

#endif //PLAZZA_KITCHEN_HPP
