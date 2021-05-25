/*
** EPITECH PROJECT, 2019
** Draw.cpp
** File description:
** Draw
*/

#include "Engine.hpp"

void Engine::draw()
{
    m_Window.clear(Color::Black);
    m_Window.draw(m_BackgroundSprite);
    m_Window.draw(m_Player.getSprite());

    int i = 0;
    int y = 0;

    // while (i < my_enemy.size()) {
    // 	m_Window.draw(my_enemy[i].getSprite());
    //     // while (y < my_enemy[i].my_lazer.size()) {
    // 	//     m_Window.draw(my_enemy[i].my_lazer[y].getSprite());
    // 	//     y += 1;
    //     // }
    // 	i += 1;
    // }
    for (int i = 0; i < m_Player.my_lazer.size(); i++) {
        m_Window.draw(m_Player.my_lazer[i]->getSprite());
    }
    for (int i = 0; i < my_enemy.size(); i++) {
        m_Window.draw(my_enemy[i]->getSprite());
        for (int y = 0; y < my_enemy[i]->my_lazer.size(); y++) {
            m_Window.draw(my_enemy[i]->my_lazer[y]->getSprite());
        }
    }
    // i = 0;
    // while (i < my_enemy.size()) {
    //     y = 0;
    // 	while (y < my_enemy[i].my_lazer.size()) {
    // 	    m_Window.draw(my_enemy[i].my_lazer[y].getSprite());
    // 	    y += 1;
    //     }
    // 	i += 1;
    // }

    m_Window.display();
}
