/*
** EPITECH PROJECT, 2018
** action.cpp
** File description:
** action
*/

#include "action.hpp"

Action::Action(Client *c, std::string act)
{
    static int num_action = 0;

    num_action++;
    id = num_action;
    action = act;
    client = c;
}

Action::~Action()
{
}
