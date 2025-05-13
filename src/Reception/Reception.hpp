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
            void addKitchen(std::unique_ptr<ForkEntity> entity);
            void createKitchen();
            void handleInput(const std::string& input);

        private:
            bool _running = false;
            std::vector<std::unique_ptr<ForkEntity>> _kitchens;
            std::unique_ptr<int> _status = nullptr;
            std::shared_ptr<Parser> _parser = std::make_shared<Parser>();
    };
}

#endif /* !RECEPTION_HPP_ */
