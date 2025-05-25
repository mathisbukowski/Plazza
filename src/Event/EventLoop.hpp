/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP
#include <memory>
#include <unordered_map>
#include "ISelectable.hpp"

namespace Plazza {
    /**
     * @class EventLoop
     * This class manages a collection of selectable objects and provides methods to poll events.
     * It allows adding and removing selectable objects, and polling for events on them.
     */
    class EventLoop {
    public:
        /**
         * Adds a selectable object to the event loop.
         * @param selectable A shared pointer to the selectable object to be added.
         */
        void addSelectable(std::shared_ptr<ISelectable> selectable);
        /**
         * Removes a selectable object from the event loop by its file descriptor.
         * @param fd The file descriptor of the selectable object to be removed.
         */
        void removeSelectable(int fd);
        /**
         * Polls events on all selectable objects.
         * This method checks for events on the registered selectables and calls their event handlers.
         * @param timeoutMs The maximum time to wait for events, in milliseconds. Default is 1000 ms.
         */
        void pollOnce(int timeoutMs = 1000);
        /**
         * Runs the event loop, continuously polling for events.
         * This method will keep running until stopped or an exit condition is met.
         * @param timeoutMs The maximum time to wait for events, in milliseconds. Default is 1000 ms.
         */
        void run(int timeoutMs = 1000);
    private:
        std::unordered_map<int, std::shared_ptr<ISelectable>> _selectables; ///> A map of file descriptors to selectable objects.
    };
}

#endif //EVENTLOOP_HPP
