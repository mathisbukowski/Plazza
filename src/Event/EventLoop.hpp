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
    class EventLoop {
    public:
        void addSelectable(std::shared_ptr<ISelectable> selectable);

        void removeSelectable(int fd);

        void pollOnce(int timeoutMs = 1000);

        void run(int timeoutMs = 1000);
    private:
        std::unordered_map<int, std::shared_ptr<ISelectable>> _selectables;
    };
}

#endif //EVENTLOOP_HPP
