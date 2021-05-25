/*
** EPITECH PROJECT, 2018
** serveur.cpp
** File description:
** serveur
*/

#include <boost/asio.hpp>
#include <iostream>
#include "serveur.hpp"

void Server::start_accept()
{
    list_sok.push_back(boost::shared_ptr<tcp::socket>(new tcp::socket(acceptor_.get_io_service())));
    communicate::pointer connection = communicate::create(acceptor_.get_io_service(), connect, &list_sok, list_sok.size() - 1);
    acceptor_.async_accept(*list_sok[list_sok.size() - 1],
        boost::bind(&Server::handle_accept, this, connection,
        boost::asio::placeholders::error));
}
  
Server::Server(boost::asio::io_service& io_service): acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234))
{
    connect = new list_connect();
    start_accept();
}

void Server::handle_accept(communicate::pointer connection, const boost::system::error_code& err)
{
    if (!err) {
        connection->start();
    }
    start_accept();
}
