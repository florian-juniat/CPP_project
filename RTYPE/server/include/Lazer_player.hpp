/*
** EPITECH PROJECT, 2019
** Lazer_player.hpp
** File description:
** Lazer_player
*/

#ifndef LAZER_PLAYER_HPP_
#define LAZER_PLAYER_HPP_

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

using namespace sf;

class Lazer_player
{
public:
	Lazer_player(float posx, float posy);
	Sprite getSprite();
    IntRect getRect();
    void moveRight();
    void stopRight();
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
    bool m_RightPressed;
    float m_Speed;
};

#endif /* !LAZER_PLAYER_HPP_ */