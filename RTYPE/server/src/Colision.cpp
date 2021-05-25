/*
** EPITECH PROJECT, 2019
** Colision.cpp
** File description:
** Colision
*/

#include "Engine.hpp"

void Engine::chechShootEnemy()
{
    for (int i = 0; i < m_Player.my_lazer.size(); i++) {
        for (int y = 0; y < my_enemy.size(); y++) {
            //printf("%f %f\n", m_Player.my_lazer[i]->getPosition().x, my_enemy[y]->getPosition().x);
            if (m_Player.my_lazer[i]->getPosition().x >= my_enemy[y]->getPosition().x && m_Player.my_lazer[i]->getPosition().x <= my_enemy[y]->getPosition().x + 40
            && m_Player.my_lazer[i]->getPosition().y >= my_enemy[y]->getPosition().y && m_Player.my_lazer[i]->getPosition().y <= my_enemy[y]->getPosition().y + 40) {
                printf("Enemy %i Dead\n", y + 1);
                my_enemy.erase(my_enemy.begin() + y);
            }
        }
    }
}

void Engine::chechShootPlayer()
{
    for (int i = 0; i < my_enemy.size(); i++) {
        for (int y = 0; y < my_enemy[i]->my_lazer.size(); y++) {
            if (my_enemy[i]->my_lazer[y]->getPosition().x >= m_Player.getPosition().x && my_enemy[i]->my_lazer[y]->getPosition().x <= m_Player.getPosition().x + 40
            && my_enemy[i]->my_lazer[y]->getPosition().y >= m_Player.getPosition().y && my_enemy[i]->my_lazer[y]->getPosition().y <= m_Player.getPosition().y + 40) {
                printf("Player Dead\n");
                m_Window.close();
            }
        }
    }
}

