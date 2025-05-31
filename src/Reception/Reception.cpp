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
#include "Message/PizzaOrderMessage.hpp"
#include "Tools/ResultException.hpp"
#include "Message/StatusMessage.hpp"
#include "Message/StatusRequestMessage.hpp"
#include "Message/StatusResponseMessage.hpp"

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
            Kitchen kitchenChild(_numberOfCooksPerKitchen, _timeToRestockIngredients, pipe->getChildFd(), _multiplierCookingTime);
            kitchenChild.start();
            std::_Exit(0);
        }

        pipe->closeChildFd();
        _latestStatuses.emplace_back();
        _kitchens.emplace_back(std::move(forkEntity), pipe);
    }

    void Reception::handleStatus()
    {
        std::cout << "Requesting status from all kitchens..." << std::endl;

        _latestStatuses.clear();

        for (auto& kitchen : _kitchens) {
            StatusRequestMessage msg;
            kitchen._pipe->sendToParent(msg);
        }

        for (auto& kitchen : _kitchens) {
            std::unique_ptr<IMessage> message = kitchen._pipe->receiveFromParent(100); // timeout 100ms

            if (!message || message->getType() != MessageType::STATUS_RESPONSE) {
                std::cerr << "Failed to receive status from kitchen." << std::endl;
                _latestStatuses.emplace_back();
                continue;
            }

            auto response = dynamic_cast<StatusResponseMessage*>(message.get());
            if (!response) {
                std::cerr << "Invalid status message received." << std::endl;
                _latestStatuses.emplace_back();
                continue;
            }

            _latestStatuses.push_back(response);
        }

        std::cout << "Status of kitchens:\n";
        for (size_t i = 0; i < _latestStatuses.size(); ++i) {
            auto& status = _latestStatuses[i];
            std::cout << "Kitchen #" << i << "\n";
            std::cout << "  Total Cooks: " << status->getTotalCooks() << "\n";
            std::cout << "  Busy Cooks: " << status->getActiveCooks() << "\n";
            std::cout << "  Stock: ";
            for (int j = 0; j < IngredientCount; ++j)
                std::cout << static_cast<Ingredient>(j) << ": " << status->getStock()[j] << " ";
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
            PizzaOrderMessage msg(batch, orderId++);
            kitchen._pipe->sendToParent(msg);
        }
    }

}
