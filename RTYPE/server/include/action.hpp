/*
** EPITECH PROJECT, 2018
** client.hpp
** File description:
** client
*/

#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

#include "tab_client.hpp"

class Action {

public:

    Action(Client *, std::string);
    ~Action();

    Client *client;
    std::string action;
    int id;
};
