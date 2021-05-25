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

class Client {

public:
    
    Client(udp::endpoint, std::string);
    ~Client();
    void send_message(std::string);

    boost::asio::io_service io_service;
    udp::socket *socket;
    boost::asio::ip::address ip;


    int port_response;
    std::string pseudo;
    udp::endpoint end;

    int num_client;
    bool in_party;
    int id_party;

    int score;
    int vie;

    int x;
    int y;
};
