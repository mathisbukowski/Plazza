/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef IBUILDER_HPP
#define IBUILDER_HPP

namespace Plazza {
    /**
     * @class IBuilder
     * Interface for a builder pattern.
     * This interface defines a method to build an object of type ClassType.
     * @tparam ClassType The type of object to be built.
     */
    template <typename ClassType>
    class IBuilder {
    public:
        /**
         * Virtual destructor for the builder interface.
         * Ensures proper cleanup of derived classes.
         */
        virtual ~IBuilder() = default;
        /**
         * Pure virtual method to build an object of type ClassType.
         * Derived classes must implement this method to provide the specific building logic.
         * @return An instance of ClassType.
         */
        virtual ClassType build() = 0;
    };
}

#endif //IBUILDER_HPP
