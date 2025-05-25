/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef PIPE_HPP
#define PIPE_HPP
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <unistd.h>
#include <vector>


namespace Plazza {
    /**
     * @class PipeChannel
     * Class responsible
     * for managing a pipe channel for inter-process communication.
     */
    class PipeChannel {
    public:
        /**
         * Default constructor for PipeChannel.
         * Initializes the pipe and sets up the file descriptors.
         */
        PipeChannel();
        /**
         * Destructor for PipeChannel.
         */
        ~PipeChannel();
        /**
         * Gets the file descriptor for the parent end of the pipe.
         * @return The file descriptor for the parent end of the pipe
         */
        int getParentFd() const;
        /**
         * Gets the file descriptor for the child end of the pipe.
         * @return The file descriptor for the child end of the pipe
         */
        int getChildFd() const;
        /**
         * Closes the parent file descriptor.
         * This method should be called when the parent process is done using the pipe.
         */
        void closeParentFd();
        /**
         * Closes the child file descriptor.
         * This method should be called when the child process is done using the pipe.
         */
        void closeChildFd();
        /**
         * sends a message through the pipe.
         * @param fd The file descriptor to send the message through
         * @param message The message to send
         * @tparam T The type of the message, which must implement serialize and deserialize methods
         */
        template<typename T>
        void send(int fd, const T& message)
        {
            std::vector<char> buffer;
            message.serialize(buffer);
            uint32_t size = buffer.size();
            if (::write(fd, &size, sizeof(size)) == -1)
                throw std::runtime_error("write failed");
            if (::write(fd, buffer.data(), buffer.size()) == -1)
                throw std::runtime_error("write failed");
        }
        /**
         * Receives a message from the pipe.
         * @param fd The file descriptor to receive the message from
         * @return A shared pointer to the received message of type T
         * @tparam T The type of the message, which must implement serialize and deserialize methods
         */
        template<typename T>
        std::shared_ptr<T> receive(int fd)
        {
            uint32_t size = 0;
            ssize_t bytes = :: read(fd, &size, sizeof(size));
            if (bytes != sizeof(size))
                throw std::runtime_error("failed to read from pipe");
            std::vector<char> buffer(size);
            bytes = :: read(fd, buffer.data(), size);
            if (bytes != static_cast<ssize_t>(size))
                throw std::runtime_error("failed to read from pipe");
            std::shared_ptr<T> message = std::make_shared<T>();
            message->deserialize(buffer);
            return message;
        }
        /**
         * Writes data to the specified file descriptor.
         * @param fd The file descriptor to write to
         * @param data The data to write
         * This method writes the data to the specified file descriptor.
         */
        void writeInChannel(int& fd, std::vector<char> data);
    private:
        int _fds[2]; ///> Array to hold the file descriptors for the pipe

        void closeIfOpen(int& fd); ///> Closes the file descriptor if it is open
    };
}


#endif //PIPE_HPP
