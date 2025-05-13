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
    class PosixQueue {
        PosixQueue(const std::string& name, bool create = false, size_t maxMsgSize = 1024);
        ~PosixQueue();

        void send(const std::string& message, unsigned int priority = 0);
        std::string receive(std::unique_ptr<unsigned int> priority);
    private:
        std::string _name;
        mqd_t _queue;
        size_t _maxMsgSize;
        bool _created;
        void closeQueue();
        void unlinkQueue();
    };
}


#endif //POSIXQUEUE_HPP
