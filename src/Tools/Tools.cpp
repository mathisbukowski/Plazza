/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Tools
*/

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <memory>
#include "Tools.hpp"

namespace Plazza {
    int toolFork() {
        int pid = fork();

        if (pid == -1) {
            std::cerr << "Fork failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return pid;
    }

    int toolWaitPid(pid_t pid, std::unique_ptr<int> &status) {

        int result = waitpid(pid, status.get(), 0);
        if (result == -1) {
            std::cerr << "Waitpid failed!" << std::endl;
            return -1;
        }
        return result;
    }

    pid_t toolGetPid() {
        return getpid();
    }

    pid_t toolGetPPid() {
        return getppid();
    }
}
