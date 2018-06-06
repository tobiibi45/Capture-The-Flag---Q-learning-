#include "Borders.h"
#include "ENGINEDEFINITIONS.hpp"

KStudio::Borders::Borders(GameDataRef data) : _data(data)
{

}

void KStudio::Borders::Init(b2World* world)
{
	bodyUserData* myStruct = new bodyUserData;
	myStruct->type = 2;

	b2BodyDef BodyDef;

	std::vector<b2Vec2> borders;
	borders.emplace_back(565.f / SCALE, 1010.f / SCALE);
	borders.emplace_back(565.f / SCALE, 40.f / SCALE);

	//////////////Horizontal Boerder///////////////////
	for (auto i = 0; i < borders.size(); i++)
	{
		BodyDef.position = b2Vec2(borders[i]);
		BodyDef.type = b2_staticBody;
		border_hori = world->CreateBody(&BodyDef);
		border_hori->SetUserData(myStruct);

		b2PolygonShape Shape;

		std::vector<sf::Vector2f> bSize;

		bSize.emplace_back(1580.f, 5.f);
		bSize.emplace_back(1580.f, 5.f);

		for (auto & k : bSize)
		{
			Shape.SetAsBox((k.x / 2.f) / SCALE, (k.y / 2.f) / SCALE);
		}

		b2FixtureDef FixtureDef;
		FixtureDef.density = 0.f;
		FixtureDef.shape = &Shape;
		FixtureDef.filter.categoryBits = BIT_BORDER;
		FixtureDef.filter.maskBits = BIT_PLAYER | BIT_BULLET | BIT_ENEMY | BIT_WALLS | BIT_ENEMY_BULLET;
		border_hori->CreateFixture(&FixtureDef);

		b2Fixture* fixture = border_hori->CreateFixture(&FixtureDef);
		fixture->SetUserData((void*)2);
	}


	//////////////Vertical Border///////////////////
	std::vector<b2Vec2> borders1;
	borders1.emplace_back(-220.f / SCALE, 520.f / SCALE);
	borders1.emplace_back(1360.f / SCALE, 520.f / SCALE);
	for (auto i = 0; i < borders.size(); i++)
	{
		BodyDef.position = b2Vec2(borders1[i]);
		BodyDef.type = b2_staticBody;
		border_vert = world->CreateBody(&BodyDef);
		border_vert->SetUserData(myStruct);

		b2PolygonShape Shape;

		std::vector<sf::Vector2f> bSize;
		bSize.emplace_back(5.f, 970.f);
		bSize.emplace_back(5.f, 970.f);

		for (auto & k : bSize)
		{
			Shape.SetAsBox((k.x / 2.f) / SCALE, (k.y / 2.f) / SCALE);
		}

		b2FixtureDef FixtureDef;
		FixtureDef.density = 0.f;
		FixtureDef.shape = &Shape;
		FixtureDef.filter.categoryBits = BIT_BORDER;
		FixtureDef.filter.maskBits = BIT_PLAYER | BIT_BULLET | BIT_ENEMY | BIT_WALLS | BIT_ENEMY_BULLET;
		border_vert->CreateFixture(&FixtureDef);

		b2Fixture* fixture = border_vert->CreateFixture(&FixtureDef);
		fixture->SetUserData((void*)2);
	}
	
	this->_data->assets.save_border_pos("HBorders", borders);
	this->_data->assets.save_border_pos("VBorders", borders1);
}
