/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Tools.cpp
*/

#include "Tools.hpp"

pid_t Plazza::Tools::toolGetPid()
{
    pid_t pid = getpid();
    if (pid < 0) {
        std::cerr << "getpid() failed: " << strerror(errno) << std::endl;
    }
    return pid;
}

ssize_t Plazza::Tools::toolRead(int fd, void *buf, size_t count)
{
    ssize_t ret = read(fd, buf, count);
    if (ret == -1)
        std::cerr << "read() failed: " << strerror(errno) << std::endl;
    return ret;
}