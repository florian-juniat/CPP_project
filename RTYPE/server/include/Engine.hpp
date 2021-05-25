/*
** EPITECH PROJECT, 2019
** Engine.hpp
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Obstacle.hpp"

using namespace sf;

class Engine {
	public:
		Engine();
		void start();
        void create_enemy();
        void create_obstacle();
        float getPosx();
        void chechShootEnemy();
        void chechShootPlayer();

        RenderWindow m_Window;
        Sprite m_BackgroundSprite;
        Texture m_BackgroundTexture;
        std::vector<Enemy *> my_enemy;
        std::vector<Obstacle *> my_obstacle;
        Player m_Player;
        int player_rate = 0;
        void input();
        void update(float dtAsSeconds);
        void draw();
};

#endif /* !ENGINE_HPP_ */
