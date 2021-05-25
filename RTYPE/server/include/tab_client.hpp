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

#include "client.hpp"
#include <vector>

using boost::asio::ip::udp;

class TabClient {

public:
    std::vector<Client *> clients;
    
    TabClient();
    ~TabClient();

    Client *getClient(udp::endpoint);
    void addClient(Client *);
    void removeClient(Client *);
};
