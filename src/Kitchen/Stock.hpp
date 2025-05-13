/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Stock.hpp
*/

#ifndef PLAZZA_STOCK_HPP
#define PLAZZA_STOCK_HPP

namespace Plazza {
    class Stock{
        public:
            Stock();
        Stock(const Stock &other);
        ~Stock();
        Stock &operator=(const Stock &other);
        void restockAll(void);
        void addDough(int number);
        void addTomato(int number);
        void addGruyere(int number);
        void addHam(int number);
        void addMushrooms(int number);
        void addSteaks(int number);
        void addEggplant(int number);
        void addGoatCheese(int number);
        void addChiefLove(int number);
        void removeDough(int number);
        void removeTomato(int number);
        void removeGruyere(int number);
        void removeHam(int number);
        void removeMushrooms(int number);
        void removeSteaks(int number);
        void removeEggplant(int number);
        void removeGoatCheese(int number);
        void removeChiefLove(int number);
        int getNumberDough() const;
        int getNumberTomato() const;
        int getNumberGruyere() const;
        int getNumberHam() const;
        int getNumberMushrooms() const;
        int getNumberSteaks() const;
        int getNumberEggplant() const;
        int getNumberGoatCheese() const;
        int getNumberChiefLove() const;
        private:
            int _numberDough;
            int _numberTomato;
            int _numberGruyere;
            int _numberHam;
            int _numberMushrooms;
            int _numberSteaks;
            int _numberEggplant;
            int _numberGoatCheese;
            int _numberChiefLove;
    };
}

#endif //PLAZZA_STOCK_HPP
