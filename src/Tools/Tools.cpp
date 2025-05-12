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
            static int toolFork() {
                int pid = fork();

                if (pid == -1) {
                    std::cerr << "Fork failed!" << std::endl;
                    std::exit(EXIT_FAILURE);
                }
                return pid;
            }
            /**
             * Waits for a child process to terminate.
             * @param pid The process ID of the child process.
             * @param status A pointer to an integer where the exit status will be stored.
             * @return The process ID of the terminated child process.
             */
            static int toolWaitPid(pid_t pid, std::unique_ptr<int> &status) {
                
                int result = waitpid(pid, status.get(), 0);
                if (result == -1) {
                    std::cerr << "Waitpid failed!" << std::endl;
                    return -1;
                }
                return result;
            }
            /**
             * Gets the process ID of the current process.
             * @return The process ID of the current process.
             */
            static pid_t toolGetPid() {
                return getpid();
            }
            /**
             * Gets the process ID of the parent process.
             * @return The process ID of the parent process.
             */
            static pid_t toolGetPPid() {
                return getppid();
            }

    };
}
