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
#include "Logger/Logger.hpp"

namespace Plazza {

    Reception::~Reception()
    {
        if (_running)
            return;

        for (const auto& kitchen : _kitchens) {
            try {
                int status = kitchen._fork->waitChild();
                LOG_INFO("Reception", "Kitchen exited with status: " + std::to_string(status));
            } catch (const ForkEntity::ForkEntityException& e) {
                LOG_ERROR("Reception", "Error while waiting for kitchen: " + std::string(e.what()));
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
            if (input.empty())
                continue;
            if (!_running)
                break;
            if (input == "status") {
                this->handleStatus();
                continue;
            }

            try {
                this->handleInput(input);
            } catch (const ReceptionException &e) {
                LOG_ERROR("Reception", "Error: " + std::string(e.what()));
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
            LOG_ERROR("Reception", "Error creating fork: " + std::string(e.what()));
            return;
        }

        if (forkEntity->isChild()) {
            pipe->closeParentFd();
            Kitchen kitchenChild(_numberOfCooksPerKitchen, _timeToRestockIngredients, pipe->getChildFd(), _multiplierCookingTime);
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
                    LOG_ERROR("Reception", "Receive error: " + std::string(e.what()));
                }
            }
        );


        _pollLoop.addSelectable(selectable);
        _kitchens.emplace_back(std::move(forkEntity), pipe);
    }

    void Reception::handleStatus()
    {
        LOG_INFO("Reception", "Requesting status from all kitchens...");
        for (auto& kitchen : _kitchens) {
            OrderMessage msg;
            msg.setType(MessageType::STATUS);
            kitchen._pipe->send(kitchen._pipe->getParentFd(), msg);
        }

        std::string statusReport = "Status of kitchens:\n";
        for (size_t i = 0; i < _latestStatuses.size(); ++i) {
            auto& status = _latestStatuses[i];
            statusReport += "Kitchen #" + std::to_string(i) + "\n";
            statusReport += "  Total Cooks: " + std::to_string(status._totalCooks) + "\n";
            statusReport += "  Busy Cooks: " + std::to_string(status._busyCooks) + "\n";
            statusReport += "  Stock: ";
            for (int j = 0; j < IngredientCount; ++j) {
                statusReport += std::to_string(static_cast<int>(static_cast<Ingredient>(j))) + ": " + std::to_string(status._stock[j]) + " ";
            }
            statusReport += "\n";
        }
        LOG_INFO("Reception", statusReport);
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