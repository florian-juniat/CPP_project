/*
** EPITECH PROJECT, 2019
** Player.cpp
** File description:
** Player
*/

#include "Player.hpp"

Player::Player()
{
    m_Speed = 400;
    m_Position.x = 500;
    m_Position.y = 800;
}

void Player::shoot() {
    Lazer_player laz(m_Position.x, m_Position.y);

    my_lazer.push_back(new Lazer_player(m_Position.x, m_Position.y));
}

IntRect Player::getRect()
{
    return m_Rect;
}

void Player::setRectUp()
{
    m_Rect = sf::IntRect(m_Rect.left += 33, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

void Player::setRectMid()
{
    m_Rect = sf::IntRect(66, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

void Player::setRectDown()
{
    m_Rect = sf::IntRect(m_Rect.left -= 33, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

Sprite Player::getSprite()
{
    return m_Sprite;
}

Vector2f Player::getPosition()
{
    return m_Position;
}

void Player::moveLeft()
{
    m_LeftPressed = true;
}

void Player::moveRight()
{
    m_RightPressed = true;
}

void Player::moveUp()
{
    m_UpPressed = true;
}

void Player::moveDown()
{
    m_DownPressed = true;
}

void Player::stopLeft()
{
    m_LeftPressed = false;
}

void Player::stopRight()
{
    m_RightPressed = false;
}

void Player::stopUp()
{
    m_UpPressed = false;
}

void Player::stopDown()
{
    m_DownPressed = false;
}

float Player::getPosx()
{
    return m_Position.x;
}

float Player::getPosy()
{
    return m_Position.y;
}

void Player::SpaceP()
{
    m_SpacePressed = true;
}

void Player::SpaceNotP()
{
    m_SpacePressed = false;
}

void Player::update(float elapsedTime)
{
    if (m_RightPressed)
    {
        m_Position.x += m_Speed * elapsedTime;
    }
    if (m_LeftPressed)
    {
        m_Position.x -= m_Speed * elapsedTime;
    }
    if (m_UpPressed)
    {
        m_Position.y -= m_Speed * elapsedTime;
    }
    if (m_DownPressed)
    {
        m_Position.y += m_Speed * elapsedTime;
    }
    if (m_SpacePressed)
    {
        my_lazer.push_back(new Lazer_player(m_Position.x, m_Position.y));
    }
    m_Sprite.setPosition(m_Position);

}
