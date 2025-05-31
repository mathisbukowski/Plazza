/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef MESSAGEFACTORY_HPP
#define MESSAGEFACTORY_HPP

#include "Message/IMessage.hpp"
#include <memory>

namespace Plazza {
    class MessageFactory {
    public:
        static std::unique_ptr<IMessage> createMessage(const std::vector<char>& buffer);
    };
}



#endif //MESSAGEFACTORY_HPP
