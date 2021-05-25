    #include "mainwindow.h"
#include <QApplication>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <QDebug>

#include <string>
#include <thread>
#include <vector>

#include <QLabel>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;
using boost::asio::ip::udp;


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


void handleButton()
{
    std::terminate();
}

int talk(std::string name)
{
    QWidget *window = new QWidget;

    window->setFixedSize(200, 100);

    QPushButton *button1 = new QPushButton("CALL");


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(button1);

    window->setLayout(layout);
    window->show();

}



void handle_read(boost::shared_ptr<tcp::socket> sok, std::string *recv, bool *start)
{

    while (!(*start));



    while (start) {
        std::cout << "Wait to recv a message" << std::endl;
        *recv = read_(sok);
        std::cout << "--------------" << std::endl;
        std::cout << *recv << std::endl;
        std::cout << "-------------" << std::endl;
        std::vector<std::string> str = split(*recv, ' ');
        if ((*recv)[0] == '1' && (*recv)[1] == '3') {
            *recv = "";
            for (int i = 0; i < 300; i ++)
                std::cout << "-------\nrecv call from : " << str[1] << "\n" << str[2] << "----" << std::endl;
            std::string ip = str[2];
                talk(str[1]);
        }

        else if ((*recv)[0] == '1' && (*recv)[1] == '2') {
            *recv = "";
            for (int i = 0; i < 300; i ++)
                std::cout << "-------\nTry to call : " << str[1] << "\n----" << std::endl;
            talk(str[1]);
        }
    }
    *start = true;
}




int main(int argc, char *argv[])
{
    boost::asio::io_service io_service;
    boost::shared_ptr<tcp::socket> sok = boost::shared_ptr<tcp::socket>(new tcp::socket(io_service));
    (*sok).connect(tcp::endpoint(boost::asio::ip::address::from_string(
    "127.0.0.1"), 1234));


    std::cout << "I launch the good project" << std::endl;

    bool start = false;
    std::string recv = "";


    std::thread rec(handle_read, sok, &recv, &start);

    QApplication a(argc, argv);

    MainWindow w(0, sok, &recv, &start);
    w.show();

    return a.exec();
}
