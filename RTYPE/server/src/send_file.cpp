/*
** EPITECH PROJECT, 2018
** send_file.cpp
** File description:
** sendfile
*/

#include "send_file.hpp"
#include <fstream>

using boost::asio::ip::udp;

std::string substrr(std::string str, int n_start, int n_stop)
{
    std::string ret = "";

    for (int i = n_start; i < n_stop; i++) {
        ret += str[i];
    }
    return (ret);
}

SendFile::SendFile(int port, std::string str)
{
    static int num_send = 1;

    port_recv = port - num_send * 2;
    port_send = port - num_send * 2 - 1;
    ip = str;

    photos.push_back("img/r-typesheet30a.png");
    photos.push_back("img/enemy.png");
    photos.push_back("img/r-typesheet14.gif");
    photos.push_back("img/r-typesheet1.gif");
    photos.push_back("img/space2.png");
    photos.push_back("img/space.png");
    photos.push_back("img/SpaceShip.png");

    num_send++;
}

SendFile::~SendFile()
{
}

std::string SendFile::display()
{
    return (std::to_string(port_recv) + " " + std::to_string(port_send));
}

void SendFile::start()
{
    std::cout << "Wait to send file to " << port_send << std::endl;
    boost::asio::io_service io_service;

    udp::endpoint send_end(boost::asio::ip::address::from_string(ip), port_send);
    udp::socket socket(io_service);
    socket.open(udp::v4());


    boost::asio::io_service ios;
    udp::socket socket_check(ios, udp::endpoint(udp::v4(), port_recv));
    udp::endpoint remote;
    boost::system::error_code error;

    int n, len, size;
    char *aa = (char *)malloc(10);
    
    socket_check.receive_from(boost::asio::buffer(aa, 3), remote, 0, error);

    std::cout << "Start to send file" << std::endl;

    int count = 0;
    int max_name = photos.size();
    
    for (std::string name : photos) {
        std::ifstream fin(name, std::ios::binary);
        char ch;
        std::string str = "";
        while (fin.read((char *)&ch, sizeof(ch)))
            str += ch;
        n = 0;
        len = str.size();
        size = 10000;
        while (n < len) {
            std::string sendd = substrr(str, n, n + size);
            n += size;
            socket.send_to(boost::asio::buffer(sendd, size), send_end);
            socket_check.receive_from(boost::asio::buffer(aa, 3), remote, 0, error);
        }
        count++;
        if (count < max_name)
            socket.send_to(boost::asio::buffer("next", 4), send_end);
        fin.close();
    }
    socket.send_to(boost::asio::buffer("stop", 4), send_end);
    std::cout << "End send files" << std::endl;
}
