/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "EventLoop.hpp"
#include <poll.h>
#include <vector>

namespace Plazza {
    void EventLoop::addSelectable(std::shared_ptr<ISelectable> selectable)
    {
        int fd = selectable->getFd();
        _selectables[fd] = std::move(selectable);
    }

    void EventLoop::removeSelectable(int fd)
    {
        _selectables.erase(fd);
    }

    void EventLoop::pollOnce(int timeoutMs)
    {
        std::vector<struct pollfd> fds;
        for (const auto& [fd, selectable] : _selectables) {
            fds.push_back({fd, selectable->getPollEvents(), 0});
        }

        if (fds.empty())
            return;
        int ret = ::poll(fds.data(), fds.size(), timeoutMs);
        if (ret < 0)
            throw std::runtime_error("poll failed");
        for (const auto& pdf: fds) {
            if (pdf.revents != 0) {
                auto it = _selectables.find(pdf.fd);
                if (it != _selectables.end())
                    it->second->onEvent(pdf.revents);
            }
        }
    }

    void EventLoop::run(int timeoutMs)
    {
        while (true) {
            this->pollOnce(timeoutMs);
        }
    }



}
