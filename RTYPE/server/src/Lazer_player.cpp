/*
** EPITECH PROJECT, 2019
** Lazer_player.cpp
** File description:
** Lazer_player
*/

#include "Engine.hpp"

Lazer_player::Lazer_player(float posx, float posy)
{
    m_Speed = 700;
    m_Position.x = posx + 30;
    m_Position.y = posy + 10;
}

IntRect Lazer_player::getRect()
{
    return m_Rect;
}

Vector2f Lazer_player::getPosition()
{
    return m_Position;
}

void Lazer_player::setRectUp()
{
    m_Rect = sf::IntRect(m_Rect.left += 33, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

void Lazer_player::setRectMid()
{
    m_Rect = sf::IntRect(66, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

void Lazer_player::setRectDown()
{
    m_Rect = sf::IntRect(m_Rect.left -= 33, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

Sprite Lazer_player::getSprite()
{
    return m_Sprite;
}

void Lazer_player::moveRight()
{
    m_RightPressed = true;
}


void Lazer_player::stopRight()
{
    m_RightPressed = false;
}

void Lazer_player::update(float elapsedTime)
{
    m_Position.x += m_Speed * elapsedTime;
    m_Sprite.setPosition(m_Position);

}
