#include "Obstacle.hpp"

Obstacle::Obstacle()
{
    m_Speed = 100;
    m_Position.x = 2000;
    m_Position.y = std::rand()%(600 + 1);

}

Vector2f Obstacle::getPosition()
{
    return m_Position;
}

void Obstacle::moveLeft()
{
    m_LeftPressed = true;
}

void Obstacle::stopLeft()
{
    m_LeftPressed = false;
}

int Obstacle::getLife()
{
    return m_Life;
}

void Obstacle::setLife(int Life)
{
    m_Life = Life;
}

void Obstacle::update(float elapsedTime)
{
    m_Position.x -= m_Speed * elapsedTime;
}
