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
        std::vector<Command> commands;
        try {
            commands = _parser->parse(input);
        } catch (const Parser::ParserException &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }
        if (commands.empty())
            throw ReceptionException("Error parsing commands.");
    }

    void Reception::createKitchen()
    {
        auto forkEntity = std::make_unique<ForkEntity>();

        if (forkEntity->isChild()) {
            // Code Enfant
        }
        this->addKitchen(std::move(forkEntity));
    }

    void Reception::handleStatus()
    {
        std::cout << "Pizza Plazza" << std::endl;
    }


}