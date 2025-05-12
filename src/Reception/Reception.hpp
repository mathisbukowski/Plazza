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

namespace Plazza
{
    class Reception
    {
        public:
            class ReceptionException : public std::exception {
                public:
                ReceptionException(const std::string &what) : message(what) {}
                virtual ~ReceptionException() = default;
                const char *what() const noexcept override { return message.c_str(); }
                private:
                    std::string message;
            };
            Reception() = default;
            ~Reception();
            int run();
            void addKitchen(pid_t pid);
            void createKitchen();

        private:
            bool _running = false;
            std::vector<pid_t> _kitchens;
            std::unique_ptr<int> _status = nullptr;
    };
}

#endif /* !RECEPTION_HPP_ */
