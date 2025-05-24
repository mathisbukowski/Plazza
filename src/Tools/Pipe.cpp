/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "Pipe.hpp"
#include <sys/socket.h>

namespace Plazza {
    PipeChannel::PipeChannel()
    {
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, _fds) == -1)
            throw std::runtime_error("PipeChannel::socketpair() failed");
    }
    PipeChannel::~PipeChannel()
    {
        this->closeIfOpen(_fds[0]);
        this->closeIfOpen(_fds[1]);
    }

    int PipeChannel::getParentFd() const
    {
        return _fds[0];
    }

    int PipeChannel::getChildFd() const
    {
        return _fds[1];
    }

    void PipeChannel::closeChildFd()
    {
        this->closeIfOpen(_fds[1]);
    }

    void PipeChannel::closeParentFd()
    {
        this->closeIfOpen(_fds[0]);
    }

    void PipeChannel::closeIfOpen(int& fd)
    {
        if (fd != -1) {
            ::close(fd);
            fd = -1;
        }
    }





}