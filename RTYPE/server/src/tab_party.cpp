/*
** EPITECH PROJECT, 2018
** tab_party.cpp
** File description:
** tab_party
*/

#include "tab_party.hpp"

TabParty::TabParty()
{
}

TabParty::~TabParty()
{
}

Party *TabParty::getParty(std::string name)
{
    for (Party *c : partys) {
        if (c->name == name)
            return (c);
    }
    return (NULL);
}

void TabParty::addParty(Party *c)
{
    partys.push_back(c);
}

void TabParty::removeParty(Party *c)
{
    int count = 0;
    int n = -1;

    for (Party *p : partys) {
        if (p->name == c->name)
            n = count;
        count++;
    }
    if (n != -1)
        partys.erase(partys.begin() + n);
}

void TabParty::quit(Client *c)
{
    for (Party *p : partys)
        p->quit(c);
}

std::string TabParty::display(void)
{
    std::string ret = "";

    for (Party *p : partys)
        ret = ret + p->display() + "\n";
    return (ret);
}
