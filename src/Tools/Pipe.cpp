/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "Pipe.hpp"
#include <iostream>
#include <sstream>
#include <sys/socket.h>

namespace Plazza {

    PipeChannel::PipeChannel(pid_t kitchenPid, bool isReception)
            : _readFd(-1), _writeFd(-1), _isReception(isReception),
              _kitchenPid(kitchenPid), _pipesCreated(isReception)
    {
        this->generatePipeNames();
        if (_pipesCreated) {
            this->createPipe(_receptionToCookPipe);
            this->createPipe(_cookToReceptionPipe);
        }
    }

    PipeChannel::PipeChannel()
            : _readFd(-1), _writeFd(-1), _isReception(true),
              _kitchenPid(getpid()), _pipesCreated(true)
    {
        int fds[2];
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1)
            throw std::runtime_error("PipeChannel::socketpair() failed");
        _readFd = fds[0];
        _writeFd = fds[1];
    }

    PipeChannel::~PipeChannel()
    {
        this->closeAll();

        if (_pipesCreated && !_receptionToCookPipe.empty()) {
            this->removePipe(_receptionToCookPipe);
            this->removePipe(_cookToReceptionPipe);
        }
    }

    PipeChannel::PipeChannel(PipeChannel&& other) noexcept
            : _receptionToCookPipe(std::move(other._receptionToCookPipe)),
              _cookToReceptionPipe(std::move(other._cookToReceptionPipe)),
              _readFd(other._readFd),
              _writeFd(other._writeFd),
              _isReception(other._isReception),
              _kitchenPid(other._kitchenPid),
              _pipesCreated(other._pipesCreated)
    {
        other._readFd = -1;
        other._writeFd = -1;
        other._pipesCreated = false;
    }

    PipeChannel& PipeChannel::operator=(PipeChannel&& other) noexcept
    {
        if (this != &other) {
            this->closeAll();

            _receptionToCookPipe = std::move(other._receptionToCookPipe);
            _cookToReceptionPipe = std::move(other._cookToReceptionPipe);
            _readFd = other._readFd;
            _writeFd = other._writeFd;
            _isReception = other._isReception;
            _kitchenPid = other._kitchenPid;
            _pipesCreated = other._pipesCreated;

            other._readFd = -1;
            other._writeFd = -1;
            other._pipesCreated = false;
        }
        return *this;
    }

    void PipeChannel::generatePipeNames()
    {
        std::ostringstream oss1, oss2;
        oss1 << "/tmp/plazza_to_kitchen_" << _kitchenPid;
        oss2 << "/tmp/kitchen_to_plazza_" << _kitchenPid;

        _receptionToCookPipe = oss1.str();
        _cookToReceptionPipe = oss2.str();
    }

    void PipeChannel::createPipe(const std::string& pipeName)
    {
        if (mkfifo(pipeName.c_str(), 0666) == -1) {
            if (errno != EEXIST) {
                throw std::runtime_error("Failed to create named pipe: " + pipeName);
            }
        }
    }

    void PipeChannel::removePipe(const std::string& pipeName)
    {
        unlink(pipeName.c_str());
    }

    int PipeChannel::getParentFd() const
    {
        return _isReception ? _readFd : _writeFd;
    }

    int PipeChannel::getChildFd() const
    {
        return _isReception ? _writeFd : _readFd;
    }

    void PipeChannel::openForReception()
    {
        if (_receptionToCookPipe.empty()) {
            throw std::runtime_error("Pipe names not initialized");
        }
        _writeFd = open(_receptionToCookPipe.c_str(), O_WRONLY | O_NONBLOCK);
        if (_writeFd == -1) {
            throw std::runtime_error("Failed to open pipe for writing: " + _receptionToCookPipe);
        }
        _readFd = open(_cookToReceptionPipe.c_str(), O_RDONLY | O_NONBLOCK);
        if (_readFd == -1) {
            this->closeIfOpen(_writeFd);
            throw std::runtime_error("Failed to open pipe for reading: " + _cookToReceptionPipe);
        }
    }

    void PipeChannel::openForKitchen()
    {
        if (_receptionToCookPipe.empty()) {
            throw std::runtime_error("Pipe names not initialized");
        }
        _readFd = open(_receptionToCookPipe.c_str(), O_RDONLY);
        if (_readFd == -1) {
            throw std::runtime_error("Failed to open pipe for reading: " + _receptionToCookPipe);
        }
        _writeFd = open(_cookToReceptionPipe.c_str(), O_WRONLY);
        if (_writeFd == -1) {
            this->closeIfOpen(_readFd);
            throw std::runtime_error("Failed to open pipe for writing: " + _cookToReceptionPipe);
        }
    }

    void PipeChannel::closeParentFd()
    {
        if (_isReception) {
            this->closeIfOpen(_readFd);
        } else {
            this->closeIfOpen(_writeFd);
        }
    }

    void PipeChannel::closeChildFd()
    {
        if (_isReception) {
            this->closeIfOpen(_writeFd);
        } else {
            this->closeIfOpen(_readFd);
        }
    }

    void PipeChannel::closeAll()
    {
        this->closeIfOpen(_readFd);
        this->closeIfOpen(_writeFd);
    }

    void PipeChannel::closeIfOpen(int& fd)
    {
        if (fd != -1) {
            ::close(fd);
            fd = -1;
        }
    }

    void PipeChannel::writeInChannel(int& fd, std::vector<char> data)
    {
        if (fd == -1) {
            throw std::runtime_error("Invalid file descriptor for writeInChannel");
        }

        if (::write(fd, data.data(), data.size()) != static_cast<ssize_t>(data.size())) {
            throw std::runtime_error("Failed to write data to channel");
        }
    }

    void PipeChannel::setFds(int readFd, int writeFd) {
        _readFd = readFd;
        _writeFd = writeFd;
    }
}