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

namespace Plazza {
    /**
     * @class PosixQueue
     * Class responsible for managing a POSIX message queue.
     * @note This class is an encapsulation of the POSIX message queue API from C
     */
    class PosixQueue {
        /**
         * Constructor to initialize the message queue.
         * @param name The name of the message queue
         * @param create Flag to indicate if the queue should be created
         * @param maxMsgSize The maximum size of a message in the queue
         */
        PosixQueue(const std::string& name, bool create = false, size_t maxMsgSize = 1024);
        /**
         * Destructor to clean up the message queue.
         */
        ~PosixQueue();

        /**
         * Send a message to the queue.
         * @param message The message to send
         * @param priority The priority of the message
         */
        void send(const std::string& message, unsigned int priority = 0);
        /**
         * Receive a message from the queue.
         * @param priority The priority of the message
         * @return The received message
         */
        std::string receive(std::unique_ptr<unsigned int> priority);

    private:
        std::string _name; ///> Name of the message queue
        mqd_t _queue; ///> Message queue descriptor
        size_t _maxMsgSize; ///> Maximum size of a message in the queue
        bool _created; ///> Flag to indicate if the queue was created
        /**
         * Close the message queue.
         */
        void closeQueue();
        /**
         * Unlink the message queue.
         */
        void unlinkQueue();
    };
}


#endif //POSIXQUEUE_HPP
