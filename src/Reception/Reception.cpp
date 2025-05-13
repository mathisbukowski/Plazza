/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"

#include "Reception.hpp"

namespace Plazza {
    Reception::~Reception()
    {
        if (_running)
            return;

        for (const auto& kitchen : _kitchens) {
            try {
                int status = kitchen->waitChild();
                std::cout << "Kitchen exited with status: " << status << std::endl;
            } catch (const std::exception& e) {
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

        std::cout << "Pizza Plazza> ";

        while (std::getline(std::cin, input)) {
            if (input == "exit" || input == "quit")
                break;
            try {
                this->handleInput(input);
            } catch (const ReceptionException &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        return 0;
    }

    void handleInput(const std::string& input)
    {
        if (input.empty())
            return;
        auto commands =
    }

    void Reception::createKitchen()
    {
        auto forkEntity = std::make_unique<ForkEntity>();

        if (forkEntity->isChild()) {
            // Code Enfant
        }
        this->addKitchen(std::move(forkEntity));
    }


}