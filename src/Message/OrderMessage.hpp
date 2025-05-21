/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef ORDERMESSAGE_HPP
#define ORDERMESSAGE_HPP
#include <memory>
#include <vector>

#include "IMessage.hpp"
#include "Pizza/IPizza.hpp"


namespace Plazza {
    class OrderMessage : public Message {
    public:
        void serialize(std::vector<char>& buffer) const override;
        void deserialize(const std::vector<char>& buffer) override;
        size_t getPackedSize() const override;
        std::vector<std::unique_ptr<IPizza>> _pizzas;
        MessageType _type;
    };
}



#endif //ORDERMESSAGE_HPP
