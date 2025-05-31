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
#include <atomic>
#include <chrono>

namespace Plazza {

    /**
     * @class PipeChannel
     * Enhanced pipe channel for bidirectional communication between reception and kitchens
     * Supports multiple simultaneous connections and message serialization
     */
    class PipeChannel {
    private:
        int _fds[2]{};                    // File descriptors [parent, child]
        std::mutex _sendMutex;          // Mutex for thread-safe sending
        std::mutex _receiveMutex;       // Mutex for thread-safe receiving
        std::atomic<bool> _isConnected; // Connection status
        std::atomic<uint32_t> _messageCounter; // For message tracking/debugging

        /**
         * Close file descriptor if open
         * @param fd File descriptor reference to close
         */
        void closeIfOpen(int& fd);

        /**
         * Send raw buffer through the pipe
         * @param fd File descriptor to send through
         * @param buffer Buffer to send
         * @return Number of bytes sent, -1 on error
         */
        ssize_t sendRawBuffer(int fd, const std::vector<char>& buffer);

        /**
         * Receive raw buffer from the pipe
         * @param fd File descriptor to receive from
         * @param buffer Buffer to store received data
         * @param timeoutMs Timeout in milliseconds (0 = no timeout)
         * @return Number of bytes received, -1 on error, 0 on timeout/disconnect
         */
        ssize_t receiveRawBuffer(int fd, std::vector<char>& buffer, int timeoutMs = 0);

    public:
        /**
         * Constructor - Creates a bidirectional pipe using socketpair
         * @throws std::runtime_error if socketpair creation fails
         */
        PipeChannel();

        /**
         * Destructor - Closes both file descriptors
         */
        ~PipeChannel();

        // Disable copy constructor and assignment operator
        PipeChannel(const PipeChannel&) = delete;
        PipeChannel& operator=(const PipeChannel&) = delete;

        // Enable move constructor and assignment operator
        PipeChannel(PipeChannel&& other) noexcept;
        PipeChannel& operator=(PipeChannel&& other) noexcept;

        /**
         * Get parent process file descriptor (typically for reception)
         * @return Parent file descriptor
         */
        int getParentFd() const;

        /**
         * Get child process file descriptor (typically for kitchen)
         * @return Child file descriptor
         */
        int getChildFd() const;

        /**
         * Close child file descriptor (call from parent process)
         */
        void closeChildFd();

        /**
         * Close parent file descriptor (call from child process)
         */
        void closeParentFd();

        /**
         * Check if the channel is still connected
         * @return true if connected, false otherwise
         */
        bool isConnected() const;

        /**
         * Send a message from parent to child
         * @param message Message to send
         * @return true on success, false on failure
         */
        bool sendToChild(const IMessage& message);

        /**
         * Send a message from child to parent
         * @param message Message to send
         * @return true on success, false on failure
         */
        bool sendToParent(const IMessage& message);

        /**
         * Receive a message on parent side (from child)
         * @param timeoutMs Timeout in milliseconds (0 = no timeout)
         * @return Unique pointer to received message, nullptr on failure/timeout
         */
        std::unique_ptr<IMessage> receiveFromChild(int timeoutMs = 0);

        /**
         * Receive a message on child side (from parent)
         * @param timeoutMs Timeout in milliseconds (0 = no timeout)
         * @return Unique pointer to received message, nullptr on failure/timeout
         */
        std::unique_ptr<IMessage> receiveFromParent(int timeoutMs = 0);

        /**
         * Overloaded operators for easy message sending
         */
        PipeChannel& operator<<(const IMessage& message);  // Send to child (if parent) or parent (if child)
        PipeChannel& operator>>(std::unique_ptr<IMessage>& message); // Receive message

        bool testConnection(int timeoutMs);
    private:
        // Statistics tracking
        mutable std::atomic<uint32_t> _messagesSent{0};
        mutable std::atomic<uint32_t> _messagesReceived{0};
        mutable std::chrono::steady_clock::time_point _lastActivity;
        mutable std::mutex _statsMutex;
    };

    /**
     * @class PipeChannelManager
     * Manages multiple pipe channels for communication with multiple kitchens
     */
    class PipeChannelManager {
    private:
        std::vector<std::unique_ptr<PipeChannel>> _channels;
        std::mutex _channelsMutex;
        std::atomic<uint32_t> _nextChannelId{0};

    public:
        PipeChannelManager() = default;
        ~PipeChannelManager();

        // Disable copy
        PipeChannelManager(const PipeChannelManager&) = delete;
        PipeChannelManager& operator=(const PipeChannelManager&) = delete;

        /**
         * Create a new channel
         * @return Channel ID, or -1 on failure
         */
        int createChannel();

        /**
         * Get a channel by ID
         * @param channelId Channel ID
         * @return Pointer to channel, nullptr if not found
         */
        PipeChannel* getChannel(int channelId);

        /**
         * Remove and close a channel
         * @param channelId Channel ID to remove
         * @return true if removed, false if not found
         */
        bool removeChannel(int channelId);

        /**
         * Get number of active channels
         * @return Number of channels
         */
        size_t getChannelCount() const;

        /**
         * Broadcast a message to all channels
         * @param message Message to broadcast
         * @param fromParent true if sending from parent to all children
         * @return Number of successful sends
         */
        size_t broadcastMessage(const IMessage& message, bool fromParent = true);

        /**
         * Check for messages on all channels (non-blocking)
         * @param messages Vector to store received messages
         * @param channelIds Vector to store corresponding channel IDs
         * @return Number of messages received
         */
        size_t pollAllChannels(std::vector<std::unique_ptr<IMessage>>& messages,
                              std::vector<int>& channelIds);

        /**
         * Remove inactive/disconnected channels
         * @return Number of channels removed
         */
        size_t cleanupInactiveChannels();

    };

} // namespace Plazza

#endif //PIPE_HPP
