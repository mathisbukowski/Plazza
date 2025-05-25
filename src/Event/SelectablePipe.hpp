/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef SELECTABLEPIPE_HPP
#define SELECTABLEPIPE_HPP


#include <functional>

#include "ISelectable.hpp"
#include "Tools/Pipe.hpp"

namespace Plazza {
    class SelectablePipe : public ISelectable {
    public:
        SelectablePipe(std::shared_ptr<PipeChannel> pipe, std::function<void()> onReadable);
        ~SelectablePipe() override;

        int getFd() const override;

        short getPollEvents() const override;

        void onEvent(short revents) override;
    private:
        std::shared_ptr<PipeChannel> _pipeChannel;
        std::function<void()> _onReadable;
    };
}



#endif //SELECTABLEPIPE_HPP
