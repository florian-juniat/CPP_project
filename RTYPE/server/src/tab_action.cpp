/*
** EPITECH PROJECT, 2018
** tab_action.cpp
** File description:
** tab_action
*/

#include "tab_action.hpp"

Tab_action::Tab_action()
{
}

Tab_action::~Tab_action()
{
}

void Tab_action::add(Action ac)
{
    mut.lock();
    actions.push_back(ac);
    mut.unlock();
}

Action Tab_action::get(void)
{
    Action ret(NULL, "null");

    mut.lock();
    if (actions.size() > 0) {
        ret = actions[0];
        actions.erase(actions.begin());
    }
    mut.unlock();
    return ret;
}
