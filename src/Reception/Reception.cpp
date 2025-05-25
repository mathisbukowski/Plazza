/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"

#include "Build/OrderMessageBuilder.hpp"
#include "Event/SelectablePipe.hpp"
#include "Factory/PizzaFactory.hpp"
#include "Kitchen/Kitchen.hpp"
#include "Message/OrderMessage.hpp"
#include "Tools/ResultException.hpp"
#include "Message/StatusMessage.hpp"


namespace Plazza {

    Reception::~Reception()
    {
        if (_running)
            return;

        for (const auto& kitchen : _kitchens) {
            try {
                int status = kitchen._fork->waitChild();
                std::cout << "Kitchen exited with status: " << status << std::endl;
            } catch (const ForkEntity::ForkEntityException& e) {
                std::cerr << "Error while waiting for kitchen: " << e.what() << std::endl;
            }
        }
        _kitchens.clear();
        _running = false;
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
            if (input == "status") {
                this->handleStatus();
                continue;
            }

            try {
                this->handleInput(input);
            } catch (const ReceptionException &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }

            _pollLoop.pollOnce(100);
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
        auto pipe = std::make_shared<PipeChannel>();
        std::unique_ptr<ForkEntity> forkEntity;

        try {
            forkEntity = std::make_unique<ForkEntity>();
        } catch (const ForkEntity::ForkEntityException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }

        if (forkEntity->isChild()) {
            pipe->closeParentFd();
            Kitchen kitchenChild(_numberOfCooksPerKitchen, _timeToRestockIngredients, pipe->getChildFd());
            kitchenChild.start();
            std::_Exit(0);
        }

        pipe->closeChildFd();
        _latestStatuses.emplace_back();
        auto selectable = std::make_shared<SelectablePipe>(
            pipe,
            [this, pipe, idx = _latestStatuses.size()]() mutable {
                try {
                    auto status = pipe->receive<StatusMessage>(pipe->getParentFd());
                    KitchenStatus ks;
                    ks._totalCooks = status->getTotalCooks();
                    ks._busyCooks = status->getBusyCooks();
                    std::copy(status->getStock().begin(), status->getStock().end(), ks._stock.begin());
                    _latestStatuses[idx] = std::move(ks);
                } catch (const std::exception& e) {
                    std::cerr << "Receive error: " << e.what() << std::endl;
                }
            }
        );


        _pollLoop.addSelectable(selectable);
        _kitchens.emplace_back(std::move(forkEntity), pipe);
    }

    void Reception::handleStatus()
    {
        std::cout << "Requesting status from all kitchens..." << std::endl;
        for (auto& kitchen : _kitchens) {
            OrderMessage msg;
            msg.setType(MessageType::STATUS);
            kitchen._pipe->send(kitchen._pipe->getParentFd(), msg);
        }
        std::cout << "Status of kitchen :\n";
        for (size_t i = 0; i < _latestStatuses.size(); ++i) {
            auto& status = _latestStatuses[i];
            std::cout << "Kitchen #" << i << "\n";
            std::cout << "  Total Cooks: " << status._totalCooks << "\n";
            std::cout << "  Busy Cooks: " << status._busyCooks << "\n";
            std::cout << "  Stock: ";
            for (int j = 0; j < IngredientCount; ++j)
                std::cout << static_cast<Ingredient>(j) << ": " << status._stock[j] << " ";
            std::cout << "\n";
        }
    }

    void Reception::dispatchCommandsToKitchen(std::vector<std::shared_ptr<IPizza>> pizzas)
    {
        int limitOfPizzas = _numberOfCooksPerKitchen * 2;
        std::size_t numKitchensNeeded = (pizzas.size() + limitOfPizzas - 1) / limitOfPizzas;

        for (std::size_t i = 0; i < numKitchensNeeded; ++i) {
            auto start = pizzas.begin() + i * limitOfPizzas;
            auto end = (i + 1) * limitOfPizzas < pizzas.size() ? start + limitOfPizzas : pizzas.end();
            std::vector<std::shared_ptr<IPizza>> batch(start, end);
            this->createKitchen();
            KitchenChannel& kitchen = _kitchens.back();
            OrderMessageBuilder builder;
            OrderMessage order = builder.setType(MessageType::COMMAND).setPizzas(batch).build();
            kitchen._pipe->send(kitchen._pipe->getParentFd(), order);
        }
    }

}