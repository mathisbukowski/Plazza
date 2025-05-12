/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** PizzaType
*/

#ifndef PIZZATYPE_HPP_
#define PIZZATYPE_HPP_

namespace Plazza
{
    enum PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };
    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    class Pizza {
        public:
            Pizza(PizzaType type, PizzaSize size, int quantity)
                : _type(type), _size(size), _quantity(quantity) {}

            PizzaType getType() const { return _type; }
            PizzaSize getSize() const { return _size; }
            int getQuantity() const { return _quantity; }
        private:
            PizzaType _type;
            PizzaSize _size;
            int _quantity;
    };
}

#endif /* !PIZZATYPE_HPP_ */
