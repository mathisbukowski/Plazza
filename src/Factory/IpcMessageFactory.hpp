/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef IPCMESSAGEFACTORY_HPP
#define IPCMESSAGEFACTORY_HPP
#include <memory>
#include <memory>

#include "Reception/Message.hpp"


namespace Plazza {
    /**
     * @class IpcMessageFactory
     * Factory class for creating IPC messages.
     */
    class IpcMessageFactory {
    public:
        /**
         * Create a message of the specified type.
         * @param type The type of the message to create
         * @return A unique pointer to the created message
         */
        static std::unique_ptr<Message> create(MessageType type);
    };
}

#endif //IPCMESSAGEFACTORY_HPP
