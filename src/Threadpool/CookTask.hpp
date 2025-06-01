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
#include <functional>
#include "../Pizza/IPizza.hpp"
#include "ICookTask.hpp"
#include "../Kitchen/Stock.hpp"

namespace Plazza {
    /**
     * @class CookTask
     * Class representing a cooking task for a pizza.
     * It implements the ICookTask interface and provides functionality to execute the cooking process.
     */
    class CookTask : public ICookTask {
        public:
            /**
             * Constructor for CookTask.
             * @param pizza The pizza to be cooked
             * @param multiplier The cooking time multiplier
             * @param stock Reference to the kitchen's stock
             */
            CookTask(const std::shared_ptr<IPizza>& pizza, double multiplier, Stock& stock, std::function<void()> onComplete = nullptr);
            /**
             * Destructor for CookTask.
             * Cleans up resources used by the cooking task.
             */
            void execute() override;

        private:
            const std::shared_ptr<IPizza>& _pizza; ///> Shared pointer to the pizza to be cooked
            double _multiplier; ///> Cooking time multiplier
            Stock& _stock;
            std::function<void()> _onComplete; ///> Callback to execute when cooking is complete
            /**
             * Gets the base cooking time for a specific pizza type.
             * @param type The type of the pizza
             * @return The base cooking time in seconds
             */
            int getBaseCookTime(PizzaType type) const;
    };
}

#endif // COOKTASK_HPP_
