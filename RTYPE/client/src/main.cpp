/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** main
*/

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include <fstream>

#include "handle.hpp"
#include "data.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System.hpp>


using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;
using boost::asio::ip::udp;



Data transform_data(std::string data)
{
    Data ret;
    std::vector<std::string> str = split(data, '\n');

    for (std::string str2 : str) {
        if (str2.length() != 0) {
            std::vector<std::string> convert = split(str2, ' ');
            if (convert.size() >= 3)
                ret.addCoo(atoi(convert[1].c_str()), atoi(convert[2].c_str()), convert[0]);
        }
    }
    return (ret);
}


void management_window(int *port, char *ip, bool *stop, Data *dataa)
{
    while ((*port) == -1);
    if (port == 0)
        return;
    sf::Texture enemy;
    sf::Sprite sprite_enemy;

    sf::Texture texture_vaisseau;
    sf::Sprite sprite_vaisseau;

    sf::Texture back;
    sf::Sprite sprite_back;
    sf::Texture back2;
    sf::Sprite sprite_back2;

    sf::Texture m_Texture;
    sf::Sprite m_Sprite;
    sf::Texture m_Texture2;
    sf::Sprite m_Sprite2;

    sf::Texture obs;
    sf::Sprite sprite_obs;

    if (!obs.loadFromFile("./img/r-typesheet30a.png")) {
        printf("Texture not Loaded\n");
    }
    sprite_obs.setTexture(obs);
    sprite_obs.setTextureRect(sf::IntRect(0, 0, 35, 35));
    sprite_obs.setScale(2, 2);
    
    m_Texture.loadFromFile("./img/r-typesheet1.gif");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setTextureRect(sf::IntRect(230, 25, 33, 17));

    m_Texture2.loadFromFile("./img/r-typesheet14.gif");
    m_Sprite2.setTexture(m_Texture2);
    m_Sprite2.setTextureRect(sf::IntRect(232, 138, 16, 15));




    if (!enemy.loadFromFile("img/enemy.png"))
        std::cout << "error load image" << std::endl;
    if (!texture_vaisseau.loadFromFile("img/SpaceShip.png"))
        std::cout << "error load image" << std::endl;
    if (!back.loadFromFile("img/space.png"))
        std::cout << "error load image" << std::endl;
    if (!back2.loadFromFile("img/space2.png"))
        std::cout << "error load image" << std::endl;
    

    sprite_vaisseau.setTextureRect(sf::IntRect(66, 0, 33, 17));
    sprite_vaisseau.setScale(2, 2);



    sprite_enemy.setTexture(enemy);

    sprite_back2.setTexture(back2);
    sprite_vaisseau.setTexture(texture_vaisseau);
    sprite_back.setTexture(back);

    int x_back = 0;
    int x_back2 = 1500;
    int ralentissement = 1;


    boost::asio::io_service io_service;
    udp::endpoint end(boost::asio::ip::address::from_string(ip), *port);
    udp::socket socket(io_service);
    socket.open(udp::v4());

    sf::RenderWindow window(sf::VideoMode(1000, 600), "RTYPE");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                socket.send_to(boost::asio::buffer("quit", 4), end);
                window.close();
                *stop = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                socket.send_to(boost::asio::buffer("left", 4), end);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                socket.send_to(boost::asio::buffer("right", 5), end);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                socket.send_to(boost::asio::buffer("up", 2), end);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                socket.send_to(boost::asio::buffer("down", 4), end);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                socket.send_to(boost::asio::buffer("space", 5), end);
            }
        }
        window.clear();
        sprite_back.setPosition(x_back, 0);
        window.draw(sprite_back);
        sprite_back2.setPosition(x_back2, 0);
        window.draw(sprite_back2);
        if (x_back <= -1500)
            x_back = 1500;
        if (x_back2 <= -1500)
            x_back2 = 1500;
        if (ralentissement % 5 == 0) {
            x_back = x_back - 1;
            x_back2 = x_back2 - 1;
            ralentissement = 1;
        }
        ralentissement += 1;
        for (Coo *coo : dataa->data) {
            if (coo->type == "ob") {
                sprite_obs.setPosition(coo->x, coo->y);
                window.draw(sprite_obs);
            }
            if (coo->type == "v") {
                sprite_enemy.setPosition(coo->x, coo->y);
                window.draw(sprite_enemy);
            }
            if (coo->type == "ma") {
                m_Sprite.setPosition(coo->x, coo->y);
                window.draw(m_Sprite);
            }
            if (coo->type == "me") {
                m_Sprite2.setPosition(coo->x, coo->y);
                window.draw(m_Sprite2);
            }
            if (coo->type[0] == 'p') {
                int n = (int)(coo->type[1]) - 48;
                sprite_vaisseau.setTextureRect(sf::IntRect(66, 17 * n, 33, 17));
                sprite_vaisseau.setPosition(coo->x, coo->y);
                window.draw(sprite_vaisseau);
            }
        }
        window.display();
    }
}

void management_reception(int *port, char *ip, bool *stop, Data *dataa)
{
    while ((*port) == -1);
    if (port == 0)
        return;
    boost::asio::io_service io_service;
    udp::endpoint end(boost::asio::ip::address::from_string("0.0.0.0"), *port);
    udp::socket socket(io_service, end);

    while (!(*stop)) {
        char *aa = (char *) calloc(1000, 1000);
        udp::endpoint remote_endpoint;
        boost::system::error_code error;
        socket.receive_from(boost::asio::buffer(aa, 100000), remote_endpoint, 0, error);
        Data data_recv = transform_data(aa);
        int count = 0;
        (*dataa) = data_recv;
        free(aa);
    }
}




void recv_file(int port_recv, int port_send, std::string ip)
{

    std::cout << "Wait to recv file" << std::endl;

    std::string stop_all = "";
    std::vector<std::string> photos;

    photos.push_back("img/r-typesheet30a.png");
    photos.push_back("img/enemy.png");
    photos.push_back("img/r-typesheet14.gif");
    photos.push_back("img/r-typesheet1.gif");
    photos.push_back("img/space2.png");
    photos.push_back("img/space.png");
    photos.push_back("img/SpaceShip.png");

    boost::asio::io_service io_service;

    udp::endpoint end(boost::asio::ip::address::from_string("0.0.0.0"), port_recv);
    udp::endpoint end2(boost::asio::ip::address::from_string(ip), port_send);
    udp::socket socket(io_service);
    socket.open(udp::v4());
    socket.bind(end);
            

    int count = 0;

    while (stop_all != "stop") {
        std::string str = "";
        std::ofstream fout(photos[count]);


        bool stop = false;

        while (!stop) {
            char *recvv = (char *)calloc(1000, 10000);
            if (count == 0)
                socket.send_to(boost::asio::buffer("yes", 3), end2);
            socket.receive_from(boost::asio::buffer(recvv, 100000), end);
            std::string test = "";
            std::string test2 = recvv;
            stop_all = recvv;
            for (int i = 0; i < 10000; i++)
                test += recvv[i];
            socket.send_to(boost::asio::buffer("yes", 3), end2);
            if (test2 == "next" || test2 == "stop")
                stop = true;
            else {
                str += test;
            }
            free(recvv);
        }
        for (char c : str)
            fout.write((char *)&c, sizeof(c));
        fout.close();
        std::cout << "recv : " << photos[count] << std::endl;
        count++;
    }
    std::cout << "End recv file" << std::endl;
}







int main(int ac, char **av)
{
    Data data;
    bool stop_thread = false;
    bool stop = false;
    int port_recv = -1;
    int port_send = -1;
    if (ac < 3) {
        std::cout << "USAGE : ./client ip port" << std::endl;
        exit(84);
    }
    boost::asio::io_service io_service;
    int port = atoi(av[2]);
    udp::endpoint end(boost::asio::ip::address::from_string(av[1]), port);
    udp::socket socket(io_service);
    socket.open(udp::v4());
    std::string message;

    std::thread manage_window(management_window, &port_send, av[1], &stop_thread, &data);
    std::thread manage_recep(management_reception, &port_recv, av[1], &stop_thread, &data);


    while (!stop) {
        message = "";
        getline(std::cin, message);
        message = message + "\n";
        try {
            socket.send_to(boost::asio::buffer(message.c_str(), message.length()), end);
            char *aa = (char *) calloc(10, 10);
            socket.receive_from(boost::asio::buffer(aa, 100), end);
            std::cout << "I recv : " << std::endl;
            std::cout << aa << std::endl;

            std::vector<std::string> str = split(aa, ' ');
            if (str[0] == "100") {
                recv_file(atoi(str[2].c_str()), atoi(str[1].c_str()), av[1]);
            }
            if (str[0] == "202" || str[0] == "201") {
                port_send = atoi(str[1].c_str());
                port_recv = atoi(str[2].c_str());
                stop_thread = false;
            }
            free(aa);

        } catch(std::exception& e) {
        }
    }

    manage_window.join();
    manage_recep.join();
}

