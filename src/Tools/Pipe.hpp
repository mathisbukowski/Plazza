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
    class PipeChannel {
    public:
        PipeChannel();
        ~PipeChannel();

        int getParentFd() const;

        int getChildFd() const;

        void closeParentFd();

        void closeChildFd();

        template<typename T>
        void send(int fd, const T& message)
        {
            std::vector<char> buffer;
            message.serialize(buffer);
            uint32_t size = buffer.size();
            ::write(fd, &size, sizeof(size));
            ::write(fd, buffer.data(), buffer.size());
        }

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
    private:
        int _fds[2];

        void closeIfOpen(int& fd);
    };
}


#endif //PIPE_HPP
