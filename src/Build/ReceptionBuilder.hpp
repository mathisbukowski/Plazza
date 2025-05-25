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
    /**
     * @class ReceptionBuilder
     * Builder for creating a Reception object.
     * This class provides methods to set the multiplier, number of cooks, and time per restock.
     */
    class ReceptionBuilder : IBuilder<std::shared_ptr<Reception>> {
    public:
        /**
         * Sets the multiplier for the cooking time.
         * @param multiplier The multiplier value to set.
         * @return Reference to the builder instance for method chaining.
         */
        ReceptionBuilder &setMultiplier(const std::string& multiplier);
        /**
         * Sets the number of cooks in the reception.
         * @param numberOfCooks The number of cooks to set.
         * @return Reference to the builder instance for method chaining.
         */
        ReceptionBuilder &setNumberOfCooks(const std::string& numberOfCooks);
        /**
         * Sets the time per restock for ingredients.
         * @param timePerRestock The time in seconds to set for restocking ingredients.
         * @return Reference to the builder instance for method chaining.
         */
        ReceptionBuilder &setTimePerRestock(const std::string& timePerRestock);
        /**
         * Builds the Reception object with the specified properties.
         * @return A shared pointer to a Reception object with the set properties.
         */
        std::shared_ptr<Reception> build() override;

    private:
        int _multiplier = 0; ///> The multiplier for the cooking time, default is 0.
        int _numberOfCooks = 0; ///> The number of cooks in the reception, default is 0.
        int _timePerRestock = 0; ///> The time in seconds for restocking ingredients, default is 0.
    };
}



#endif //RECEPTIONBUILDER_HPP
