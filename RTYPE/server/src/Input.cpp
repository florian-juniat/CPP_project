/*
** EPITECH PROJECT, 2019
** Include.cpp
** File description:
** Include
*/

#include "Engine.hpp"

float Engine::getPosx()
{
    return m_Player.m_Position.x;
}

void Engine::input()
{
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        m_Window.close();
    }

    if (Keyboard::isKeyPressed(Keyboard::Q))
    {
        m_Player.moveLeft();
    }
    else
    {
        m_Player.stopLeft();
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        m_Player.moveRight();
    }
    else
    {
        m_Player.stopRight();
    }

    if (Keyboard::isKeyPressed(Keyboard::Z))
    {
        if (m_Player.getRect().left < 123) {
            m_Player.setRectUp();
        }
        m_Player.moveUp();
    }
    else
    {
        m_Player.setRectMid();
        m_Player.stopUp();
    }

    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        if (m_Player.getRect().left > 0) {
            m_Player.setRectDown();
        }
        m_Player.moveDown();
    }
    else
    {
        m_Player.stopDown();
    }

    if (Keyboard::isKeyPressed(Keyboard::Space) && player_rate == 0)
    {
        m_Player.SpaceP();
        player_rate = 10;
    }
    else
    {
        m_Player.SpaceNotP();
    }
}
