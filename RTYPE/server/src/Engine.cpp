/*
** EPITECH PROJECT, 2019
** Engine.cpp
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine()
{
}

void Engine::create_enemy() {
    my_enemy.push_back(new Enemy());
}

void Engine::create_obstacle()
{
    my_obstacle.push_back(new Obstacle());
}

void Engine::start()
{
    int test = 1;
    Clock clock;
    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();
        if (test > 1000)
            test = 0;
        if (player_rate > 0) {
            player_rate -= 1;
        }

        if (test % 200 == 0) {
            create_enemy();
        }
        if (test % 50 == 0) {
            for (int i = 0; i < my_enemy.size(); i++) {
                my_enemy[i]->SpaceP();
            }
        } else {
            for (int i = 0; i < my_enemy.size(); i++) {
                my_enemy[i]->SpaceNotP();
            }
        }
        int i = 0;
        while (i < my_enemy.size()) {
            if (my_enemy[i]->getPosition().x < -100) {
                my_enemy.erase(my_enemy.begin() + i);
            } else {
    	        i += 1;
            }
        }
        input();
        chechShootEnemy();
        chechShootPlayer();
        update(dtAsSeconds);
        draw();
        test += 1;
    }
    // int i = 0;
    // while (i < my_enemy.size()) {
    //     my_enemy[i].~Enemy();
    // }
}
