/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef RECEPTIONBUILDER_HPP
#define RECEPTIONBUILDER_HPP

#include "IBuilder.hpp"
#include "Reception/Reception.hpp"

namespace Plazza {
    class ReceptionBuilder : IBuilder<std::shared_ptr<Reception>> {
    public:
        ReceptionBuilder &setMultiplier(const std::string& multiplier);

        ReceptionBuilder &setNumberOfCooks(const std::string& numberOfCooks);

        ReceptionBuilder &setTimePerRestock(const std::string& timePerRestock);

        std::shared_ptr<Reception> build() override;

    private:
        int _multiplier = 0;
        int _numberOfCooks = 0;
        int _timePerRestock = 0;
    };
}



#endif //RECEPTIONBUILDER_HPP
