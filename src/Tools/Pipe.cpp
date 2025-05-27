/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "Pipe.hpp"
#include <sys/socket.h>

#include "Message/KitchenClosingMessage.hpp"
#include "Message/OrderMessage.hpp"
#include "Message/ReceiveStatusMessage.hpp"
#include "Message/StatusMessage.hpp"
#include <limits>

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
        uint8_t byteType;
        ssize_t bytesReceived = ::read(fd, &byteType, sizeof(byteType));
        if (bytesReceived <= 0)
            return nullptr;

        auto typeMessage = static_cast<MessageType>(byteType);
        std::shared_ptr<IMessage> message = createMessage(typeMessage);

        char buffer[4096];
        buffer[0] = byteType;
        ssize_t lengthReceived = ::read(fd, buffer + 1, 4096 - 1);
        if (lengthReceived <= 0)
            return nullptr;
        std::string data(buffer, lengthReceived + 1);
        try {
            message->deserialize(data);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return nullptr;
        }
        return message;
    }

    std::shared_ptr<IMessage> PipeChannel::createMessage(MessageType messageType)
    {
        switch (messageType) {
        case MessageType::KITCHEN_CLOSING:
            return std::make_shared<KitchenClosing>(static_cast<uint8_t>(messageType));
        case MessageType::STATUS:
            return std::make_shared<StatusMessage>(static_cast<uint8_t>(messageType));
        case MessageType::ORDER:
            return std::make_shared<OrderMessage>(static_cast<uint8_t>(messageType));
        case MessageType::RECEIVE_STATUS:
            return std::make_shared<ReceiveStatusMessage>(static_cast<uint8_t>(messageType));
        default:
            return nullptr;
        }
    }

    bool PipeChannel::send(int fd, const IMessage& message)
    {
        std::string buffer;
        message.serialize(buffer);
        ssize_t bytesSent = ::write(fd, buffer.c_str(), buffer.size());
        return bytesSent == static_cast<ssize_t>(buffer.size());
    }

}
