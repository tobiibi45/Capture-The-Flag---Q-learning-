#include "Bullet.h"
#include "ENGINEDEFINITIONS.hpp"
#include <iostream>
#include <utility>
#include "Contact.h"

KStudio::Bullet::Bullet(GameDataRef data) : _data(std::move(data))
{
	
}

KStudio::Bullet::~Bullet()
{

}

void KStudio::Bullet::Init(b2World* world, float posX, float posY, float angle, b2Body* pBody) //Bullet for Player
{

	m_speed = 40.f;
	bullet_sprite_.setTexture(_data->assets.GetTexture("redbullet"));
	bullet_sprite_.setOrigin(bullet_sprite_.getGlobalBounds().width / 2, bullet_sprite_.getGlobalBounds().height / 2);
	

	//!set structure contents as necessary
	bodyUserData* myStruct = new bodyUserData;
	myStruct->type = 15;

	//!Set the Bodydef as necessary
	b2BodyDef BodyDef;
	BodyDef.position.Set(posX, posY);
	BodyDef.angle = pBody->GetAngle();
	BodyDef.type = b2_dynamicBody;
	bullet_body_ = world->CreateBody(&BodyDef);
	bullet_body_->SetUserData(myStruct);
	bullet_body_->SetBullet(true);
	
	b2PolygonShape Shape;
	Shape.SetAsBox(((bullet_sprite_.getGlobalBounds().width / 2) / SCALE), ((bullet_sprite_.getGlobalBounds().height / 2) / SCALE));

	//!Set the Fixturedef
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = BIT_BULLET;
	FixtureDef.filter.maskBits = BIT_WALLS | BIT_BORDER | BIT_ENEMY;
	bullet_body_->CreateFixture(&FixtureDef);

	bullet_body_->SetFixedRotation(true);

	//!Set the Fixture data as necessary
	b2Fixture* fixture = bullet_body_->CreateFixture(&FixtureDef);
	fixture->SetUserData((void*)10);
	
	bullet_body_->SetLinearVelocity(b2Vec2(cos(angle) * (m_speed), sin(angle) * (m_speed)));
}


void KStudio::Bullet::Init(b2World* world, float posX, float posY, b2Body* body, sf::Vector2f targetPos, float angle) //Bullet for Enemy
{

	m_speed = 40.f;
	bullet_sprite_.setTexture(_data->assets.GetTexture("bluebullet"));
	bullet_sprite_.setOrigin(bullet_sprite_.getGlobalBounds().width / 2, bullet_sprite_.getGlobalBounds().height / 2);


	//!set structure contents as necessary
	bodyUserData* myStruct = new bodyUserData;
	myStruct->type = 10;

	//!Set the Bodydef as necessary
	b2BodyDef BodyDef;
	BodyDef.position.Set(posX, posY);
	BodyDef.angle = body->GetAngle();
	BodyDef.type = b2_dynamicBody;
	bullet_body_ = world->CreateBody(&BodyDef);
	bullet_body_->SetUserData(myStruct);
	bullet_body_->SetBullet(true);

	b2PolygonShape Shape;
	Shape.SetAsBox(((bullet_sprite_.getGlobalBounds().width / 2) / SCALE), ((bullet_sprite_.getGlobalBounds().height / 2) / SCALE));

	//!Set the Fixturedef
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = BIT_ENEMY_BULLET;
	FixtureDef.filter.maskBits = BIT_WALLS | BIT_BORDER | BIT_PLAYER;
	bullet_body_->CreateFixture(&FixtureDef);

	bullet_body_->SetFixedRotation(true);

	//!Set the Fixture data as necessary
	b2Fixture* fixture = bullet_body_->CreateFixture(&FixtureDef);
	fixture->SetUserData((void*)9);


	//auto angle = angle_to_target(bullet_sprite_.getPosition(), targetPos) * (b2_pi / 180);
	bullet_body_->SetLinearVelocity(b2Vec2(cos(angle) * (m_speed), sin(angle) * (m_speed)));

}

void KStudio::Bullet::Update(b2Body* body, float dt)
{
	bullet_sprite_.setRotation(body->GetAngle() * (180 / b2_pi) - 180);
	bullet_sprite_.setPosition(body->GetPosition().x * SCALE + 390.f, body->GetPosition().y * SCALE + 15.f);
}


void KStudio::Bullet::Draw()
{
	_data->window.draw(bullet_sprite_);
}

float KStudio::Bullet::angle_to_target(sf::Vector2f SpritePos, sf::Vector2f targetPos)
{
	auto a = SpritePos.x - targetPos.x;
	auto b = SpritePos.y - targetPos.y;
	const auto rotation = ((atan2(b, a)) * 180 / b2_pi);
	return (rotation);
}
