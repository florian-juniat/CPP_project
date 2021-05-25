/*
** EPITECH PROJECT, 2018
** serveur.cpp
** File description:
** serveur
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "serveur.hpp"

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    try {
        boost::asio::io_service io_service;  
        Server server(io_service);
        io_service.run();
    } catch(std::exception& e) {
        std::cerr << e.what() << endl;
    }
    return (0);
}
