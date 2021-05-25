/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** main
*/

#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "Engine.hpp"


#include "handle.hpp"
#include "tab_party.hpp"
#include "data.hpp"
#include "send_file.hpp"

using boost::asio::ip::udp;


std::string transform_coo(std::vector<Client *> str, std::vector<Enemy *> enem,
std::vector<Lazer_player *> my_lazer, std::vector<Obstacle *> my_obs)
{
    std::string ret = "";

    int count = 0;
    for (Client * c : str) {
        ret = ret + "p" + std::to_string(count) + " " + std::to_string(c->x) + " " + std::to_string(c->y);
        ret = ret + "\n";
        count++;
    }
    for (Enemy * c : enem) {
        Vector2f vect = c->getPosition();
        ret = ret + "v " + std::to_string((int)vect.x) + " " + std::to_string((int)vect.y);
        ret = ret + "\n";
        for (Lazer_enemy *cc : c->my_lazer) {
            Vector2f vect = cc->getPosition();
            ret = ret + "me " + std::to_string((int)vect.x) + " " + std::to_string((int)vect.y) + "\n";
        }
    }
    for (Lazer_player * c : my_lazer) {
        Vector2f vect = c->getPosition();
        ret = ret + "ma " + std::to_string((int)vect.x) + " " + std::to_string((int)vect.y);
        ret = ret + "\n";
    }
    for (Obstacle * c : my_obs) {
        Vector2f vect = c->getPosition();
        ret = ret + "ob " + std::to_string((int)vect.x) + " " + std::to_string((int)vect.y);
        ret = ret + "\n";
    }
    return (ret);
}


std::string manage_connection(std::vector<std::string> str, TabClient *clients, Client *client, udp::endpoint ud_end)
{
    if (str[0] == "quit") {
        clients->removeClient(client);
        return ("300 quit accepted");
    }
    if (str[0] == "connect") {
        if (str.size() < 2)
            return ("401 can't connect without pseudo");
        client = new Client(ud_end, str[1]);
        clients->addClient(client);
        return ("100");
    }
    return ("");
}


std::string manage_party(std::vector<std::string> str, Client *client, TabParty *tab_party, int port)
{
    if (str[0] == "create") {
        if (str.size() < 3) { 
            return ("402 can't create party without name and number");
        }
        std::stringstream g(str[2]);
        int p = 0;
        g >> p;
        Party *part = new Party(str[1], p, port);
        part->join(client);
        tab_party->addParty(part);
        return ("201 " + part->get_port_party() + " create party accepted");
    }
    if (str[0] == "join") {
        if (str.size() < 2) {
            return ("403 can't join party without a name");
        }
        Party *part = tab_party->getParty(str[1]);
        if (part == NULL) {
            return ("404 can't find your party");
        }
        part->join(client);
        return ("202 " + part->get_port_party() + " you join the party");
    }
    if (str[0] == "leave") {
        tab_party->quit(client);
        return ("203 you leave a party");
    }
    if (str[0] == "display") {
        std::string ret = "204 ";
        ret = ret + tab_party->display();
        return (ret);
    }
    return ("");
}


 


void reception(Party *party)
{
    boost::asio::io_service io_service;
	udp::socket socket(io_service, udp::endpoint(udp::v4(), party->port_recv));
    
    while (party->launch) {
        char *recv_buf = (char *) calloc(10, 10);
        udp::endpoint remote_endpoint;
        boost::system::error_code error;
        socket.receive_from(boost::asio::buffer(recv_buf, 100), remote_endpoint, 0, error); 

        Action act(party->getClient(remote_endpoint.address()), recv_buf);
        if (act.action == "quit") {
            party->quit(act.client);
            std::cout << "A client quit a game : " << party->nb_co << std::endl;
            if ((party->clients).size() == 0)
                party->launch = false;
        } else {
            (party->tab_actions).add(act);
        }
    }
}


void party_game(Party *party)
{
    std::cout << "-----------------" << std::endl;
    std::cout << "Launch a new game" << std::endl;
    std::cout << "port recv : " << party->port_recv << std::endl;
    std::cout << "port send : " << party->port_send << std::endl;
    std::cout << "nb player : " << party->nb_max << std::endl;
    std::cout << "-----------------" << std::endl;
    boost::asio::io_service io_service;
	udp::socket socket(io_service);
    socket.open(udp::v4());

    int count = 0;
    for (Client *c : party->clients) {
        c->y = int(600 / (party->nb_max + 1)) * count;
        count++;
    }

    Engine engine;
    int clock_enemy = 1;
    Clock clock;


    while (party->launch) {

        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        if (clock_enemy > 50000) {
            clock_enemy = 0;
        }
        if (clock_enemy % 10000 == 0)
            engine.create_enemy();
        if (clock_enemy == 2000) {
            engine.create_obstacle();
        }
        if (clock_enemy % 2000 == 0) {
            for (int i = 0; i < engine.my_enemy.size(); i++) {
                engine.my_enemy[i]->SpaceP();
            }
        } else {
            for (int i = 0; i < engine.my_enemy.size(); i++) {
                engine.my_enemy[i]->SpaceNotP();
            }
        }
        int i = 0;
        while (i < engine.my_enemy.size()) {
            if (engine.my_enemy[i]->getPosition().x < -100) {
                engine.my_enemy.erase(engine.my_enemy.begin() + i);
            } else {
    	        i += 1;
            }
        }
        i = 0;
        while (i < engine.m_Player.my_lazer.size()) {
            if (engine.m_Player.my_lazer[i]->getPosition().x > 1100) {
                engine.m_Player.my_lazer.erase(engine.m_Player.my_lazer.begin() + i);
            } else
                i += 1;
        }
        i = 0;
        while (i < engine.my_obstacle.size()) {
            if (engine.my_obstacle[i]->getPosition().x < -100) {
                engine.my_obstacle.erase(engine.my_obstacle.begin() + i);
            } else
                i += 1;
        }


        for (int i = 0; i < 10; i++) {
            Action act = (party->tab_actions).get();
            if (act.client != NULL) {
                if (act.action == "left" && (act.client)->x > 10)
                    (act.client)->x -= 10;
                if (act.action == "right" && (act.client)->x < 990)
                    (act.client)->x += 10;
                if (act.action == "up" && (act.client)->y > 10)
                    (act.client)->y -= 10;
                if (act.action == "down" && (act.client)->y < 590)
                    (act.client)->y += 10;
                if (act.action == "space") {
                    engine.m_Player.my_lazer.push_back(new Lazer_player((act.client)->x, (act.client)->y));
                }
            }
        }

        for (Obstacle *obs : engine.my_obstacle) {
            Vector2f pos = obs->getPosition();
            for (Client *c : party->clients) {
                if (c->x + 50 >= pos.x && c->x <= pos.x + 70 && c->y + 34 >= pos.y && c->y <= pos.y + 70)
                    c->y = -10000;

            }
        }

        for (int m = 0; m < engine.my_enemy.size(); m++) {
            for (int y = 0; y < engine.my_enemy[m]->my_lazer.size(); y++) {
                Vector2f pos = engine.my_enemy[m]->getPosition();
                for (Client *c : party->clients) {
                    if (engine.my_enemy[m]->my_lazer[y]->getPosition().x >= c->x && engine.my_enemy[m]->my_lazer[y]->getPosition().x <= c->x + 40
            && engine.my_enemy[m]->my_lazer[y]->getPosition().y >= c->y && engine.my_enemy[m]->my_lazer[y]->getPosition().y <= c->y + 40) {
                        c->y = -10000;
                    }
                    if (c->x + 50 >= pos.x && c->x <= pos.x + 70 && c->y + 34 >= pos.y && c->y <= pos.y + 70)
                        c->y = -10000;
                }
            }
        }

        engine.chechShootEnemy();
        
        engine.update(dtAsSeconds);

        std::string envoie = transform_coo(party->clients, engine.my_enemy, engine.m_Player.my_lazer, engine.my_obstacle);
        for (Client * c : party->clients) {
            udp::endpoint remote_endpoint = c->end;
            remote_endpoint.port(party->port_send);
            socket.send_to(boost::asio::buffer(envoie, envoie.size()), remote_endpoint);
        }
        clock_enemy++;
    }
}




void send_file(SendFile my_send)
{
    my_send.start();
}







int main(int ac, char **av)
{
    int num_recv = 100;
    boost::asio::io_service io_service;

    if (ac < 2) {
        std::cout << "Enter the port to listen" << std::endl;
        exit(84);
    }
    int port = atoi(av[1]);



    // ressource utile 
    
    TabClient tab_client;
    TabParty tab_party;

    std::vector<std::thread> thread_recv;
    std::vector<std::thread> thread_send;
    std::vector<std::thread> thread_file;
    
    // end ressource utile


    try {
        boost::asio::io_service io_service;
		udp::socket socket(io_service, udp::endpoint(udp::v4(), port));
		while (1)
		{
            char *recv_buf = (char *) calloc(10, 10);
			udp::endpoint remote_endpoint;
			boost::system::error_code error;
			socket.receive_from(boost::asio::buffer(recv_buf, 100), remote_endpoint, 0, error); 

            int k = 0;
            while (k < (tab_party.partys).size()) {
                if ((tab_party.partys[k])->clients.size() == 0)
                    tab_party.removeParty(tab_party.partys[k]);
                else
                    k++;
            }

            std::string data(recv_buf);
            std::cout << "recv command : " << recv_buf << std::endl;
            std::vector<std::string> str_back = split(data, '\n');
            std::vector<std::string> str = split(str_back[0], ' ');

            Client *client = tab_client.getClient(remote_endpoint);
            std::string message = "";

            if (client == NULL && str[0] != "connect") {
                message = "400";
            } else {
                message += manage_connection(str, &tab_client, client, remote_endpoint);
                message += manage_party(str, client, &tab_party, port);
            }

            boost::system::error_code igno;


            if (message == "100") {
                SendFile sendfile(port, remote_endpoint.address().to_string());
                thread_file.push_back(std::thread(send_file, sendfile));
                message = message + " " + sendfile.display();
            }

		    socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, igno);

            // --- check if a party is full and not lunch
            
            for (Party *p : tab_party.partys) {
                if (p->full && p->launch == false) {
                    p->launch = true;
                    thread_recv.push_back(std::thread(reception, p));
                    thread_send.push_back(std::thread(party_game, p));
                }
            }

            free(recv_buf);



		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
    for (int i = 0; i < thread_recv.size(); i++)
        thread_recv[i].join();
    for (int i = 0; i < thread_send.size(); i++)
        thread_send[i].join();
    for (int i = 0; i < thread_file.size(); i++)
        thread_send[i].join();
    return (0);
}
