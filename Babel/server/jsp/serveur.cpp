/*
** EPITECH PROJECT, 2018
** serveur.cpp
** File description:
** serveur
*/

#include <stdio.h>
#include <boost/bind.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;
using namespace boost;
using namespace boost::asio;
using std::vector;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

string read_(tcp::socket & socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until( socket, buf, "\n" );
    string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

void send_(tcp::socket & socket, const string& message) {
    const string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(message) );
}

int main(int ac, char **av)
{
    const int BACKLOG_SIZE = 30;
    vector<shared_ptr<tcp::socket> > sok;
    int nb_client = 2;
    int nb_connect = 0;
    boost::asio::io_service ios;

    tcp::resolver resolver(ios);
    tcp::resolver::query query(boost::asio::ip::host_name(), "");
    tcp::resolver::iterator iter = resolver.resolve(query);
    tcp::resolver::iterator end; // End marker.
    while (iter != end)
    {
        tcp::endpoint epy = *iter++;
        std::cout << epy << std::endl;
    }

    asio::ip::address ip_address = asio::ip::address_v4::any();
    asio::ip::tcp::endpoint ep(ip_address, atoi(av[1])); // --> create endpoint


    try {
        asio::ip::tcp::acceptor acceptor(ios, ep.protocol());
        boost::system::error_code ec;
        acceptor.bind(ep);
        acceptor.listen(BACKLOG_SIZE);
        asio::ip::tcp::socket sock(ios);
        acceptor.accept(sock);
        send_(sock, "salut\n");
    } catch (system::system_error &e) {
        std::cout << "Error" << std::endl;
        return (84);
    }
   return 0;
}
