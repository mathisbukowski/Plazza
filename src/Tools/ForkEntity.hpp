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
    class ForkEntity {
    public:
        ForkEntity();
        ~ForkEntity() = default;

        [[nodiscard]] bool isParent() const;
        [[nodiscard]] bool isChild() const;

        [[nodiscard]] pid_t getParentPid() const;
        [[nodiscard]] pid_t getChildPid() const;

        int waitChild();
        [[nodiscard]] std::optional<int> getExitStatus() const;

        class ForkEntityException : public std::exception {
        public:
            ForkEntityException(const std::string &message): _message(message) {}
            ~ForkEntityException() = default;
            [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
        };

    private:
        pid_t _parentPid;
        pid_t _childPid;
        std::optional<int> _exitStatus;
    };
};



#endif //FORKENTITY_HPP
