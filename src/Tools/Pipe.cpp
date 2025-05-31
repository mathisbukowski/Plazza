/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "Pipe.hpp"
#include <sys/socket.h>
#include "Factory/MessageFactory.hpp"
#include "Message/PingMessage.hpp"

namespace Plazza {
    PipeChannel::PipeChannel() : _fds{-1, -1}, _isConnected(false), _messageCounter(0) {
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, _fds) == -1) {
            throw std::runtime_error("PipeChannel::socketpair() failed");
        }
        _isConnected = true;
        _lastActivity = std::chrono::steady_clock::now();
    }

    PipeChannel::~PipeChannel() {
        closeIfOpen(_fds[0]);
        closeIfOpen(_fds[1]);
        _isConnected = false;
    }

    PipeChannel::PipeChannel(PipeChannel&& other) noexcept {
        _fds[0] = other._fds[0];
        _fds[1] = other._fds[1];
        other._fds[0] = -1;
        other._fds[1] = -1;
        _isConnected.store(other._isConnected.load());
        _messageCounter.store(other._messageCounter.load());
        _messagesSent.store(other._messagesSent.load());
        _messagesReceived.store(other._messagesReceived.load());
        _lastActivity = other._lastActivity;
        other._isConnected = false;
    }

    PipeChannel& PipeChannel::operator=(PipeChannel&& other) noexcept {
        if (this != &other) {
            closeIfOpen(_fds[0]);
            closeIfOpen(_fds[1]);

            _fds[0] = other._fds[0];
            _fds[1] = other._fds[1];
            other._fds[0] = -1;
            other._fds[1] = -1;
            _isConnected.store(other._isConnected.load());
            _messageCounter.store(other._messageCounter.load());
            _messagesSent.store(other._messagesSent.load());
            _messagesReceived.store(other._messagesReceived.load());
            _lastActivity = other._lastActivity;
            other._isConnected = false;
        }
        return *this;
    }

    void PipeChannel::closeIfOpen(int& fd) {
        if (fd != -1) {
            ::close(fd);
            fd = -1;
        }
    }

    int PipeChannel::getParentFd() const {
        return _fds[0];
    }

    int PipeChannel::getChildFd() const {
        return _fds[1];
    }

    void PipeChannel::closeChildFd() {
        closeIfOpen(_fds[1]);
    }

    void PipeChannel::closeParentFd() {
        closeIfOpen(_fds[0]);
    }

    bool PipeChannel::isConnected() const {
        return _isConnected.load() && (_fds[0] != -1 || _fds[1] != -1);
    }

    ssize_t PipeChannel::sendRawBuffer(int fd, const std::vector<char>& buffer) {
        if (fd == -1 || buffer.empty()) {
            return -1;
        }

        uint32_t messageSize = static_cast<uint32_t>(buffer.size());
        ssize_t sizeSent = ::write(fd, &messageSize, sizeof(messageSize));
        if (sizeSent != sizeof(messageSize)) {
            _isConnected = false;
            return -1;
        }
        ssize_t bytesSent = ::write(fd, buffer.data(), buffer.size());
        if (bytesSent != static_cast<ssize_t>(buffer.size())) {
            _isConnected = false;
            return -1;
        }

        _lastActivity = std::chrono::steady_clock::now();
        return bytesSent;
    }

    ssize_t PipeChannel::receiveRawBuffer(int fd, std::vector<char>& buffer, int timeoutMs) {
        if (fd == -1) {
            return -1;
        }

        if (timeoutMs > 0) {
            struct timeval timeout;
            timeout.tv_sec = timeoutMs / 1000;
            timeout.tv_usec = (timeoutMs % 1000) * 1000;

            fd_set readSet;
            FD_ZERO(&readSet);
            FD_SET(fd, &readSet);

            int result = select(fd + 1, &readSet, nullptr, nullptr, &timeout);
            if (result <= 0) {
                return result;
            }
        }

        uint32_t messageSize;
        ssize_t sizeRead = ::read(fd, &messageSize, sizeof(messageSize));
        if (sizeRead != sizeof(messageSize)) {
            if (sizeRead == 0) {
                _isConnected = false;
            }
            return sizeRead;
        }

        if (messageSize == 0 || messageSize > 65536) {
            return -1;
        }
        buffer.resize(messageSize);
        ssize_t bytesRead = ::read(fd, buffer.data(), messageSize);
        if (bytesRead != static_cast<ssize_t>(messageSize)) {
            _isConnected = false;
            return -1;
        }

        _lastActivity = std::chrono::steady_clock::now();
        return bytesRead;
    }

    bool PipeChannel::sendToChild(const IMessage& message) {
        std::lock_guard<std::mutex> lock(_sendMutex);

        std::vector<char> buffer;
        try {
            message.serialize(buffer);
            ssize_t sent = sendRawBuffer(_fds[1], buffer);
            if (sent > 0) {
                ++_messagesSent;
                return true;
            }
        } catch (const std::exception&) {
            // Serialization error
        }
        return false;
    }

    bool PipeChannel::sendToParent(const IMessage& message) {
        std::lock_guard<std::mutex> lock(_sendMutex);

        std::vector<char> buffer;
        try {
            message.serialize(buffer);
            ssize_t sent = sendRawBuffer(_fds[0], buffer);
            if (sent > 0) {
                ++_messagesSent;
                return true;
            }
        } catch (const std::exception&) {
            // Serialization error
        }
        return false;
    }

    std::unique_ptr<IMessage> PipeChannel::receiveFromChild(int timeoutMs) {
        std::lock_guard<std::mutex> lock(_receiveMutex);

        std::vector<char> buffer;
        ssize_t received = receiveRawBuffer(_fds[1], buffer, timeoutMs);

        if (received > 0) {
            try {
                auto message = MessageFactory::createMessage(buffer);
                ++_messagesReceived;
                return message;
            } catch (const std::exception&) {
                std::cerr << "errror" << std::endl;
            }
        }
        return nullptr;
    }

    std::unique_ptr<IMessage> PipeChannel::receiveFromParent(int timeoutMs) {
        std::lock_guard<std::mutex> lock(_receiveMutex);

        std::vector<char> buffer;
        ssize_t received = receiveRawBuffer(_fds[0], buffer, timeoutMs);

        if (received > 0) {
            try {
                auto message = MessageFactory::createMessage(buffer);
                ++_messagesReceived;
                return message;
            } catch (const std::exception&) {
                std::cerr << "receiveFromParent receiveFromParent failed" << std::endl;
            }
        }
        return nullptr;
    }

    PipeChannel& PipeChannel::operator<<(const IMessage& message) {
        if (_fds[1] != -1) {
            sendToChild(message);
        } else if (_fds[0] != -1) {
            sendToParent(message);
        }
        return *this;
    }

    PipeChannel& PipeChannel::operator>>(std::unique_ptr<IMessage>& message) {
        if (_fds[1] != -1) {
            message = receiveFromChild(0);
        } else if (_fds[0] != -1) {
            message = receiveFromParent(0);
        } else {
            message = nullptr;
        }
        return *this;
    }

    bool PipeChannel::testConnection(int timeoutMs) {
        PingMessage heartbeat(std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count());
        if (!sendToChild(heartbeat)) {
            return false;
        }

        auto response = receiveFromChild(timeoutMs);
        return response && response->getType() == MessageType::HEARTBEAT;
    }

}