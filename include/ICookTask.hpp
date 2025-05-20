/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** ICookTask
*/

#ifndef ICOOKTASK_HPP_
#define ICOOKTASK_HPP_

class ICookTask {
public:
    virtual ~ICookTask() = default;
    virtual void execute() = 0;
};

#endif //ICOOKTASK_HPP_
