#pragma once
#include "Player.h"
#include "ENGINEDEFINITIONS.hpp"
#include <iostream>


KStudio::Player::Player(GameDataRef data) : _data(data)
{

}

void KStudio::Player::Init(b2World* world)
{
	
	m_speed = 2.f;
	pRotate = 0.f;
	acceleration = 0.1f;
	actor_spawn = b2Vec2(-50.f / SCALE, 500.f / SCALE);
	respawn.restart();
	respawn_time = 2;
	health = 0.f;
	
	p_sprite_.setTexture(this->_data->assets.GetTexture("PTexture"));
	healthbar.setTexture(this->_data->assets.GetTexture("healthbar"));
	healthbar_backg.setTexture(this->_data->assets.GetTexture("healthbar_backg"));
	

	//!set structure contents as necessary
	bodyUserData* myStruct = new bodyUserData;
	myStruct->type = 1;

	//!Set the Bodydef as necessary
	b2BodyDef BodyDef;
	BodyDef.position = actor_spawn;
	BodyDef.type = b2_dynamicBody;
	_p_body_ = world->CreateBody(&BodyDef);
	_p_body_->SetUserData(myStruct);

	b2PolygonShape Shape;
	Shape.SetAsBox((((p_sprite_.getGlobalBounds().width / 2) / 2) / SCALE)  * 0.4f, ((p_sprite_.getGlobalBounds().height / 2) / 2) / SCALE);

	//!Set the Fixturedef
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.5f;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = BIT_PLAYER;
	FixtureDef.filter.maskBits = BIT_WALLS | BIT_ENEMY_BULLET | BIT_BORDER | BIT_RED_FLAG | BIT_BLUE_FLAG | BIT_RED_PED | BIT_ENEMY_RADER | BIT_PLAYER_BASE_AREA;
	_p_body_->CreateFixture(&FixtureDef);

	_p_body_->SetFixedRotation(true);

	//!Set the Fixture data as necessary
	fixture = _p_body_->CreateFixture(&FixtureDef);
	fixture->SetUserData((void*)1);

	//!Initialising the movement speed
	direction = 0;

	desirevelocityX = fmax(_p_body_->GetLinearVelocity().x - acceleration,
		fmin(direction * m_speed, _p_body_->GetLinearVelocity().x + acceleration));

	desirevelocityY = fmax(_p_body_->GetLinearVelocity().y - acceleration,
		fmin(direction * m_speed, _p_body_->GetLinearVelocity().y + acceleration));
}

void KStudio::Player::Update(b2Body* body, float dt, float actorhealth)
{
	const float mouse_angle = rotationAngle(p_sprite_.getPosition(), _data->input.GetMousePosition(this->_data->window)) * (b2_pi / 180);
	healthbar.setOrigin(p_sprite_.getOrigin().x, 50.f);
	healthbar.setPosition(p_sprite_.getPosition().x, p_sprite_.getPosition().y);
	healthbar.setRotation(p_sprite_.getRotation());
	healthbar_backg.setPosition(healthbar.getPosition().x, healthbar.getPosition().y);
	healthbar_backg.setOrigin(healthbar.getOrigin());
	healthbar_backg.setRotation(healthbar.getRotation());
	healthbar.setScale(1, actorhealth / actors_max_health);

	p_sprite_.setScale(0.5f, 0.5f);
	p_sprite_.setOrigin(30.f, 60.f);
	p_sprite_.setPosition((body->GetPosition().x) * SCALE + 390.f, body->GetPosition().y * SCALE + 15.f);
	p_sprite_.setRotation(body->GetAngle() * (180 / b2_pi));
	if (actorhealth > 0.f)
	{
		body->SetTransform(body->GetPosition(), mouse_angle);
	}


	momentum = body->GetLinearVelocity();
	// fOR VERTICAL MOVEMENT
	velocityChangeX = desirevelocityX - momentum.x;
	impulseX = body->GetMass() * velocityChangeX;

	// fOR HORIZONTAL MOVEMENT
	velocityChangeY = desirevelocityY - momentum.y;
	impulseY = body->GetMass() * velocityChangeY;

	body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), body->GetWorldCenter(), true);

	if (actorhealth <= 0.f)
	{
		if (respawn.getElapsedTime().asSeconds() > RESPAWN_DELAY)
		{
			reset_actor(body, mouse_angle);
		}
	}

	health = actorhealth;
}

void KStudio::Player::Draw()
{
	this->_data->window.draw(p_sprite_);
	this->_data->window.draw(healthbar);
	this->_data->window.draw(healthbar_backg);
}

void KStudio::Player::keyInput(sf::Event event)
{
	if (health > 0.f)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			/** If D is pressed */
			if (event.key.code == sf::Keyboard::D)
			{
				direction = 1;
				desirevelocityX = direction * (m_speed * 5.f);
				desirevelocityX;
			}

			/** If A is pressed */
			if (event.key.code == sf::Keyboard::A)
			{
				direction = -1;
				desirevelocityX = direction * (m_speed * 5.f);
				desirevelocityX;
			}
			/** If S is pressed */
			if (event.key.code == sf::Keyboard::S)
			{
				direction = 1;
				desirevelocityY = direction * (m_speed * 5.f);
				desirevelocityY;
			}

			/** If W is pressed */
			if (event.key.code == sf::Keyboard::W)
			{
				direction = -1;
				desirevelocityY = direction * (m_speed * 5.f);
				desirevelocityY;
			}
		}
	}
}

void KStudio::Player::keyRealease(sf::Event event)
{
	if (health > 0.f)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			/** If D is pressed */
			if (event.key.code == sf::Keyboard::D)
			{
				direction = 1;
				desirevelocityX = 0;
				desirevelocityX;
			}
			/** If A is pressed */
			if (event.key.code == sf::Keyboard::A)
			{
				direction = -1;
				desirevelocityX = 0;
				desirevelocityX;
			}
			/** If S is pressed */
			if (event.key.code == sf::Keyboard::S)
			{
				direction = 1;
				desirevelocityY = 0;
				desirevelocityY;
			}

			/** If W is pressed */
			if (event.key.code == sf::Keyboard::W)
			{
				direction = -1;
				desirevelocityY = 0;
				desirevelocityY;
			}
		}
	}
}

sf::Vector2f KStudio::Player::getPosition()
{
	auto x = p_sprite_.getPosition().x;
	auto y = p_sprite_.getPosition().y;
	const sf::Vector2f position(x, y);
	return position;
}

b2Body* &KStudio::Player::getBody()
{
	b2Body* &body = _p_body_;
	return body;
}

b2Fixture*& KStudio::Player::getFixture()
{
	b2Fixture* &fixture = this->fixture;
	return fixture;
}

sf::Sprite &KStudio::Player::getSprite()
{
	return p_sprite_;
}

void KStudio::Player::reset_actor(b2Body* body, float angle)
{
	body->SetTransform(actor_spawn, angle);
}
