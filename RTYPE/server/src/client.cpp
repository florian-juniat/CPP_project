/*
** EPITECH PROJECT, 2018
** client.cpp
** File description:
** client
*/

#include "client.hpp"

Client::Client(udp::endpoint uu, std::string name)
{
    static int num_client2 = 0;

    pseudo = name;
    end = uu;
    ip = end.address();
    num_client = num_client2;
    num_client2++;
    x = 100;
    y = 0;
}

Client::~Client()
{
}

void Client::send_message(std::string message)
{
    socket->send_to(boost::asio::buffer(message, message.length()), end);
}


