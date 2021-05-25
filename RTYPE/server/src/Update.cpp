/*
** EPITECH PROJECT, 2019
** Update.cpp
** File description:
** Update
*/

#include "Engine.hpp"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    m_Player.update(dtAsSeconds);
    // int i = 0;

    // while (i < my_enemy.size()) {
    // 	my_enemy[i].update(dtAsSeconds);
    // 	i += 1;
    // }
    // int y = 0;
    for (int i = 0; i < my_enemy.size(); i++) {
        my_enemy[i]->update(dtAsSeconds);
        for (int y = 0; y < my_enemy[i]->my_lazer.size(); y++) {
            my_enemy[i]->my_lazer[y]->update(dtAsSeconds);
        }
    }
    for (int i = 0; i < m_Player.my_lazer.size(); i++) {
        m_Player.my_lazer[i]->update(dtAsSeconds);
    }

    for (Obstacle *ob : my_obstacle)
        ob->update(dtAsSeconds);


    // while (y < m_Player.my_lazer.size()) {
    // 	m_Player.my_lazer[y].update(dtAsSeconds);
    // 	y += 1;
    // }
    // i = 0;

    // while (i < my_enemy.size()) {
    //     y = 0;
    // 	while (y < my_enemy[i].my_lazer.size()) {
    // 	    my_enemy[i].my_lazer[y].update(dtAsSeconds);
    // 	    y += 1;
    //     }
    // 	i += 1;
    // }
}
