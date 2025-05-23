/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"

#include "Factory/PizzaFactory.hpp"
#include "Kitchen/Kitchen.hpp"
#include "Tools/ResultException.hpp"


namespace Plazza {
    Reception::~Reception()
    {
        if (_running)
            return;

        for (const auto& kitchen : _kitchens) {
            try {
                int status = kitchen->waitChild();
                std::cout << "Kitchen exited with status: " << status << std::endl;
            } catch (const ForkEntity::ForkEntityException& e) {
                std::cerr << "Error while waiting for kitchen: " << e.what() << std::endl;
            }
        }
        _kitchens.clear();
        _running = false;
    }

    void Reception::addKitchen(std::unique_ptr<ForkEntity> entity)
    {
        _kitchens.emplace_back(std::move(entity));
    }

    int Reception::run()
    {
        _running = true;
        std::string input;

        while (true) {
            std::cout << "Pizza Plazza> ";
            if (!std::getline(std::cin, input))
                break;
            if (input == "exit" || input == "quit")
                break;
            if (!_running)
                break;
            if (input == "status")
                this->handleStatus();
            try {
                this->handleInput(input);
            } catch (const ReceptionException &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        return 0;
    }

    void Reception::handleInput(const std::string& input)
    {
        if (input.empty())
            return;
        auto pizzas = PizzaFactory::createPizzaFromString(input);
        if (pizzas.empty())
            throw ReceptionException("Error parsing commands.");
        this->dispatchCommandsToKitchen(pizzas);
    }

    void Reception::createKitchen()
    {
        std::unique_ptr<ForkEntity> forkEntity = nullptr;

        try {
            forkEntity = std::make_unique<ForkEntity>();
        } catch (const ForkEntity::ForkEntityException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }
        if (forkEntity->isChild()) {
            Kitchen kitchenChild(this->_numberOfCooksPerKitchen, this->_timeToRestockIngredients);

            kitchenChild.start();
            std::_Exit(0); // Not executed parent code
        }
        this->addKitchen(std::move(forkEntity));
    }

    void Reception::handleStatus()
    {
        std::cout << "Pizza Plazza" << std::endl;
    }

    void Reception::dispatchCommandsToKitchen(std::vector<std::shared_ptr<IPizza>> pizzas)
    {
        int limitOfPizzas = this->_numberOfCooksPerKitchen * 2;

        std::size_t numKitchensNeeded = (pizzas.size() + limitOfPizzas - 1) / limitOfPizzas;
        for (std::size_t i = 0; i < numKitchensNeeded; i++) {
            auto start = pizzas.begin() + i * limitOfPizzas;
            auto end = (i + 1) * limitOfPizzas < pizzas.size() ? start + limitOfPizzas : pizzas.end();
            std::vector<std::shared_ptr<IPizza>> batch(start, end);
            this->createKitchen();
        }
    }


}