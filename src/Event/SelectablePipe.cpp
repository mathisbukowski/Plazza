/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "SelectablePipe.hpp"

#include <poll.h>


namespace Plazza {
    SelectablePipe::SelectablePipe(std::shared_ptr<PipeChannel> pipe, std::function<void()> onReadable)
    {
        _pipeChannel = std::move(pipe);
        _onReadable = std::move(onReadable);
    }

    SelectablePipe::~SelectablePipe() = default;

    int SelectablePipe::getFd() const
    {
        return this->_pipeChannel->getParentFd();
    }

    short SelectablePipe::getPollEvents() const
    {
        return POLLIN;
    }

    void SelectablePipe::onEvent(short revents)
    {
        if (revents & POLLIN)
            this->_onReadable();
    }
}
