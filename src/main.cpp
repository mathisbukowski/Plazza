/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** main
*/

#include <iostream>

#include "Build/ReceptionBuilder.hpp"
#include "Reception/Reception.hpp"
#include "Logger/Logger.hpp"

int main(int ac, char **av)
{
    if (ac != 4 || !av || !av[1] || !av[2] || !av[3]) {
        std::cerr << "Usage: " << av[0] << " <multiplierCookingTime> <numberOfCooksPerKitchen> <timeToRestockIngredients>" << std::endl;
        return 84;
    }
    std::shared_ptr<Plazza::Reception> reception;

    try {
        Plazza::Logger::getInstance().setLogFile("plazza.log");
        Plazza::ReceptionBuilder receptionBuilder;

        reception = receptionBuilder.setMultiplier(av[1]).setNumberOfCooks(av[2]).setTimePerRestock(av[3]).build();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    reception->run();
    return 0;
}
