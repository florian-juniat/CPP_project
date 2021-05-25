/*
** EPITECH PROJECT, 2019
** Lazer_enemy.cpp
** File description:
** Lazer_enemy
*/

#include "Lazer_enemy.hpp"

Lazer_enemy::Lazer_enemy(float posx, float posy)
{
    m_Speed = 500;
    m_Position.x = posx;
    m_Position.y = posy + 20;
}

IntRect Lazer_enemy::getRect()
{
    return m_Rect;
}

Vector2f Lazer_enemy::getPosition()
{
    return m_Position;
}

void Lazer_enemy::setRectUp()
{
    m_Rect = sf::IntRect(m_Rect.left += 33, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

void Lazer_enemy::setRectMid()
{
    m_Rect = sf::IntRect(66, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

void Lazer_enemy::setRectDown()
{
    m_Rect = sf::IntRect(m_Rect.left -= 33, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

Sprite Lazer_enemy::getSprite()
{
    return m_Sprite;
}

void Lazer_enemy::moveLeft()
{
    m_LeftPressed = true;
}

void Lazer_enemy::stopLeft()
{
    m_LeftPressed = false;
}


void Lazer_enemy::update(float elapsedTime)
{
    m_Position.x -= m_Speed * elapsedTime;
    m_Sprite.setPosition(m_Position);

}
