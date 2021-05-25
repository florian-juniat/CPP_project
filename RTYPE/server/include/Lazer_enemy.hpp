/*
** EPITECH PROJECT, 2019
** Lazer_enemy.hpp
** File description:
** Lazer_enemy
*/

#ifndef LAZER_ENEMY_HPP_
#define LAZER_ENEMY_HPP_

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

using namespace sf;

class Lazer_enemy
{
public:
	Lazer_enemy(float posx, float posy);
	Sprite getSprite();
    IntRect getRect();
    void moveLeft();
    void stopLeft();
    void setRectUp();
    void setRectDown();
    void setRectMid();
    void update(float elapsedTime);
    Vector2f getPosition();

private:
	Vector2f m_Position;
    Sprite m_Sprite;
    Texture m_Texture;
    IntRect m_Rect;
    bool m_LeftPressed;
    float m_Speed;
};

#endif /* !LAZER_ENEMY_HPP_ */