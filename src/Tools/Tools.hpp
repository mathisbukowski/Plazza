/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Tools.hpp
*/

#ifndef PLAZZA_TOOLS_HPP
#define PLAZZA_TOOLS_HPP

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstring>

namespace Plazza {

    /**
     * @class Tools
     * A utility class for various helper functions.
     * This class provides static methods that can be used throughout the application.
     */
    class Tools {
    public:
        /**
         * Retrieves the process ID of the current process.
         * @return The process ID as a pid_t.
         */
        static pid_t toolGetPid();
        /**
         * Reads data from a file descriptor.
         * @param fd The file descriptor to read from.
         * @param buf The buffer to store the read data.
         * @param count The number of bytes to read.
         * @return The number of bytes read, or -1 on error.
         */
        static ssize_t toolRead(int fd, void *buf, size_t count);

        static ssize_t toolWrite(int fd, const void *buf, size_t count);
    };

} // namespace Plazza

#endif //PLAZZA_TOOLS_HPP
