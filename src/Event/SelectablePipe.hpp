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
    /**
     * @class SelectablePipe
     * This class represents a selectable pipe that can be used in an event loop.
     * It implements the ISelectable interface and provides methods to handle events on the pipe.
     */
    class SelectablePipe : public ISelectable {
    public:
        /**
         * Constructor for SelectablePipe.
         * @param pipe A shared pointer to a PipeChannel object representing the pipe.
         * @param onReadable A callback function to be called when the pipe is readable.
         */
        SelectablePipe(std::shared_ptr<PipeChannel> pipe, std::function<void()> onReadable);
        /**
         * Destructor for SelectablePipe.
         */
        ~SelectablePipe() override;
        /**
         * Gets the file descriptor of the pipe.
         * @return The file descriptor associated with the pipe.
         */
        int getFd() const override;
        /**
         * Gets the poll events for the pipe.
         * This method returns the events that the pipe is interested in, such as POLLIN for readability.
         * @return A short representing the poll events (e.g., POLLIN).
         */
        short getPollEvents() const override;
        /**
         * Handles events for the pipe.
         * This method will be called when the pipe has events to process, such as when it is readable.
         * @param revents The events that occurred, as returned by the poll function.
         */
        void onEvent(short revents) override;
    private:
        std::shared_ptr<PipeChannel> _pipeChannel; ///> A shared pointer to the PipeChannel object representing the pipe.
        std::function<void()> _onReadable; ///> A callback function to be called when the pipe is readable.
    };
}



#endif //SELECTABLEPIPE_HPP
