/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef ISELECTABLE_HPP
#define ISELECTABLE_HPP

namespace Plazza {
    class ISelectable {
    public:
        virtual ~ISelectable() = default;
        virtual int getFd() const = 0;
        virtual short getPollEvents() const = 0;
        virtual void onEvent(short revents) = 0;
    };
}

#endif //ISELECTABLE_HPP
