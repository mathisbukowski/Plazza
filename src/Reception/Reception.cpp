/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "Event/SelectablePipe.hpp"
#include "Factory/PizzaFactory.hpp"
#include "Kitchen/Kitchen.hpp"
#include "Message/OrderMessage.hpp"
#include "Message/ReceiveStatusMessage.hpp"
#include "Tools/ResultException.hpp"


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
            Kitchen kitchenChild(_numberOfCooksPerKitchen, _timeToRestockIngredients, pipe->getChildFd(), pipe->getChildFd(), _multiplierCookingTime, _kitchenCount++);
            kitchenChild.start();
            std::_Exit(0);
        }

        pipe->closeChildFd();
        _latestStatuses.emplace_back();
        auto selectable = std::make_shared<SelectablePipe>(
            pipe,
            [this, pipe]() mutable {
                this->processMessage(pipe->getParentFd());
            }
        );
        _pollLoop.addSelectable(selectable);
        _kitchens.emplace_back(std::move(forkEntity), pipe);
    }

    void Reception::handleStatus()
    {
        std::cout << "Status of kitchen :\n";
        for (size_t i = 0; i < _latestStatuses.size(); ++i) {
            auto& status = _latestStatuses[i];
            std::cout << "Kitchen #" << i << "\n";
            std::cout << "  Total Cooks: " << status._totalCooks << "\n";
            std::cout << "  Busy Cooks: " << status._busyCooks << "\n";
            std::cout << "  Stock: ";
            for (int j = 0; j < IngredientCount; ++j)
                std::cout << j << ": " << status._stock[j] << " ";
            std::cout << "\n";
        }
    }

    void Reception::dispatchCommandsToKitchen(std::vector<std::shared_ptr<IPizza>> pizzas)
    {
        int limitOfPizzas = _numberOfCooksPerKitchen;
        std::size_t numKitchensNeeded = (pizzas.size() + limitOfPizzas - 1) / limitOfPizzas;

        for (std::size_t i = 0; i < numKitchensNeeded; ++i) {
            auto start = pizzas.begin() + i * limitOfPizzas;
            auto end = (i + 1) * limitOfPizzas < pizzas.size() ? start + limitOfPizzas : pizzas.end();
            std::vector<std::shared_ptr<IPizza>> batch(start, end);
            this->createKitchen();
            KitchenChannel& kitchen = _kitchens.back();
            OrderMessage message = OrderMessage(static_cast<uint8_t>(MessageType::ORDER));
            message._pizzas = batch;
            if (!PipeChannel::send(kitchen._pipe->getParentFd(), message))
                return;
        }
    }
    void Reception::processMessage(int fd)
    {
        auto receivedMessage = PipeChannel::receive(fd);

        if (!receivedMessage)
            return;

        switch (receivedMessage->getType()) {
        case static_cast<uint8_t>(MessageType::KITCHEN_CLOSING):
            std::cout << "Kitchen closing" << std::endl;
            break;
        case static_cast<uint8_t>(MessageType::ORDER):
            break;
        case static_cast<uint8_t>(MessageType::RECEIVE_STATUS):
            this->receiveStatusFromKitchen(std::dynamic_pointer_cast<ReceiveStatusMessage>(receivedMessage));
        case static_cast<uint8_t>(MessageType::STATUS):
            break;
        default:
            std::cerr << "Unknown message received" << std::endl;
        }
    }

    void Reception::receiveStatusFromKitchen(const std::shared_ptr<ReceiveStatusMessage>& message)
    {
        KitchenStatus ks;
        ks._stock = message->_stock;
        ks._busyCooks = message->_busyCooks;
        ks._totalCooks = message->_totalCooks;
        _latestStatuses.emplace_back(ks);
    }


}