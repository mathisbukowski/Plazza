/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Reception
*/

#include "Tools/Tools.hpp"
#include "Reception.hpp"

namespace Plazza {
    Reception::~Reception()
    {
        if (_running)
            return;
        for (auto kitchen : _kitchens) {
            if (kitchen == -1)
                continue;
            if (Tools::toolWaitPid(kitchen, _status) == -1)
                std::cerr << "Error while waiting for kitchen process" << std::endl;
        }
        _kitchens.clear();
        _running = false;
    }

    void Reception::addKitchen(pid_t pid)
    {
        this->_kitchens.emplace_back(pid);
    }

    int Reception::run()
    {
        _running = true;
        try {
            this->createKitchen();
        } catch (const ReceptionException& e) {
            std::cerr << "Reception Error: " << e.what() << std::endl;
            return 84;
        }
        return 0;
    }

    void Reception::createKitchen()
    {
        pid_t newKitchen = Tools::toolFork();

        if (newKitchen == -1)
            throw ReceptionException("Error while forking new kitchen");
        if (newKitchen == 0)
            throw ReceptionException("Error while forking new kitchen: already in child process");
        this->addKitchen(newKitchen);
    }


}