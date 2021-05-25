/*
** EPITECH PROJECT, 2019
** Enemy.hpp
** File description:
** Enemy
*/

#ifndef Enemy_HPP_
#define Enemy_HPP_

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Lazer_enemy.hpp"

using namespace sf;

class Enemy {
	public:
		Enemy();
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
        void SpaceNotP();
        void SpaceP();
        Vector2f m_Position;
        Vector2f getPosition();
        std::vector<Lazer_enemy *> my_lazer;

	protected:
	private:
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

#endif /* !Enemy_HPP_ */
