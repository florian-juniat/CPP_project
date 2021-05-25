/*
** EPITECH PROJECT, 2018
** list_connect.cpp
** File description:
** list_connect
*/

#include <iostream>
#include "list_connect.hpp"

list_connect::list_connect()
{
}

user *list_connect::isconnect(std::string ps)
{
    for (user *str : list) {
        if (ps == str->pseudo)
            return (str);
    }
    return (NULL);
}

void list_connect::add_remove(user *pseudo, bool type)
{
    int count = 0;
    int del = -1;

    mut.lock();
    if (type) {
        list.push_back(pseudo);
    } else {
        for (user *str : list) {
            if (pseudo->pseudo == str->pseudo)
                del = count;
            count++;
        }
        if (del != -1)
            list.erase(list.begin() + del);
    }
    mut.unlock();
}
