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
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

namespace Plazza {
    /**
     * @class PipeChannel
     * Class responsible for managing a named pipe channel for inter-process communication.
     * Uses FIFO (named pipes) instead of anonymous pipes for better IPC management.
     */
    class PipeChannel {
    public:
        /**
         * Constructor for PipeChannel with kitchen PID.
         * Creates named pipes for bidirectional communication.
         * @param kitchenPid The PID of the kitchen process
         * @param isReception True if this is the reception side, false for kitchen side
         */
        PipeChannel(pid_t kitchenPid, bool isReception = true);

        /**
         * Default constructor for PipeChannel (for backward compatibility).
         * Creates named pipes using current process PID.
         */
        PipeChannel();

        /**
         * Destructor for PipeChannel.
         * Cleans up file descriptors and removes named pipes if created by reception.
         */
        ~PipeChannel();

        // Disable copy constructor and assignment
        PipeChannel(const PipeChannel&) = delete;
        PipeChannel& operator=(const PipeChannel&) = delete;

        // Move semantics
        PipeChannel(PipeChannel&& other) noexcept;
        PipeChannel& operator=(PipeChannel&& other) noexcept;

        /**
         * Gets the file descriptor for the parent (reception) end of the pipe.
         * @return The file descriptor for reading from kitchen
         */
        int getParentFd() const;

        /**
         * Gets the file descriptor for the child (kitchen) end of the pipe.
         * @return The file descriptor for writing to reception
         */
        int getChildFd() const;

        /**
         * Opens the pipes for reception side.
         * Reception writes commands to kitchen and reads status from kitchen.
         */
        void openForReception();

        /**
         * Opens the pipes for kitchen side.
         * Kitchen reads commands from reception and writes status to reception.
         */
        void openForKitchen();

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
         * Closes all file descriptors.
         */
        void closeAll();

        /**
         * Sends a message through the pipe.
         * @param fd The file descriptor to send the message through
         * @param message The message to send
         * @tparam T The type of the message, which must implement serialize and deserialize methods
         */
        template<typename T>
        void send(int fd, const T& message)
        {
            if (fd == -1) {
                throw std::runtime_error("Invalid file descriptor for send");
            }

            std::vector<char> buffer;
            message.serialize(buffer);
            uint32_t size = buffer.size();

            if (::write(fd, &size, sizeof(size)) != sizeof(size))
                throw std::runtime_error("Failed to write message size to pipe");
            if (::write(fd, buffer.data(), buffer.size()) != static_cast<ssize_t>(buffer.size()))
                throw std::runtime_error("Failed to write message data to pipe");
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
            if (fd == -1) {
                throw std::runtime_error("Invalid file descriptor for receive");
            }

            uint32_t size = 0;
            ssize_t bytes = ::read(fd, &size, sizeof(size));
            if (bytes != sizeof(size)) {
                if (bytes == 0) {
                    return nullptr; // Pipe closed
                }
                throw std::runtime_error("Failed to read message size from pipe");
            }

            std::vector<char> buffer(size);
            bytes = ::read(fd, buffer.data(), size);
            if (bytes != static_cast<ssize_t>(size))
                throw std::runtime_error("Failed to read message data from pipe");

            std::shared_ptr<T> message = std::make_shared<T>();
            message->deserialize(buffer);
            return message;
        }

        /**
         * Overloaded operator<< for sending messages.
         * @param message The message to send
         * @return Reference to this PipeChannel for chaining
         * @tparam T The type of the message
         */
        template<typename T>
        PipeChannel& operator<<(const T& message)
        {
            if (_isReception) {
                send(_writeFd, message);
            } else {
                send(_writeFd, message);
            }
            return *this;
        }

        /**
         * Overloaded operator>> for receiving messages.
         * @param message Shared pointer to store the received message
         * @return Reference to this PipeChannel for chaining
         * @tparam T The type of the message
         */
        template<typename T>
        PipeChannel& operator>>(std::shared_ptr<T>& message)
        {
            if (_isReception) {
                message = receive<T>(_readFd);
            } else {
                message = receive<T>(_readFd);
            }
            return *this;
        }

        /**
         * Writes data to the specified file descriptor.
         * @param fd The file descriptor to write to
         * @param data The data to write
         * This method writes the data to the specified file descriptor.
         */
        void writeInChannel(int& fd, std::vector<char> data);

        /**
         * Gets the kitchen PID associated with this pipe.
         * @return The kitchen PID
         */
        pid_t getKitchenPid() const { return _kitchenPid; }

        /**
         * Gets the read file descriptor.
         * @return The read file descriptor
         */
        int getReadFd() const { return _readFd; }

        /**
         * Gets the write file descriptor.
         * @return The write file descriptor
         */
        int getWriteFd() const { return _writeFd; }
        /**
         * Sets the file descriptors for this pipe.
         * @param readFd The file descriptor for reading
         * @param writeFd The file descriptor for writing
         */
        void setFds(int readFd, int writeFd);

    private:
        std::string _receptionToCookPipe;  ///< Path to pipe from reception to kitchen
        std::string _cookToReceptionPipe;  ///< Path to pipe from kitchen to reception
        int _readFd;                       ///< File descriptor for reading
        int _writeFd;                      ///< File descriptor for writing
        bool _isReception;                 ///< True if this is reception side
        pid_t _kitchenPid;                 ///< PID of the kitchen process
        bool _pipesCreated;                ///< True if this instance created the pipes

        /**
         * Creates a named pipe (FIFO).
         * @param pipeName The path to the pipe to create
         */
        void createPipe(const std::string& pipeName);

        /**
         * Removes a named pipe.
         * @param pipeName The path to the pipe to remove
         */
        void removePipe(const std::string& pipeName);

        /**
         * Closes the file descriptor if it is open.
         * @param fd Reference to the file descriptor to close
         */
        void closeIfOpen(int& fd);

        /**
         * Generates pipe names based on kitchen PID.
         */
        void generatePipeNames();
    };
}

#endif //PIPE_HPP