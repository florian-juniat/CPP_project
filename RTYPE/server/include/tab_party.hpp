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

#include "party.hpp"
#include <vector>

using boost::asio::ip::udp;

class TabParty {

public:
    std::vector<Party *> partys;
    
    TabParty();
    ~TabParty();

    Party *getParty(std::string);
    void addParty(Party *);
    void removeParty(Party *);
    void quit(Client *);
    std::string display();
};
