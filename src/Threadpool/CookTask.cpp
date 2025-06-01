/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** CookTask
*/

#include "CookTask.hpp"
#include <chrono>
#include <iostream>
#include <thread>


namespace Plazza {
    CookTask::CookTask(const std::shared_ptr<IPizza>& pizza, double multiplier, Stock &stock, std::function<void()> onComplete)
        : _pizza(pizza), _multiplier(multiplier), _stock(stock), _onComplete(onComplete)
    {}

    int CookTask::getBaseCookTime(PizzaType type) const
    {
        switch (type) {
            case PizzaType::Margarita:
                return 1;
            case PizzaType::Regina:
                return 2;
            case PizzaType::Americana:
                return 2;
            case PizzaType::Fantasia:
                return 4;
            default:
                return 2;
        }
    }

    void CookTask::execute()
    {
        if (!_stock.consumeIngredientsFor(_pizza)) {
            std::cout << "Cannot cook pizza: missing ingredients\n";
            return;
        }
        int baseTime = this->getBaseCookTime(_pizza->getType());
        int actualTimeMs = static_cast<int>(baseTime * _multiplier * 1000);

        std::cout << "Cooking pizza...\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(actualTimeMs));

        std::cout << "Pizza cooked!\n";

        if (_onComplete) {
            _onComplete();
        }
    }
}
