/*
** EPITECH PROJECT, 2018
** name
** File description:
** communicate
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <vector>

#include "contact.hpp"
#include "list_connect.hpp"

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;

class communicate : public boost::enable_shared_from_this<communicate>
{
public:
    user *me;
    std::vector<boost::shared_ptr<tcp::socket>> *list_sok;
    contact_list all_contact;
    enum { max_length = 1024 };
    char data[max_length];
    std::string pseudo = "";
    list_connect *connect;
    int nb;

    boost::shared_ptr<tcp::socket> sok;
    tcp::socket sock;
    typedef boost::shared_ptr<communicate> pointer;
    communicate(boost::asio::io_service& io_service, list_connect*,
    std::vector<boost::shared_ptr<tcp::socket>> *, int nb);
    static pointer create(boost::asio::io_service& io_service, list_connect*con,
    std::vector<boost::shared_ptr<tcp::socket>> *list_so, int n)
    {
        return (pointer(new communicate(io_service, con, list_so, n)));
    }
    void call_someone(std::vector<std::string>);
    void command_pseudo(std::string);
    tcp::socket& socket();
    void start();
    void launch();
    void send_contact();
    bool check_pseudo(std::string);

    void handle_read(const boost::system::error_code& err, size_t bytes_transferred);
};
