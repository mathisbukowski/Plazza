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


namespace Plazza
{
    class Reception
    {
        public:
            Reception();
            ~Reception();
            void start();
            void stop();
            void addOrder(const std::string &order);
            void processOrders();

        private:
            bool _running;
            std::vector<std::string> _orders;
    };
}

#endif /* !RECEPTION_HPP_ */
