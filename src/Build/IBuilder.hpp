/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef IBUILDER_HPP
#define IBUILDER_HPP

namespace Plazza {
    template <typename ClassType>
    class IBuilder {
    public:
        virtual ~IBuilder() = default;
        virtual ClassType build() = 0;
    };
}

#endif //IBUILDER_HPP
