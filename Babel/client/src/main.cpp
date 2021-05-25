/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** main
*/

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>


using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;
using boost::asio::ip::udp;

bool stopTemp;

int call(std::string name, std::string, int, int, bool *);


std::vector<std::string> split(std::string str, char c)
{
    std::string stock = "";
    std::vector<std::string> ret;

    for (std::string::iterator it = str.begin(); it != str.end(); it++) {
        if (*it == c) {
            ret.push_back(stock);
            stock = "";
        } else {
            stock+=(*it);
        }
    }
    ret.push_back(stock);
    return (ret);
}

std::string read_(boost::shared_ptr<tcp::socket> sok) {
       boost::asio::streambuf buf;
       boost::asio::read_until(*sok, buf, "\n" );
       std::string data = boost::asio::buffer_cast<const char*>(buf.data());
       return data;
}

void send_(boost::shared_ptr<tcp::socket> sok, std::string message) {
       const std::string msg = message + "\n";
       boost::asio::write(*sok, boost::asio::buffer(message) );
}

void prepare_call(std::string message, bool *stop)
{
    int port_send;
    int port_recv;
    std::string ip;
    std::string name;
    std::vector<std::string> str = split(message, ' ');

    port_send = std::stoi(str[4]);
    port_recv = std::stoi(str[5]);
    ip = str[3];
    name = str[1];
    std::cout << "***************" << std::endl;
    std::cout << "name       : " << name << std::endl;
    std::cout << "ip         : " << ip << std::endl;
    std::cout << "port_send  : " << port_send << std::endl;
    std::cout << "port_recv  : " << port_recv << std::endl;
    std::cout << "***************" << std::endl;

    call(name, ip, port_send, port_recv, stop);
}



void handle_recv(boost::shared_ptr<tcp::socket> sok, bool *stop, bool *call,
int *accept, bool *stop_call)
{
    std::string message;

    while (!(*stop)) {
        message = read_(sok);
        std::cout << "---\nserver : " << message << "\n---" << std::endl;
        if (message[0] == '1' && message[1] == '3') {
            std::cout << "-------------" << std::endl;
            std::cout << "You receiv a call, send yes to accept" << std::endl;
            std::cout << "Send stop to stop the call or refuse" << std::endl;
            *call = true;
            std::cout << "-------------" << std::endl;
            while (*accept == 0);
            if (*accept == 1) {
                *call = false;
                std::cout << "You accept the call" << std::endl;
                prepare_call(message, stop_call);
                *accept = 0;
            }
            else if (*accept == -1) {
                *accept = 0;
            }
        }
        if (message[0] == '1' && message[1] == '2') {
            std::cout << "-------------" << std::endl;
            std::cout << "Try to call someone, send stop to stop the call" << std::endl;
            std::cout << "-------------" << std::endl;
            *call = false;
            prepare_call(message, stop_call);
        }
    }
}

void signalHandler(int signum)
{
    std::cout << "Signal received" << std::endl;
    stopTemp = true;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cout << "USAGE : ./client <server ip>" << std::endl;
        exit(84);
    }
    signal(SIGTSTP, signalHandler); 
    boost::asio::io_service io_service;
    boost::shared_ptr<tcp::socket> sok = boost::shared_ptr<tcp::socket>(new tcp::socket(io_service));
    (*sok).connect(tcp::endpoint(boost::asio::ip::address::from_string(
    av[1]), 1234));
    bool stop = false;
    std::string message;
    bool call = false;
    int accept = 0;
    bool stop_call = false;

    std::thread tt(handle_recv, sok, &stop, &call, &accept, &stop_call);
    
    while (!stop) {
        message = "";
        getline(std::cin, message);
        message = message + "\n";
        if (message.find("quit") != std::string::npos) {
            send_(sok, "quit end\n");
            stop = true;
        }
        else if (message.find("stop") != std::string::npos && call == true) {
            call = false;
            accept = -1;
            std::cout << "You stop the call" << std::endl;
        }
        else if (message.find("yes") != std::string::npos && call == true) {
            accept = 1;
        } else if (call == true) {
            std::cout << "Please responde to the call" << std::endl;
        } else if(message[0] == 'S') {
            stop_call = true;
        }
        else {
            send_(sok, message);
        }
    }
    tt.join();
}

