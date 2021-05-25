/*
** EPITECH PROJECT, 2018
** party.cpp
** File description:
** party
*/

#include "party.hpp"

Party::Party(std::string na, int max, int port)
{
    static int num_party = 0;

    num_party++;
    id = num_party;
    name = na;
    full = false;
    nb_co = 0;
    nb_max = max;
    end = false;
    launch = false;
    port_recv = port + num_party * 2;
    port_send = port + num_party * 2 + 1;
}

Party::~Party()
{
}

void Party::join(Client *client)
{
    if (full)
        return;
    nb_co++;
    clients.push_back(client);
    if (nb_co >= nb_max)
        full = true;
}

std::string Party::display(void)
{
    std::string ret = "";
    int count = 0;

    ret = ret + "-----" + name + "-----\n";
    for (Client *c : clients) {
        ret = ret + " > " + c->pseudo + "\n";
        count++;
    }
    while (count < nb_max) {
        ret = ret + " > \n";
        count++;
    }
    return (ret);
}

void Party::quit(Client *cl)
{
    int n = -1;
    int count = 0;

    for (Client *c : clients) {
        if (c->num_client == cl->num_client)
            n = count;
        count++;
    }
    if (n != -1) {
        clients.erase(clients.begin() + n);
        nb_co--;
        full = false;
    }
}

std::string Party::get_port_party()
{
    std::string recv_ = std::to_string(port_recv);
    std::string send_ = std::to_string(port_send);

    return (recv_ + " " + send_);
}

Client *Party::getClient(boost::asio::ip::address ip)
{
    for (Client *c : clients) {
        if (c->ip == ip)
            return (c);
    }
    return (NULL);
}
