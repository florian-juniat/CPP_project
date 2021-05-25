/*
** EPITECH PROJECT, 2018
** name
** File description:
** communicate
*/

#include "communicate.hpp"
#include <vector>

std::vector<std::string> split(std::string, char);

communicate::communicate(boost::asio::io_service& io_service, list_connect *con,
std::vector<boost::shared_ptr<tcp::socket>> *list_so, int n): sock(io_service)
{
    nb = n;
    list_sok = list_so;
    connect = con;
    pseudo = "";
    me = new user(pseudo, (*list_sok)[nb]);
    sok = (*list_sok)[nb];
}

tcp::socket& communicate::socket()
{
    return sock;
}

bool communicate::check_pseudo(std::string ps)
{
    bool one = false;

    for (contact str : all_contact.list)
        if (str.pseudo == ps)
            one = true;
    if (!one)
        return (false);
    if (connect->isconnect(ps) == NULL)
        return (true);
    return (false);
}

void communicate::start()
{
    boost::asio::write(*sok,
boost::asio::buffer("100 Connection established\nplease enter your pseudo\n"));
    launch();
}

void communicate::launch()
{
    (*(*list_sok)[nb]).async_read_some(
            boost::asio::buffer(data, max_length),
            boost::bind(&communicate::handle_read,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void communicate::call_someone(std::vector<std::string> recv_client)
{
    user *check = connect->isconnect(recv_client[1]);
    
    if (check) {
        boost::asio::write(*sok, boost::asio::buffer((
        "120 " + all_contact.get(recv_client[1]).in_str() + 
        " 7001 7000 \n")));
        boost::asio::write(*(check->sok), boost::asio::buffer(
        ("130 " + all_contact.get(pseudo).in_str()) + " 7000 7001 \n"));
    } else
        boost::asio::write(*sok, boost::asio::buffer("220 The client is not connected\n"));
    launch();
}

void communicate::command_pseudo(std::string str)
{
    if (check_pseudo(str)) {
        pseudo = str;
        me->pseudo = pseudo;
        connect->add_remove(me, true);
        boost::asio::write(*sok, boost::asio::buffer("101 Welcome " + pseudo + "\n"));
    } else {
        boost::asio::write(*sok, boost::asio::buffer("201 Pseudo already use\n"));
    }
}

void communicate::send_contact()
{
    std::string str = "";
    for (contact cont : all_contact.list)
        str = str + cont.pseudo + " ";
    boost::asio::write(*sok, boost::asio::buffer(str + "\n"));
}

void communicate::handle_read(const boost::system::error_code& err,
size_t bytes_transferred)
{
    std::vector<std::string> recv_client;
    std::string data2;
    
    if (!err) {
        data2 = data;
        recv_client = split(data2, ' ');
        if (recv_client[0] == "quit") {
            boost::asio::write(*sok, boost::asio::buffer("143 Good bye\n"));
            connect->add_remove(me, false);
            sok->close();
            return;
        }
        if (recv_client[0] == "pseudo") {
            command_pseudo(recv_client[1]);
            launch();
            return;
        }
        if (pseudo == "") {
            boost::asio::write(*sok, boost::asio::buffer("300 You have to enter a pseudo first\n"));
            launch();
            return;
        }
        if (recv_client[0] == "call") {
            call_someone(recv_client);
            launch();
            return;
        }
        if (recv_client[0] == "contact") {
            send_contact();
            launch();
            return;
        }
        boost::asio::write(*sok, boost::asio::buffer("200 bad command\n"));
        launch();
        return;
    }
    sok->close();
}
