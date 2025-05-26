/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#include "ReceptionBuilder.hpp"

namespace Plazza {
    static int safeStrToInt(const std::string &str)
    {
        errno = 0;
        char *end = nullptr;
        long val = std::strtol(str.c_str(), &end, 10);

        if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
            throw std::out_of_range("Integer value out of range: " + str);
        }

        if (end == str.c_str() || *end != '\0') {
            throw std::invalid_argument("Invalid integer value: " + str);
        }

        return static_cast<int>(val);
    }

    static int safeStrToDouble(const std::string &str)
    {
        errno = 0;
        char *end = nullptr;
        double val = std::strtod(str.c_str(), &end);

        if (errno == ERANGE || val < -DBL_MAX || val > DBL_MAX) {
            throw std::out_of_range("Double value out of range: " + str);
        }

        if (end == str.c_str() || *end != '\0') {
            throw std::invalid_argument("Invalid double value: " + str);
        }

        return static_cast<int>(val);
    }

    ReceptionBuilder& ReceptionBuilder::setMultiplier(const std::string& multiplier)
    {
        _multiplier = safeStrToDouble(multiplier);
        return *this;
    }

    ReceptionBuilder& ReceptionBuilder::setNumberOfCooks(const std::string& numberOfCooks)
    {
        _numberOfCooks = safeStrToInt(numberOfCooks);
        return *this;
    }

    ReceptionBuilder& ReceptionBuilder::setTimePerRestock(const std::string& timePerRestock)
    {
        _timePerRestock = safeStrToInt(timePerRestock);
        return *this;
    }

    std::shared_ptr<Reception> ReceptionBuilder::build()
    {
        return std::make_shared<Reception>(_multiplier, _numberOfCooks, _timePerRestock);
    }



}