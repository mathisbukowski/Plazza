/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Stock.cpp
*/

#include "Stock.hpp"

Plazza::Stock::Stock()
{
    _numberDough = 0;
    _numberTomato = 0;
    _numberGruyere = 0;
    _numberHam = 0;
    _numberMushrooms = 0;
    _numberSteaks = 0;
    _numberEggplant = 0;
    _numberGoatCheese = 0;
    _numberChiefLove = 0;
}

Plazza::Stock::Stock(const Plazza::Stock &other)
{
    _numberDough = other._numberDough;
    _numberTomato = other._numberTomato;
    _numberGruyere = other._numberGruyere;
    _numberHam = other._numberHam;
    _numberMushrooms = other._numberMushrooms;
    _numberSteaks = other._numberSteaks;
    _numberEggplant = other._numberEggplant;
    _numberGoatCheese = other._numberGoatCheese;
    _numberChiefLove = other._numberChiefLove;
}

Plazza::Stock::Stock(int numberDough, int numberTomato, int numberGruyere, int numberHam, int numberMushrooms,
    int numberSteaks, int numberEggplant, int numberGoatCheese, int numberChiefLove)
{
    _numberDough = numberDough;
    _numberTomato = numberTomato;
    _numberGruyere = numberGruyere;
    _numberHam = numberHam;
    _numberMushrooms = numberMushrooms;
    _numberSteaks = numberSteaks;
    _numberEggplant = numberEggplant;
    _numberGoatCheese = numberGoatCheese;
    _numberChiefLove = numberChiefLove;
}

Plazza::Stock::~Stock()
{
}

Plazza::Stock &Plazza::Stock::operator=(const Plazza::Stock &other)
{
    if (this != &other) {
        _numberDough = other._numberDough;
        _numberTomato = other._numberTomato;
        _numberGruyere = other._numberGruyere;
        _numberHam = other._numberHam;
        _numberMushrooms = other._numberMushrooms;
        _numberSteaks = other._numberSteaks;
        _numberEggplant = other._numberEggplant;
        _numberGoatCheese = other._numberGoatCheese;
        _numberChiefLove = other._numberChiefLove;
    }
    return *this;
}

void Plazza::Stock::addDough(int number)
{
    _numberDough += number;
}

void Plazza::Stock::addTomato(int number)
{
    _numberTomato += number;
}

void Plazza::Stock::addGruyere(int number)
{
    _numberGruyere += number;
}

void Plazza::Stock::addHam(int number)
{
    _numberHam += number;
}

void Plazza::Stock::addMushrooms(int number)
{
    _numberMushrooms += number;
}

void Plazza::Stock::addSteaks(int number)
{
    _numberSteaks += number;
}

void Plazza::Stock::addEggplant(int number)
{
    _numberEggplant += number;
}

void Plazza::Stock::addGoatCheese(int number)
{
    _numberGoatCheese += number;
}

void Plazza::Stock::addChiefLove(int number)
{
    _numberChiefLove += number;
}

void Plazza::Stock::removeDough(int number)
{
    if (_numberDough - number >= 0) {
        _numberDough -= number;
        return;
    }
    _numberDough = 0;
}

void Plazza::Stock::removeTomato(int number)
{
    if (_numberTomato - number >= 0) {
        _numberTomato -= number;
        return;
    }
    _numberTomato = 0;
}

void Plazza::Stock::removeGruyere(int number)
{
    if (_numberGruyere - number >= 0) {
        _numberGruyere -= number;
        return;
    }
    _numberGruyere = 0;
}

void Plazza::Stock::removeHam(int number)
{
    if (_numberHam - number >= 0) {
        _numberHam -= number;
        return;
    }
    _numberHam = 0;
}

void Plazza::Stock::removeMushrooms(int number)
{
    if (_numberMushrooms - number >= 0) {
        _numberMushrooms -= number;
        return;
    }
    _numberMushrooms = 0;
}

void Plazza::Stock::removeSteaks(int number)
{
    if (_numberSteaks - number >= 0) {
        _numberSteaks -= number;
        return;
    }
    _numberSteaks = 0;
}

void Plazza::Stock::removeEggplant(int number)
{
    if (_numberEggplant - number >= 0) {
        _numberEggplant -= number;
        return;
    }
    _numberEggplant = 0;
}

void Plazza::Stock::removeGoatCheese(int number)
{
    if (_numberGoatCheese - number >= 0) {
        _numberGoatCheese -= number;
        return;
    }
    _numberGoatCheese = 0;
}

void Plazza::Stock::removeChiefLove(int number)
{
    if (_numberChiefLove - number >= 0) {
        _numberChiefLove -= number;
        return;
    }
    _numberChiefLove = 0;
}

int Plazza::Stock::getNumberDough() const
{
    return _numberDough;
}

int Plazza::Stock::getNumberTomato() const
{
    return _numberTomato;
}

int Plazza::Stock::getNumberGruyere() const
{
    return _numberGruyere;
}

int Plazza::Stock::getNumberHam() const
{
    return _numberHam;
}

int Plazza::Stock::getNumberMushrooms() const
{
    return _numberMushrooms;
}

int Plazza::Stock::getNumberSteaks() const
{
    return _numberSteaks;
}

int Plazza::Stock::getNumberEggplant() const
{
    return _numberEggplant;
}

int Plazza::Stock::getNumberGoatCheese() const
{
    return _numberGoatCheese;
}

int Plazza::Stock::getNumberChiefLove() const
{
    return _numberChiefLove;
}