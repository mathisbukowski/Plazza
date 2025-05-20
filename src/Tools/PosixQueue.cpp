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

#include "Factory/IpcMessageFactory.hpp"

namespace Plazza {
    PosixQueue::PosixQueue(const std::string& name, bool create, mode_t mode)
    : _queue((mqd_t)-1), _name("/" + name), _created(create)
    {
        mq_attr attr{};
        attr.mq_maxmsg = MAX_MESSAGES;
        attr.mq_msgsize = MAX_MSG_SIZE;
        attr.mq_flags = 0;

        _queue = mq_open(_name.c_str(), (create ? O_CREAT : 0) | O_RDWR, mode, &attr);
        if (_queue == (mqd_t)-1)
            throw std::runtime_error("mq_open() failed for " + _name);
    }

    PosixQueue::~PosixQueue() {
        if (_queue != (mqd_t)-1) {
            mq_close(_queue);
            if (_created)
                mq_unlink(_name.c_str());
        }
    }

    bool PosixQueue::sendBuffer(const std::vector<char>& buffer, unsigned int priority) {
        if (_queue == (mqd_t)-1 || buffer.size() > MAX_MSG_SIZE)
            return false;
        return mq_send(_queue, buffer.data(), buffer.size(), priority) == 0;
    }

    bool PosixQueue::receiveBuffer(std::vector<char>& buffer, size_t& sizeReceived, unsigned int& priority) {
        buffer.resize(MAX_MSG_SIZE);
        ssize_t received = mq_receive(_queue, buffer.data(), MAX_MSG_SIZE, &priority);
        if (received < 0)
            return false;
        sizeReceived = static_cast<size_t>(received);
        buffer.resize(sizeReceived);
        return true;
    }

    bool PosixQueue::sendMessage(const std::unique_ptr<Message>& msg, unsigned int priority) {
        std::vector<char> buffer(msg->getPackedSize());
        size_t packedSize = 0;
        msg->serialize(buffer.data(), packedSize);
        buffer.resize(packedSize);
        return sendBuffer(buffer, priority);
    }

    std::unique_ptr<Message> PosixQueue::receiveMessage(unsigned int& priority) {
        std::vector<char> buffer;
        size_t sizeReceived;
        if (!receiveBuffer(buffer, sizeReceived, priority))
            return nullptr;
        if (sizeReceived < sizeof(MessageType))
            return nullptr;
        MessageType type;
        std::memcpy(&type, buffer.data(), sizeof(MessageType));
        std::unique_ptr<Message> msg = IpcMessageFactory::create(type);
        if (msg)
            msg->deserialize(buffer.data(), sizeReceived);
        return msg;
    }

    void PosixQueue::unlink(const std::string& name) {
        mq_unlink(("/" + name).c_str());
    }

}
