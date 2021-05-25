/*
** EPITECH PROJECT, 2018
** serveur.cpp
** File description:
** serveur
*/

#include <thread>
#include <stdio.h>
#include <boost/bind.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost;
using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

#include "my.hpp"

void communicate(tcp::socket &socket);

string read_(tcp::socket & socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until( socket, buf, "\n" );
    string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

void send_(tcp::socket socket, const string& message) {
    const string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(message) );
}

void test(boost::shared_ptr<tcp::socket> sok)
{
}

int main(int ac, char **av)
{
    const int BACKLOG_SIZE = 30;
    int nb_client = 2;
    int nb_connect = 0;
    boost::asio::io_service ios;
    bool stop = false;

    asio::ip::address ip_address = asio::ip::address_v4::any();
    asio::ip::tcp::endpoint ep(ip_address, atoi(av[1]));

    try {
        while (!stop) {
            asio::ip::tcp::acceptor acceptor(ios, ep.protocol());
            boost::system::error_code ec;
            acceptor.bind(ep);
            acceptor.listen(BACKLOG_SIZE);
            asio::ip::tcp::socket sock(ios);
            acceptor.accept(sock);
            //send_(sock, "Connecté\n");
            boost::thread t{test, sock};
            t.join();
        }
    } catch (system::system_error &e) {
        std::cout << "Error" << std::endl;
        return (84);
    }
   return 0;
}
