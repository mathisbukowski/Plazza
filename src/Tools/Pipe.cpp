/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "Pipe.hpp"
#include <sys/socket.h>

#include "Tools.hpp"

namespace Plazza {
    PipeChannel::PipeChannel()
    {
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, _fds) == -1)
            throw std::runtime_error("PipeChannel::socketpair() failed");
    }
    PipeChannel::~PipeChannel()
    {
        if (_fds[0] != -1) {
            ::close(_fds[0]);
            _fds[0] = -1;
        }
        if (_fds[1] != -1) {
            ::close(_fds[1]);
            _fds[1] = -1;
        }
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

    std::shared_ptr<IMessage> PipeChannel::receive(int fd)
    {
        uint32_t size = 0;
        ssize_t bytes = Tools::toolRead(fd, &size, sizeof(size));
        if (bytes != sizeof(size))
            throw std::runtime_error("failed to read from pipe");
        std::vector<char> buffer(size);
        bytes = Tools::toolRead(fd, buffer.data(), size);
        if (bytes != static_cast<ssize_t>(size))
            throw std::runtime_error("failed to read from pipe");
        std::shared_ptr<IMessage> message = std::make_shared<IMessage>();
        message->deserialize(buffer);
        return message;
    }

    void PipeChannel::send(int fd, const IMessage& message)
    {
        std::vector<char> buffer;
        message.serialize(buffer);
        uint32_t size = buffer.size();
        if (Tools::toolWrite(fd, &size, sizeof(size)) == -1)
            throw std::runtime_error("write failed");
        if (Tools::toolWrite(fd, buffer.data(), buffer.size()) == -1)
            throw std::runtime_error("write failed");
    }

}
