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
#include "Message/NotificationMessage.hpp"
#include <chrono>
#include <thread>



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
            Kitchen kitchenChild(_numberOfCooksPerKitchen, _timeToRestockIngredients, pipe->getChildFd(), _multiplierCookingTime);
            kitchenChild.start();
            std::_Exit(0);
        }

        pipe->closeChildFd();
        _latestStatuses.emplace_back();
        _kitchenPizzaCounts.push_back(0);
        auto selectable = std::make_shared<SelectablePipe>(
            pipe,
            [this, pipe, idx = _latestStatuses.size() - 1]() mutable {
                try {
                    uint32_t size = 0;
                    ssize_t bytesRead = read(pipe->getParentFd(), &size, sizeof(size));
                    if (bytesRead != sizeof(size)) return;

                    std::vector<char> buffer(size);
                    bytesRead = read(pipe->getParentFd(), buffer.data(), size);
                    if (bytesRead != static_cast<ssize_t>(size)) return;

                    auto status = pipe->receive<StatusMessage>(pipe->getParentFd());
                    if (idx < _latestStatuses.size()) {
                        KitchenStatus ks;
                        ks._totalCooks = status->getTotalCooks();
                        ks._busyCooks = status->getBusyCooks();
                        std::copy(status->getStock().begin(), status->getStock().end(), ks._stock.begin());
                        _latestStatuses[idx] = std::move(ks);
                    }
                } catch (const std::exception& e) {
                    _pollLoop.removeSelectable(pipe->getParentFd());
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
            try {
                OrderMessage msg;
                msg.setType(MessageType::STATUS);
                kitchen._pipe->send(kitchen._pipe->getParentFd(), msg);
            } catch (const std::exception& e) {
                std::cerr << "Failed to send status request: " << e.what() << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        _pollLoop.pollOnce(100);

        std::cout << "Status of kitchens:\n";
        for (size_t i = 0; i < _latestStatuses.size() && i < _kitchens.size(); ++i) {
            auto& status = _latestStatuses[i];
            std::cout << "Kitchen #" << i << "\n";
            std::cout << "  Total Cooks: " << status._totalCooks << "\n";
            std::cout << "  Busy Cooks: " << status._busyCooks << "\n";
            std::cout << "  Pizzas in queue: " << (i < _kitchenPizzaCounts.size() ? _kitchenPizzaCounts[i] : 0) << "\n";
            std::cout << "  Stock:\n";
            std::cout << "    Dough: " << status._stock[0] << "\n";
            std::cout << "    Tomato: " << status._stock[1] << "\n";
            std::cout << "    Gruyere: " << status._stock[2] << "\n";
            std::cout << "    Ham: " << status._stock[3] << "\n";
            std::cout << "    Mushrooms: " << status._stock[4] << "\n";
            std::cout << "    Steak: " << status._stock[5] << "\n";
            std::cout << "    Eggplant: " << status._stock[6] << "\n";
            std::cout << "    Goat Cheese: " << status._stock[7] << "\n";
            std::cout << "    Chief Love: " << status._stock[8] << "\n";
            std::cout << "  ---\n";
        }
    }

    void Reception::dispatchCommandsToKitchen(std::vector<std::shared_ptr<IPizza>> pizzas)
    {
        int limitOfPizzas = _numberOfCooksPerKitchen * 2;

        for (auto& pizza : pizzas) {
            int selectedKitchenIndex = -1;
            int minLoad = limitOfPizzas + 1;

            for (size_t i = 0; i < _kitchens.size(); ++i) {
                if (i < _kitchenPizzaCounts.size()) {
                    int currentLoad = _kitchenPizzaCounts[i];
                    if (currentLoad < limitOfPizzas && currentLoad < minLoad) {
                        selectedKitchenIndex = i;
                        minLoad = currentLoad;
                    }
                }
            }

            if (selectedKitchenIndex == -1) {
                this->createKitchen();
                selectedKitchenIndex = _kitchens.size() - 1;
            }

            std::vector<std::shared_ptr<IPizza>> singlePizza = {pizza};
            OrderMessageBuilder builder;
            OrderMessage order = builder.setType(MessageType::COMMAND).setPizzas(singlePizza).build();
            _kitchens[selectedKitchenIndex]._pipe->send(_kitchens[selectedKitchenIndex]._pipe->getParentFd(), order);

            _kitchenPizzaCounts[selectedKitchenIndex]++;

            std::cout << "Pizza dispatched to kitchen #" << selectedKitchenIndex
                      << " (now has " << _kitchenPizzaCounts[selectedKitchenIndex] << " pizzas)" << std::endl;
        }
    }

}
