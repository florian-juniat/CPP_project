/*
** EPITECH PROJECT, 2018
** tab_client.cpp
** File description:
** tabclient
*/

#include "tab_client.hpp"

TabClient::TabClient()
{
}

TabClient::~TabClient()
{
}

Client *TabClient::getClient(udp::endpoint cli)
{
    for (Client *c : clients) {
        if (c->end == cli)
            return (c);
    }
    return (NULL);
}

void TabClient::addClient(Client *cli)
{
    clients.push_back(cli);
}

void TabClient::removeClient(Client *cli)
{
    int ret = -1;
    int count = 0;

    for (Client *c : clients) {
        if (c->end == cli->end)
            ret = count;
        count++;
    }
    if (ret != -1)
        clients.erase(clients.begin() + ret);
}
