/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** CookTask
*/

#ifndef COOKTASK_HPP_
#define COOKTASK_HPP_

#include <memory>
#include <vector>
#include "../Pizza/IPizza.hpp"
#include "ICookTask.hpp"

namespace Plazza {
    class CookTask : public ICookTask {
        public:
            CookTask(const std::shared_ptr<IPizza>& pizza, double multiplier);
            void execute() override;

        private:
            const std::shared_ptr<IPizza>& _pizza;
            double _multiplier;

            int getBaseCookTime(PizzaType type) const;
    };
}

#endif // COOKTASK_HPP_
