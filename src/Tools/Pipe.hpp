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

#include "Message/IMessage.hpp"


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
         */
        static bool send(int fd, const IMessage& message);
        /**
         * Receives a message from the pipe.
         * @param fd The file descriptor to receive the message from
         * @return A shared pointer to the received message IMessage
         */
        static std::shared_ptr<IMessage> receive(int fd);

        static std::shared_ptr<IMessage> createMessage(MessageType messageType);
    private:
        int _fds[2]; ///> Array to hold the file descriptors for the pipe

        void closeIfOpen(int& fd); ///> Closes the file descriptor if it is open
    };
}


#endif //PIPE_HPP
