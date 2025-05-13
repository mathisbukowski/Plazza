/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "PosixQueue.hpp"
#include <stdexcept>
#include <cstring>
#include <vector>

namespace Plazza {
    PosixQueue::PosixQueue(const std::string& name, bool create, size_t maxMsgSize):
    _name(name), _created(create), _maxMsgSize(maxMsgSize), _queue(-1)
    {
        mq_attr attr = {};
        attr.mq_msgsize = maxMsgSize;
        attr.mq_flags = 0;
        attr.mq_maxmsg = 20;

        int flags = O_RDWR;
        if (create)
            flags |= O_CREAT;
        _queue = mq_open(name.c_str(), flags, 0644, create ? &attr : nullptr);
        if (_queue == -1)
            throw std::runtime_error("Failed to open message queue: " + std::string(strerror(errno)));
    }

    PosixQueue::~PosixQueue()
    {
        this->closeQueue();
        if (_created)
            this->unlinkQueue();
    }

    void PosixQueue::closeQueue()
    {
        if (_queue != -1)
            mq_close(_queue);
    }

    void PosixQueue::unlinkQueue()
    {
        mq_unlink(_name.c_str());
    }

    void PosixQueue::send(const std::string& message, unsigned int priority)
    {
        if (message.size() > _maxMsgSize)
            throw std::runtime_error("Message is too big to send");
        if (mq_send(_queue, message.c_str(), message.size(), priority) == -1)
            throw std::runtime_error("Failed to send message" + std::string(strerror(errno)));
    }

    std::string PosixQueue::receive(std::unique_ptr<unsigned int> priority)
    {
        std::vector<char> buffer(_maxMsgSize);
        ssize_t bytesRead = mq_receive(_queue, buffer.data(), _maxMsgSize, priority.get());

        if (bytesRead == -1)
            throw std::runtime_error("Failed to receive message" + std::string(strerror(errno)));
        return std::string(buffer.data(), bytesRead);
    }



}
