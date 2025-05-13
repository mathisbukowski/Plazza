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

    private:
        pid_t _parentPid;
        pid_t _childPid;
        std::optional<int> _exitStatus;
    };
};



#endif //FORKENTITY_HPP
