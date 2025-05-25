/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** ICookTask
*/

#ifndef ICOOKTASK_HPP_
#define ICOOKTASK_HPP_

namespace Plazza {
    /**
     * @class ICookTask
     * Interface for a cooking task.
     * It defines the contract for executing a cooking task.
     */
    class ICookTask {
        public:
            /**
             * Virtual destructor for ICookTask.
             * Ensures proper cleanup of derived classes.
             */
            virtual ~ICookTask() = default;

            /**
             * Execute the cooking task.
             * This method should be implemented by derived classes to perform the cooking operation.
             */
            virtual void execute() = 0;
    };
}

#endif //ICOOKTASK_HPP_
