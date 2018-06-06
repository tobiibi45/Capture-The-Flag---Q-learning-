#pragma once

#include "Box2D\Box2D.h"
#include "SFML/Graphics.hpp"
#include "Game.hpp"


namespace KStudio
{
	class Bullet
	{
	public:
		Bullet(GameDataRef data);
		~Bullet();
		void Init(b2World *world, float posX, float posY, float angle, b2Body* pBody);
		void Init(b2World *world, float posX, float posY, b2Body* body, sf::Vector2f targetPos, float angle);
		void Update(b2Body* body, float dt);
		void Draw();

		float angle_to_target(sf::Vector2f SpritePos, sf::Vector2f targetPos);

	private:
		GameDataRef _data;
		sf::Sprite bullet_sprite_;
		b2Body* bullet_body_;
		float m_speed;




	};
}
