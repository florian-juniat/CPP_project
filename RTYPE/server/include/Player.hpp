/*
** EPITECH PROJECT, 2019
** Player.hpp
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Lazer_player.hpp"

using namespace sf;

class Player {
	public:
		Player();
        Sprite getSprite();
        IntRect getRect();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void stopLeft();
        void stopRight();
        void stopUp();
        void stopDown();
        void setRectUp();
        void setRectDown();
        void setRectMid();
        void update(float elapsedTime);
        void shoot();
        float getPosx();
        float getPosy();
        void SpaceNotP();
        void SpaceP();
        std::vector<Lazer_player *> my_lazer;
        Vector2f m_Position;
        Vector2f getPosition();

	protected:
        Sprite m_Sprite;
        Texture m_Texture;
        IntRect m_Rect;
        bool m_SpacePressed;
        bool m_LeftPressed;
        bool m_RightPressed;
        bool m_UpPressed;
        bool m_DownPressed;
        float m_Speed;
};

#endif /* !PLAYER_HPP_ */
