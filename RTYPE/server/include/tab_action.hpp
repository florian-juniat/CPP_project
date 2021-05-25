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

#include <vector>
#include <mutex>

using boost::asio::ip::udp;

#include "action.hpp"

class Tab_action {

public:

    Tab_action();
    ~Tab_action();
    void add(Action);
    Action get(void);

    std::vector<Action> actions;
    std::mutex mut;

};
