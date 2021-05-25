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

#include "tab_action.hpp"
#include <vector>

using boost::asio::ip::udp;

class Party {

public:

    Party(std::string, int, int);
    ~Party();
    void join(Client *);
    std::string display(void);
    void quit(Client *);
    Client *getClient(boost::asio::ip::address);

    std::string get_port_party();

    std::vector<Client *> clients;
    Tab_action tab_actions;
    std::string name;
    int nb_co;
    int nb_max;
    bool full;
    bool launch;
    bool end;
    int id;
    int port_recv;
    int port_send;
};
