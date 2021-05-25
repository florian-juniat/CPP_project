/*
** EPITECH PROJECT, 2018
** name
** File description:
** serveur
*/


#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;

#include "communicate.hpp"

class Server 
{
public:
    boost::asio::io_service io;
    std::vector<boost::shared_ptr<tcp::socket>> list_sok;
    list_connect *connect;
    tcp::acceptor acceptor_;
    void start_accept();

    Server(boost::asio::io_service& io_service);
    void handle_accept(communicate::pointer conn, const boost::system::error_code& err);
};
