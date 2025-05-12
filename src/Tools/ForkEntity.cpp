/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "ForkEntity.hpp"
#include <sys/wait.h>
#include <iostream>
#include <stdexcept>

namespace Plazza {

    ForkEntity::ForkEntity()
        : _parentPid(getpid()), _childPid(fork()), _exitStatus(std::nullopt)
    {
        if (_childPid < 0)
            throw std::runtime_error("Fork failed");
    }

    bool ForkEntity::isParent() const {
        return _childPid > 0;
    }

    bool ForkEntity::isChild() const {
        return _childPid == 0;
    }

    pid_t ForkEntity::getParentPid() const {
        return _parentPid;
    }

    pid_t ForkEntity::getChildPid() const {
        return _childPid;
    }

    int ForkEntity::waitChild() {
        if (!isParent())
            throw std::logic_error("Only parent can wait for child");

        int status = 0;
        if (waitpid(_childPid, &status, 0) == -1)
            throw std::runtime_error("waitpid failed");

        _exitStatus = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
        return *_exitStatus;
    }

    std::optional<int> ForkEntity::getExitStatus() const {
        return _exitStatus;
    }

}