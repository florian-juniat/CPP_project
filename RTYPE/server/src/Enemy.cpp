/*
** EPITECH PROJECT, 2019
** Enemy.cpp
** File description:
** Enemy
*/

#include "../include/Enemy.hpp"

Enemy::Enemy()
{
    m_Speed = 150;
    m_Position.x = 2000;
    m_Position.y = std::rand()%(600 + 1);
    // std::srand(std::time(nullptr));
    // m_Position.x = VideoMode::getDesktopMode().width;
    // m_Position.y = std::rand()%(VideoMode::getDesktopMode().height - 300 + 1) + 300;
    // std::rand()%(800-100 + 1) + 100
}

Vector2f Enemy::getPosition()
{
    return m_Position;
}

void Enemy::shoot() {
    my_lazer.push_back(new Lazer_enemy(m_Position.x, m_Position.y));
}

IntRect Enemy::getRect()
{
    return m_Rect;
}

void Enemy::setRectUp()
{
    m_Rect = sf::IntRect(m_Rect.left += 33, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

void Enemy::setRectMid()
{
    m_Rect = sf::IntRect(66, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

void Enemy::setRectDown()
{
    m_Rect = sf::IntRect(m_Rect.left -= 33, 0, 33, 17);
    m_Sprite.setTextureRect(m_Rect);
}

Sprite Enemy::getSprite()
{
    return m_Sprite;
}

void Enemy::moveLeft()
{
    m_LeftPressed = true;
}

void Enemy::moveRight()
{
    m_RightPressed = true;
}

void Enemy::moveUp()
{
    m_UpPressed = true;
}

void Enemy::moveDown()
{
    m_DownPressed = true;
}

void Enemy::stopLeft()
{
    m_LeftPressed = false;
}

void Enemy::stopRight()
{
    m_RightPressed = false;
}

void Enemy::stopUp()
{
    m_UpPressed = false;
}

void Enemy::stopDown()
{
    m_DownPressed = false;
}

void Enemy::SpaceP()
{
    m_SpacePressed = true;
}

void Enemy::SpaceNotP()
{
    m_SpacePressed = false;
}

void Enemy::update(float elapsedTime)
{
    // m_Position.x -= m_Speed * elapsedTime;
    if (m_SpacePressed)
    {
        //Lazer_enemy laz(m_Position.x, m_Position.y);
        int rand = std::rand()%(50);
        if (rand == 0)
            my_lazer.push_back(new Lazer_enemy(m_Position.x, m_Position.y));
    }
    m_Position.x -= m_Speed * elapsedTime;
    m_Sprite.setPosition(m_Position);
}
