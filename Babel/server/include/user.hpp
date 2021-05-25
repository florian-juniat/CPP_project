/*
** EPITECH PROJECT, 2018
** user.hpp
** File description:
** user
*/

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;
using ip::tcp;

class user
{   
public:
    std::string pseudo;
    boost::shared_ptr<tcp::socket> sok;
    user(std::string ps, boost::shared_ptr<tcp::socket> ss) : sok(ss)
    {
        pseudo = ps;
    }
};
