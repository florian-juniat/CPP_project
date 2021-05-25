/*
** EPITECH PROJECT, 2018
** recv.cpp
** File description:
** revp
*/

#include <boost/asio.hpp>
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <boost/array.hpp>

using namespace boost::asio::ip;

int main(int ac, char **av)
{
  try
  {
    boost::asio::io_service io_service;
    boost::asio::ip::udp::endpoint endpoint (boost::asio::ip::address::from_string(av[1]), atoi(av[2]));
    boost::asio::ip::udp::endpoint sender;
 
    boost::asio::ip::udp::socket socket(io_service);
    socket.open(udp::v4());
    socket.bind(endpoint); // <------
 
    boost::array<char, 128> recv_buf;
    size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender);
 
    std::cout.write(recv_buf.data(), len);
 
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
 
  return 0;
 
}
