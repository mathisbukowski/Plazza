/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef FORKENTITY_HPP
#define FORKENTITY_HPP

#include <sys/types.h>
#include <optional>
#include <string>

namespace Plazza {
    /**
     * @class ForkEntity
     * Class responsible for managing the fork process.
     */
    class ForkEntity {
    public:
        /**
         * Default constructor to initialize the fork entity.
         */
        ForkEntity();
        /**
         * Default destructor to clean up the fork entity.
         */
        ~ForkEntity() = default;

        /**
         * Is the current process the parent?
         * @return True if the current process is the parent, false otherwise
         */
        [[nodiscard]] bool isParent() const;
        /**
         * Is the current process the child?
         * @return True if the current process is the child, false otherwise
         */
        [[nodiscard]] bool isChild() const;

        /**
         * Gets the parent process ID.
         * @return The parent process ID
         */
        [[nodiscard]] pid_t getParentPid() const;
        /**
         * Gets the child process ID.
         * @return The child process ID
         */
        [[nodiscard]] pid_t getChildPid() const;

        /**
         * Waits for the child process to finish.
         * @return The exit status of the child process
         */
        int waitChild();
        /**
         * Gets the exit status of the child process.
         * @return The exit status of the child process
         */
        [[nodiscard]] std::optional<int> getExitStatus() const;

        pid_t getPid();

        /**
         * @class ForkEntityException
         * Exception class for handling fork-related errors.
         * Inherits from std::exception.
         */
        class ForkEntityException : public std::exception {
        public:
            /**
             * Constructor to initialize the exception with a message.
             * @param message The error message
             */
            ForkEntityException(const std::string &message): _message(message) {}
            /**
             * Destructor for the exception.
             */
            ~ForkEntityException() = default;
            /**
             * Get the error message.
             * @return The error message
             */
            [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message; ///> Error message
        };

    private:
        pid_t _parentPid; ///> Parent process ID
        pid_t _childPid; ///> Child process ID
        std::optional<int> _exitStatus; ///> Exit status of the child process
    };
};



#endif //FORKENTITY_HPP
