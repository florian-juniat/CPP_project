/*
** EPITECH PROJECT, 2019
** Obstacle.hpp
** File description:
** Obstacle
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

using namespace sf;

class Obstacle {
	public:
		Obstacle();
        void moveLeft();
        void stopLeft();
        void update(float elapsedTime);
        int getLife();
        void setLife(int m_Life);
        Vector2f m_Position;
        Vector2f getPosition();

	protected:
	private:
        bool m_LeftPressed;
        float m_Speed;
        int m_Life;
};

#endif /* !OBJECT_HPP_ */
