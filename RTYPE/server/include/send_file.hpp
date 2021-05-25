/*
** EPITECH PROJECT, 2018
** client.hpp
** File description:
** sendfile
*/

#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

class SendFile {

public:
    SendFile(int, std::string);
    ~SendFile();
    void start();
    std::string display();

    std::vector<std::string> photos;
    int port_recv;
    int port_send;
    std::string ip;
};
