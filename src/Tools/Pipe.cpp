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
        uint32_t size;
        if (::read(fd, &size, sizeof(size)) != sizeof(size))
            return nullptr;

        std::vector<char> buffer(size);
        if (::read(fd, buffer.data(), size) != static_cast<ssize_t>(size))
            return nullptr;

        auto byteType = static_cast<uint8_t>(buffer[0]);
        auto message = createMessage(static_cast<MessageType>(byteType));
        if (!message)
            return nullptr;

        try {
            message->deserialize(std::string(buffer.begin(), buffer.end()));
        } catch (const std::exception& e) {
            std::cerr << "Deserialization error: " << e.what() << std::endl;
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

        uint32_t size = buffer.size();
        if (::write(fd, &size, sizeof(size)) != sizeof(size))
            return false;
        if (::write(fd, buffer.c_str(), buffer.size()) != static_cast<ssize_t>(buffer.size()))
            return false;
        return true;
    }

}
