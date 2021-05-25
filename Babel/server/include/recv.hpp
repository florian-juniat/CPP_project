/*
** EPITECH PROJECT, 2018
** recv.hpp
** File description:
** recv
*/

using namespace boost;
using namespace boost::asio;
using ip::tcp;
using std::string;

class recv
{
    public:
        recv(tcp::socket &socket);
        ~recv();
};
