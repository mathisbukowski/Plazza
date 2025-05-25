/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef ISELECTABLE_HPP
#define ISELECTABLE_HPP

namespace Plazza {
    /**
     * @class ISelectable
     * Interface for selectable objects in the event loop.
     * This interface defines methods to get the file descriptor, poll events, and handle events.
     */
    class ISelectable {
    public:
        /**
         * Virtual destructor for the selectable interface.
         * Ensures proper cleanup of derived classes.
         */
        virtual ~ISelectable() = default;
        /**
         * Pure virtual method to get the file descriptor of the selectable object.
         * @return The file descriptor associated with the selectable object.
         */
        virtual int getFd() const = 0;
        /**
         * Pure virtual method to get the poll events for the selectable object.
         * This method should return the events that the selectable object is interested in.
         * @return A short representing the poll events (e.g., POLLIN, POLLOUT).
         */
        virtual short getPollEvents() const = 0;
        /**
         * Pure virtual method to handle events for the selectable object.
         * This method will be called when the selectable object has events to process.
         * @param revents The events that occurred, as returned by the poll function.
         */
        virtual void onEvent(short revents) = 0;
    };
}

#endif //ISELECTABLE_HPP
