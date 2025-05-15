/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "Message.hpp"

namespace Plazza {
    void OrderMessage::serialize(const std::string& buffer, size_t& size) const
    {
        std::string ptr = buffer;

        std::memcpy(ptr.data(), &_type, sizeof(MessageType));
        ptr += sizeof(MessageType);

        size_t count = _pizzas.size();
        std::memcpy(ptr.data(), &count, sizeof(size_t));
        ptr += sizeof(size_t);

        for (const auto& pizza : _pizzas) {
            PizzaType type = pizza.getType();
            PizzaSize pizza_size = pizza.getSize();
            std::memcpy(ptr.data(), &type, sizeof(PizzaType));
            ptr += sizeof(PizzaType);
            std::memcpy(ptr.data(), &pizza_size, sizeof(PizzaSize));
            ptr += sizeof(PizzaSize);
        }

        size = ptr.size() - buffer.size();
    }

    void OrderMessage::deserialize(const std::string& buffer, size_t size)
    {
        std::string ptr = buffer;

        std::memcpy(&_type, ptr.c_str(), sizeof(MessageType));
        ptr += sizeof(MessageType);

        size_t count;
        std::memcpy(&count, ptr.c_str(), sizeof(size_t));
        ptr += sizeof(size_t);

        _pizzas.clear();
        _pizzas.reserve(count);

        (void)size;
        for (size_t i = 0; i < count; ++i) {
            PizzaType type;
            PizzaSize pizza_size;
            std::memcpy(&type, ptr.c_str(), sizeof(PizzaType));
            ptr += sizeof(PizzaType);
            std::memcpy(&pizza_size, ptr.c_str(), sizeof(PizzaSize));
            ptr += sizeof(PizzaSize);
            _pizzas.emplace_back(type, pizza_size);
        }
    }

    size_t OrderMessage::getPackedSize() const
    {
        return sizeof(MessageType) + sizeof(size_t) + _pizzas.size() * (sizeof(PizzaType) + sizeof(PizzaSize));
    }

    void StatusMessage::serialize(const std::string& buffer, size_t& size) const
    {
        std::string ptr = buffer;

        std::memcpy(ptr.data(), &_type, sizeof(MessageType));
        ptr += sizeof(MessageType);
        std::memcpy(ptr.data(), &_active, sizeof(int));
        ptr += sizeof(int);
        std::memcpy(ptr.data(), &_total, sizeof(int));
        ptr += sizeof(int);
        std::memcpy(ptr.data(), &_queued, sizeof(int));
        ptr += sizeof(int);

        size = ptr.size() - buffer.size();
    }

    void StatusMessage::deserialize(const std::string& buffer, size_t size)
    {
        std::string ptr = buffer;

        std::memcpy(&_type, ptr.c_str(), sizeof(MessageType));
        ptr += sizeof(MessageType);
        std::memcpy(&_active, ptr.c_str(), sizeof(int));
        ptr += sizeof(int);
        std::memcpy(&_total, ptr.c_str(), sizeof(int));
        ptr += sizeof(int);
        std::memcpy(&_queued, ptr.c_str(), sizeof(int));
        ptr += sizeof(int);
        (void)size;
    }

    void NotificationMessage::serialize(const std::string& buffer, size_t& size) const
    {
        std::string ptr = buffer.data();

        std::memcpy(ptr.data(), &_type, sizeof(MessageType));
        ptr += sizeof(MessageType);

        size_t len = _message.size();
        std::memcpy(ptr.data(), &len, sizeof(size_t));
        ptr += sizeof(size_t);

        if (len > 0) {
            std::memcpy(ptr.data(), _message.data(), len);
            ptr += len;
        }

        size = ptr.size() - buffer.size();
    }

    void NotificationMessage::deserialize(const std::string& buffer, size_t size)
    {
        std::string ptr = buffer;

        std::memcpy(&_type, ptr.c_str(), sizeof(MessageType));
        ptr += sizeof(MessageType);

        size_t len;
        std::memcpy(&len, ptr.c_str(), sizeof(size_t));
        ptr += sizeof(size_t);

        _message.assign(ptr, len);
        (void)size;
    }


}