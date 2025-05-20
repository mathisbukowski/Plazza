/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef POSIXQUEUE_HPP
#define POSIXQUEUE_HPP


#include <memory>
#include <mqueue.h>
#include <vector>

#include "Reception/Message.hpp"

namespace Plazza {
    /**
     * @class PosixQueue
     * Class responsible for managing a POSIX message queue.
     * @note This class is an encapsulation of the POSIX message queue API from C
     */
    class PosixQueue {
        public:
            /**
             * Constructor for the PosixQueue class.
             * @param name The name of the queue
             * @param create Flag to indicate if the queue should be created
             * @param mode The mode for the queue (default is 0666)
             * @throws std::runtime_error if the queue cannot be opened
             * @note The name must start with a '/' character
             */
            PosixQueue(const std::string& name, bool create = false, mode_t mode = 0666);
            /**
             * Destructor for the PosixQueue class.
             */
            ~PosixQueue();

            /**
             * Delete the copy constructor to prevent copying
             */
            PosixQueue(const PosixQueue&) = delete;
            /**
             * Delete the copy assignment operator to prevent copying
             */
            PosixQueue& operator=(const PosixQueue&) = delete;

            /**
             * Sends a message to the queue.
             * @param msg The message to send
             * @param priority The priority of the message
             * @return True if the message was sent successfully, false otherwise
             * @note The message must be a unique pointer to a Message object
             */
            bool sendMessage(const std::unique_ptr<Message>& msg, unsigned int priority = 0);
            /**
             * Receives a message from the queue.
             * @param priority The priority of the received message
             * @return A unique pointer to the received message
             * @note The caller is responsible for deleting the message
             */
            std::unique_ptr<Message> receiveMessage(unsigned int& priority);

            /**
             * Unlinks the message queue.
             * @param name The name of the queue to unlink
             * @note This function should be called when the queue is no longer needed
             */
            static void unlink(const std::string& name);
            /**
             * Gets the name of the queue.
             * @return The name of the queue
             */
            std::string getName() const { return _name; }
            /**
             * Checks if the queue is open.
             * @return True if the queue is open, false otherwise
             */
            bool isOpen() const { return _queue != -1; }

            template<typename T>
            std::unique_ptr<T> receiveTypedMessage(unsigned int& priority) {
                std::vector<char> buffer;
                size_t sizeReceived;
                if (!receiveBuffer(buffer, sizeReceived, priority))
                    return nullptr;

                if (sizeReceived < sizeof(MessageType))
                    return nullptr;

                MessageType type;
                std::memcpy(&type, buffer.data(), sizeof(MessageType));

                if (type != T().getType())
                    return nullptr;

                auto msg = std::make_unique<T>();
                msg->deserialize(buffer.data(), sizeReceived);
                return msg;
            }

        private:
            /**
             * Sends a buffer to the queue.
             * @param buffer The buffer to send
             * @param priority The priority of the message
             * @return True if the message was sent successfully, false otherwise
             * @note The buffer size must not exceed MAX_MSG_SIZE
             */
            bool sendBuffer(const std::vector<char>& buffer, unsigned int priority);
            /**
             * Receives a message from the queue.
             * @param buffer The buffer to store the received message
             * @param sizeReceived The size of the received message
             * @param priority The priority of the received message
             * @return True if the message was received successfully, false otherwise
             */
            bool receiveBuffer(std::vector<char>& buffer, size_t& sizeReceived, unsigned int& priority);

            mqd_t _queue; ///> POSIX message queue descriptor
            std::string _name; ///> Name of the message queue
            bool _created; ///> Flag to indicate if the queue was created by this instance
            static constexpr size_t MAX_MSG_SIZE = 8192; ///> Maximum message size
            static constexpr size_t MAX_MESSAGES = 10; ///> Maximum number of messages in the queue
        };
}


#endif //POSIXQUEUE_HPP
