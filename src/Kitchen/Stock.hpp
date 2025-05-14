/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Stock.hpp
*/

#ifndef PLAZZA_STOCK_HPP
#define PLAZZA_STOCK_HPP

namespace Plazza {
    /**
     * @class Stock
     * Class representing the stock of ingredients in the kitchen.
     * It manages the quantities of various ingredients and provides methods to add or remove them.
     */
    class Stock{
        public:
            /**
             * Default constructor to initialize the stock with default values.
             */
            Stock();
            /**
             * Constructor to initialize the stock with another stock.
             * @param other The stock to copy
             */
            Stock(const Stock &other);
            /**
             * Destructor to clean up the stock.
             */
            ~Stock();
            /**
             * Operator to check if two stocks are equal.
             * @param other The stock to compare with
             * @return True if the stocks are equal, false otherwise
             */
            Stock &operator=(const Stock &other);

            /**
             * Restock all ingredients in the stock to their default values.
             * 
             */
            void restockAll(void);
            /**
             * Add dough to the stock.
             * @param number The number of dough to add
             */
            void addDough(int number);
            /**
             * Add tomato to the stock.
             * @param number The number of tomatoes to add
             */
            void addTomato(int number);
            /**
             * Add gruyere to the stock.
             * @param number The number of gruyere to add
             */
            void addGruyere(int number);
            /**
             * Add ham to the stock.
             * @param number The number of ham to add
             */
            void addHam(int number);
            /**
             * Add mushrooms to the stock.
             * @param number The number of mushrooms to add
             */
            void addMushrooms(int number);
            /**
             * Add steaks to the stock.
             * @param number The number of steaks to add
             */
            void addSteaks(int number);
            /**
             * Add eggplant to the stock.
             * @param number The number of eggplants to add
             */
            void addEggplant(int number);
            /**
             * Add goat cheese to the stock.
             * @param number The number of goat cheese to add
             */
            void addGoatCheese(int number);
            /**
             * Add chief love to the stock.
             * @param number The number of chief love to add
             */
            void addChiefLove(int number);
            /**
             * Remove dough from the stock.
             * @param number The number of dough to remove
             */
            void removeDough(int number);
            /**
             * Remove tomato from the stock.
             * @param number The number of tomatoes to remove
             */
            void removeTomato(int number);
            /**
             * Remove gruyere from the stock.
             * @param number The number of gruyere to remove
             */
            void removeGruyere(int number);
            /**
             * Remove ham from the stock.
             * @param number The number of ham to remove
             */
            void removeHam(int number);
            /**
             * Remove mushrooms from the stock.
             * @param number The number of mushrooms to remove
             */
            void removeMushrooms(int number);
            /**
             * Remove steaks from the stock.
             * @param number The number of steaks to remove
             */
            void removeSteaks(int number);
            /**
             * Remove eggplant from the stock.
             * @param number The number of eggplants to remove
             */
            void removeEggplant(int number);
            /**
             * Remove goat cheese from the stock.
             * @param number The number of goat cheese to remove
             */
            void removeGoatCheese(int number);
            /**
             * Remove chief love from the stock.
             * @param number The number of chief love to remove
             */
            void removeChiefLove(int number);
            /**
             * Get the number of dough in the stock.
             * @return The number of dough in the stock
             */
            int getNumberDough() const;
            /**
             * Get the number of tomatoes in the stock.
             * @return The number of tomatoes in the stock
             */
            int getNumberTomato() const;
            /**
             * Get the number of gruyere in the stock.
             * @return The number of gruyere in the stock
             */
            int getNumberGruyere() const;
            /**
             * Get the number of ham in the stock.
             * @return The number of ham in the stock
             */
            int getNumberHam() const;
            /**
             * Get the number of mushrooms in the stock.
             * @return The number of mushrooms in the stock
             */
            int getNumberMushrooms() const;
            /**
             * Get the number of steaks in the stock.
             * @return The number of steaks in the stock
             */
            int getNumberSteaks() const;
            /**
             * Get the number of eggplants in the stock.
             * @return The number of eggplants in the stock
             */
            int getNumberEggplant() const;
            /**
             * Get the number of goat cheese in the stock.
             * @return The number of goat cheese in the stock
             */
            int getNumberGoatCheese() const;
            /**
             * Get the number of chief love in the stock.
             * @return The number of chief love in the stock
             */
            int getNumberChiefLove() const;
        private:
            int _numberDough; ///> Number of dough in the stock
            int _numberTomato; ///> Number of tomatoes in the stock
            int _numberGruyere; ///> Number of gruyere in the stock
            int _numberHam; ///> Number of ham in the stock
            int _numberMushrooms; ///> Number of mushrooms in the stock
            int _numberSteaks; ///> Number of steaks in the stock
            int _numberEggplant; ///> Number of eggplants in the stock
            int _numberGoatCheese; ///> Number of goat cheese in the stock
            int _numberChiefLove; ///> Number of chief love in the stock
    };
}

#endif //PLAZZA_STOCK_HPP
