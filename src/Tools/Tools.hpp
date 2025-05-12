/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <memory>

namespace Plazza {
    /**
     * @class Tools
     * A class that provides encasulation for system calls;
     */
    class Tools {
    public:
        /**
         * Forks the current process.
         * @return The process ID of the child process.
         */
        static int toolFork();
        /**
         * Waits for a child process to terminate.
         * @param pid The process ID of the child process.
         * @param status A pointer to an integer where the exit status will be stored.
         * @return The process ID of the terminated child process.
         */
        static int toolWaitPid(pid_t pid, std::unique_ptr<int> &status);
        /**
         * Gets the process ID of the current process.
         * @return The process ID of the current process.
         */
        static pid_t toolGetPid();
        /**
         * Gets the process ID of the parent process.
         * @return The process ID of the parent process.
         */
        static pid_t toolGetPPid();

    };
}

#endif //TOOLS_HPP
