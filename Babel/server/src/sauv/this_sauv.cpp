/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** main
*/



#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost;
using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;


class con_handler : public boost::enable_shared_from_this<con_handler>
{
    private:
        tcp::socket sock;
        std::string message="Hello From Server!";

    public:
        typedef boost::shared_ptr<con_handler> pointer;
        con_handler(boost::asio::io_service& io_service): sock(io_service){}

        static pointer create(boost::asio::io_service& io_service)
        {
            return pointer(new con_handler(io_service));
        }

        tcp::socket& socket()
        {
            return sock;
        }
        
        std::string read_() {
            boost::asio::streambuf buf;
            boost::asio::read_until(sock, buf, "\n" );
            std::string data = boost::asio::buffer_cast<const char*>(buf.data());
            return data;
        }

        void send_(const std::string& message) {
            const std::string msg = message + "\n";
            boost::asio::write(sock, boost::asio::buffer(message));
        }

        void start()
        {
            while (true) {
                std::string data = read_();
                std::cout << data << "\n" << std::endl;
                send_("receiv : " + data + "\n");
            }
        }
};



class Server 
{
    private:
        tcp::acceptor my_accept;
        con_handler::pointer connection;

        void start_accept()
        {
            connection = con_handler::create(my_accept.get_io_service());

            my_accept.async_accept(connection->socket(),
            boost::bind(&Server::handle_accept, this, connection,
            boost::asio::placeholders::error));
        }
    
    public:
        Server(boost::asio::io_service& io_service): my_accept(io_service, tcp::endpoint(tcp::v4(), 1234))
        {
            start_accept();
        }
        void handle_accept(con_handler::pointer connection, const boost::system::error_code& err)
        {
            if (!err)
                connection->start();
            start_accept();
        }
};





int main(int argc, char **argv)
{
    try {
        boost::asio::io_service io_service;  
        Server server(io_service);
        io_service.run();
    } catch(std::exception& e) {
        std::cerr << "Problem" << endl;
    }
    return (0);
}
