#pragma once
#include "Actors.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "Bullet.h"

namespace KStudio
{
	class Player : public Actors

	{
	public:
		Player(GameDataRef data);
		void Init(b2World* world) override;
		void Update(b2Body* body, float dt, float actorhealth) override;
		void keyInput(sf::Event event) override;
		void keyRealease(sf::Event event) override;
		void Draw() override;
		sf::Vector2f getPosition() override;
		b2Body* &getBody()override;
		b2Fixture* &getFixture()override;
		sf::Sprite &getSprite() override;
		void reset_actor(b2Body* body, float angle)override;
		

	private:
		float desirevelocityX;
		float desirevelocityY;
		float velocityChangeX;
		float velocityChangeY;
		float m_speed;
		float impulseX;
		float impulseY;
		int direction;
		b2Vec2 momentum;
		float pRotate;
		float acceleration;
		GameDataRef _data;
		int respawn_time;
		float health;

		sf::Sprite p_sprite_;
		b2Body* _p_body_;;
		b2Fixture* fixture;
	};
}