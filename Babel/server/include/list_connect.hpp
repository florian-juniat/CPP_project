/*
** EPITECH PROJECT, 2018
** list_connect.cpp
** File description:
** list_connect
*/

#include <mutex>
#include <vector>
#include <string>

#include "user.hpp"

class list_connect
{
public:
    std::vector<user *> list;
    std::mutex mut;
    list_connect();
    user *isconnect(std::string);
    void add_remove(user *, bool); // one -> add , two -> remove
};
