#include "StaticObjects.h"
#include "SFML/Graphics.hpp"
#include "ENGINEDEFINITIONS.hpp"
#include <iostream>
#include "Contact.h"


KStudio::StaticObjects::StaticObjects(GameDataRef data) : _data(data)
{

}

void KStudio::StaticObjects::Init(b2World* world)
{
	blue_flag_picked_player = false;
	red_flag_picked_player = false;
	blue_flag_picked_enemy = false;
	red_flag_picked_enemy = false;

	////////////////////////////////////   VERTICAL BUSH    ////////////////////////////////////////////////

	bush_sprite_.setTexture(this->_data->assets.GetTexture("BTexture"));
	bush_sprite_.setOrigin(bush_sprite_.getGlobalBounds().width / 2, bush_sprite_.getGlobalBounds().height / 2);

	bodyUserData* myStruct = new bodyUserData;
	myStruct->type = 3;

	b2BodyDef BodyDef;
	std::vector<b2Vec2> bushes;
	bushes.push_back(b2Vec2(300.f / SCALE, 525.f / SCALE)); // Middle left bush
	bushes.push_back(b2Vec2(830.f / SCALE, 525.f / SCALE)); // Middle right bush
	bushes.push_back(b2Vec2(90.f / SCALE, 300.f / SCALE)); // Top Left bush vertical
	bushes.push_back(b2Vec2(90.f / SCALE, 740.f / SCALE)); // Bottom Left push vertical
	bushes.push_back(b2Vec2(1045.f / SCALE, 300.f / SCALE)); // Top Right bush vertical
	bushes.push_back(b2Vec2(1045.f / SCALE, 740.f / SCALE)); // Bottom Right bush vertical
	for (auto i = 0; i < bushes.size(); i++)
	{
		BodyDef.position = b2Vec2(bushes[i]);
		BodyDef.type = b2_staticBody;
		bush_body = world->CreateBody(&BodyDef);
		bush_body->SetUserData(myStruct);

		b2PolygonShape Shape;
		sf::Vector2f v[1];
		v[0].x = ((bush_sprite_.getGlobalBounds().width / 2) / SCALE) * 0.5f;
		v[0].y = ((bush_sprite_.getGlobalBounds().height / 2) / SCALE) * 0.85f;
		Shape.SetAsBox(v->x, v->y);

		b2FixtureDef FixtureDef;
		FixtureDef.density = 0.f;
		FixtureDef.shape = &Shape;
		FixtureDef.filter.categoryBits = BIT_WALLS;
		FixtureDef.filter.maskBits = BIT_PLAYER | BIT_BULLET | BIT_ENEMY | BIT_BORDER | BIT_ENEMY_BULLET | BIT_ENEMY_RADER | BIT_ENEMY_OBJECT_FINDER;
		bush_body->CreateFixture(&FixtureDef);

		b2Fixture* fixture = bush_body->CreateFixture(&FixtureDef);
		fixture->SetUserData((void*)2); //Userdata is 2
	}

	
	sprites.push_back(bush_sprite_);/* Middle left bush save_sprites */ 
	sprites.push_back(bush_sprite_);// Middle right bush
	sprites.push_back(bush_sprite_);// Top Left bush vertical
	sprites.push_back(bush_sprite_);// Bottom Left bush vertical
	sprites.push_back(bush_sprite_);// Top Right bush vertical
	sprites.push_back(bush_sprite_);// Bottom Right bush vertical
	spritesPos.push_back(sf::Vector2f((300.f / SCALE) * SCALE + 390.f, (525.f / SCALE) * SCALE + 15.f));  // Middle left bush Position
	spritesPos.push_back(sf::Vector2f((830.f / SCALE) * SCALE + 390.f, (525.f / SCALE) * SCALE + 15.f)); // Middle Right bush Position 
	spritesPos.push_back(sf::Vector2f((90.f / SCALE) * SCALE + 390.f, (300.f / SCALE) * SCALE + 15.f));  // Top left bush Position vertical
	spritesPos.push_back(sf::Vector2f((90.f / SCALE) * SCALE + 390.f, (740.f / SCALE) * SCALE + 15.f)); // Bottom left bush Position vertical
	spritesPos.push_back(sf::Vector2f((1045.f / SCALE) * SCALE + 390.f, (300.f / SCALE) * SCALE + 15.f));  // Top Right bush Position vertical
	spritesPos.push_back(sf::Vector2f((1045.f / SCALE) * SCALE + 390.f, (740.f / SCALE) * SCALE + 15.f)); // Bottom Right bush Position vertical

	////////////////////////////////////   Horizontal BUSH    ////////////////////////////////////////////////

	bush_sprite_rotated_.setTexture(this->_data->assets.GetTexture("BRTexture"));
	bush_sprite_rotated_.setOrigin(bush_sprite_rotated_.getGlobalBounds().width / 2, bush_sprite_rotated_.getGlobalBounds().height / 2);

	std::vector<b2Vec2> bushes1;
	bushes1.push_back(b2Vec2(560.f / SCALE, 250.f / SCALE)); //Top Middle Bush
	bushes1.push_back(b2Vec2(560.f / SCALE, 800.f / SCALE)); //Bottom middle bush
	bushes1.push_back(b2Vec2(-60.f / SCALE, 230.f / SCALE)); //left Top Bush horizontal
	bushes1.push_back(b2Vec2(-60.f / SCALE, 815.f / SCALE)); //left bottom bush horizontal
	bushes1.push_back(b2Vec2(1200.f / SCALE, 230.f / SCALE)); //left Top Bush horizontal
	bushes1.push_back(b2Vec2(1200.f / SCALE, 815.f / SCALE)); //left bottom bush horizontal
	for (auto i = 0; i < bushes1.size(); i++)
	{
		BodyDef.position = b2Vec2(bushes1[i]);
		BodyDef.type = b2_staticBody;
		b2Body* Body = world->CreateBody(&BodyDef);
		Body->SetUserData(myStruct);

		b2PolygonShape Shape;
		sf::Vector2f v[1];
		v[0].x = ((bush_sprite_rotated_.getGlobalBounds().width / 2) / SCALE) * 0.85f;
		v[0].y = ((bush_sprite_rotated_.getGlobalBounds().height / 2) / SCALE) * 0.5f;
		Shape.SetAsBox(v->x, v->y);

		b2FixtureDef FixtureDef;
		FixtureDef.density = 0.f;
		FixtureDef.shape = &Shape;
		FixtureDef.filter.categoryBits = BIT_WALLS;
		FixtureDef.filter.maskBits = BIT_PLAYER | BIT_BULLET | BIT_ENEMY | BIT_BORDER | BIT_ENEMY_BULLET | BIT_ENEMY_RADER | BIT_ENEMY_OBJECT_FINDER;
		Body->CreateFixture(&FixtureDef);

		b2Fixture* fixture = Body->CreateFixture(&FixtureDef);
		fixture->SetUserData((void*)2); //Userdata is 2
	}

	sprites.push_back(bush_sprite_rotated_); //Top Middle Bush
	sprites.push_back(bush_sprite_rotated_); //Bottom middle bush
	sprites.push_back(bush_sprite_rotated_); //left Top Bush horizontal
	sprites.push_back(bush_sprite_rotated_); //left bottom bush horizontal
	sprites.push_back(bush_sprite_rotated_); //right Top Bush horizontal
	sprites.push_back(bush_sprite_rotated_); //right bottom bush horizontal
	spritesPos.push_back(sf::Vector2f((560.f / SCALE) * SCALE + 390.f, (250.f / SCALE) * SCALE + 15.f)); //Top Middle Bush position
	spritesPos.push_back(sf::Vector2f((560.f / SCALE) * SCALE + 390.f, (800.f / SCALE) * SCALE + 15.f)); //Cottom Middle Bush position
	spritesPos.push_back(sf::Vector2f((-60.f / SCALE) * SCALE + 390.f, (230.f / SCALE) * SCALE + 15.f)); //left Top Bush horizontal
	spritesPos.push_back(sf::Vector2f((-60.f / SCALE) * SCALE + 390.f, (815.f / SCALE) * SCALE + 15.f)); //left bottom bush horizontal
	spritesPos.push_back(sf::Vector2f((1200.f / SCALE) * SCALE + 390.f, (230.f / SCALE) * SCALE + 15.f)); //rigt Top Bush horizontal
	spritesPos.push_back(sf::Vector2f((1200.f / SCALE) * SCALE + 390.f, (815.f / SCALE) * SCALE + 15.f)); //right bottom bush horizontal


	////////////////////////////////////   RED PEDESTAL  ////////////////////////////////////////////////

	red_ped_.setTexture(this->_data->assets.GetTexture("redPed"));
	red_ped_.setOrigin(red_ped_.getGlobalBounds().width / 2, red_ped_.getGlobalBounds().height / 2);

	std::vector<b2Vec2> redpedestal;
	redpedestal.push_back(b2Vec2(-170.f / SCALE, 525.f / SCALE)); //Red Pedestal
	for (auto i = 0; i < redpedestal.size(); i++)
	{
		BodyDef.position = b2Vec2(redpedestal[i]);
		BodyDef.type = b2_staticBody;
		b2Body* Body = world->CreateBody(&BodyDef);
		Body->SetUserData(myStruct);

		b2PolygonShape Shape;
		Shape.SetAsBox(((red_ped_.getGlobalBounds().width / 2) / SCALE), ((red_ped_.getGlobalBounds().height / 2) / SCALE));

		b2FixtureDef FixtureDef;
		FixtureDef.density = 0.f;
		FixtureDef.shape = &Shape;
		FixtureDef.filter.categoryBits = BIT_RED_PED;
		FixtureDef.filter.maskBits = BIT_PLAYER | BIT_BULLET | BIT_ENEMY_BULLET | BIT_RED_FLAG;
		Body->CreateFixture(&FixtureDef);

		b2Fixture* fixture = Body->CreateFixture(&FixtureDef);
		fixture->SetUserData((void*)3); //Userdata is 3

		float radius = 9;
		b2Vec2 vertices[8];
		vertices[0].Set(0, 0);
		for (int i = 0; i < 7; i++) {
			float angle = i / 6.0 * 180 * (b2_pi / 180) + 4.71f;
			vertices[i + 1].Set(radius * cosf(angle), radius * sinf(angle));
		}

		b2PolygonShape area_shape;
		area_shape.Set(vertices, 8);

		b2FixtureDef red_base_area_fix_def;
		red_base_area_fix_def.shape = &area_shape;
		red_base_area_fix_def.isSensor = true;
		red_base_area_fix_def.filter.categoryBits = BIT_PLAYER_BASE_AREA;
		red_base_area_fix_def.filter.maskBits = BIT_PLAYER;
		Body->CreateFixture(&red_base_area_fix_def);

		b2Fixture* red_base_area_fixture = Body->CreateFixture(&red_base_area_fix_def);
		red_base_area_fixture->SetUserData((void*)5);
	}

	sprites.push_back(red_ped_); //Top Middle Bush
	spritesPos.push_back(sf::Vector2f((-170.f / SCALE) * SCALE + 390.f, (525.f / SCALE) * SCALE + 15.f)); // Red Pedestal

	////////////////////////////////////   BLUE PEDESTAL    ////////////////////////////////////////////////

	blue_ped_.setTexture(this->_data->assets.GetTexture("bluePed"));
	blue_ped_.setOrigin(blue_ped_.getGlobalBounds().width / 2, blue_ped_.getGlobalBounds().height / 2);

	std::vector<b2Vec2> bluepedestal;
	bluepedestal.push_back(b2Vec2(1305.f / SCALE, 525.f / SCALE)); //Blue Pedestal
	for (auto i = 0; i < bluepedestal.size(); i++)
	{
		BodyDef.position = b2Vec2(bluepedestal[i]);
		BodyDef.type = b2_staticBody;
		b2Body* Body = world->CreateBody(&BodyDef);
		Body->SetUserData(myStruct);

		b2PolygonShape Shape;
		Shape.SetAsBox(((blue_ped_.getGlobalBounds().width / 2) / SCALE), ((blue_ped_.getGlobalBounds().height / 2) / SCALE));

		b2FixtureDef FixtureDef;
		FixtureDef.density = 0.f;
		FixtureDef.shape = &Shape;
		FixtureDef.filter.categoryBits = BIT_BLUE_PED;
		FixtureDef.filter.maskBits = BIT_ENEMY | BIT_BULLET | BIT_ENEMY_BULLET |BIT_BLUE_FLAG;
		Body->CreateFixture(&FixtureDef);

		b2Fixture* fixture = Body->CreateFixture(&FixtureDef);
		fixture->SetUserData((void*)4); //Userdata is 4

		float radius = 9;
		b2Vec2 vertices[8];
		vertices[0].Set(0, 0);
		for (int i = 0; i < 7; i++) {
			float angle = i / 6.0 * 180 * (b2_pi / 180) - 4.71f;
			vertices[i + 1].Set(radius * cosf(angle), radius * sinf(angle));
		}

		b2PolygonShape area_shape;
		area_shape.Set(vertices, 8);

		b2FixtureDef blue_base_area_fix_def;
		blue_base_area_fix_def.shape = &area_shape;
		blue_base_area_fix_def.isSensor = true;
		blue_base_area_fix_def.filter.categoryBits = BIT_ENEMY_BASE_AREA;
		blue_base_area_fix_def.filter.maskBits = BIT_ENEMY;
		Body->CreateFixture(&blue_base_area_fix_def);

		b2Fixture* blue_base_area_fixture = Body->CreateFixture(&blue_base_area_fix_def);
		blue_base_area_fixture->SetUserData((void*)6);
	}

	sprites.push_back(blue_ped_); //Blue Pedestal 
	spritesPos.push_back(sf::Vector2f((1305.f / SCALE) * SCALE + 390.f, (525.f / SCALE) * SCALE + 15.f)); // Blue Pedestal Position

	////////////////////////////////////   Red Flag    ////////////////////////////////////////////////

	red_flag_.setTexture(this->_data->assets.GetTexture("redFlag"));
	red_flag_.setOrigin(red_flag_.getGlobalBounds().width / 2, red_flag_.getGlobalBounds().height / 2);

	std::vector<b2Vec2> redflag;
	redflag.push_back(b2Vec2(-170.f / SCALE, 525.f / SCALE)); //Blue Pedestal
	for (auto i = 0; i < redflag.size(); i++)
	{
		BodyDef.position = b2Vec2(redflag[i]);
		BodyDef.type = b2_staticBody;
		red_flag_body = world->CreateBody(&BodyDef);
		red_flag_body->SetUserData(myStruct);

		b2PolygonShape Shape;
		Shape.SetAsBox(((red_flag_.getGlobalBounds().width / 2) / SCALE), ((red_flag_.getGlobalBounds().height / 2) / SCALE));

		b2FixtureDef FixtureDef;
		FixtureDef.density = 0.f;
		FixtureDef.shape = &Shape;
		FixtureDef.isSensor = true;
		FixtureDef.filter.categoryBits = BIT_RED_FLAG;
		FixtureDef.filter.maskBits = BIT_ENEMY | BIT_PLAYER | BIT_RED_PED;
		red_flag_body->CreateFixture(&FixtureDef);

		b2Fixture* fixture = red_flag_body->CreateFixture(&FixtureDef);
		fixture->SetUserData((void*)17); //Userdata is 17
	}

	sprites.push_back(red_flag_); //Red flag 
	spritesPos.push_back(sf::Vector2f((-170.f / SCALE) * SCALE + 390.f, (525.f / SCALE) * SCALE + 15.f)); // Red flag Position
	//sprites[14].setPosition(spritesPos[14].x, spritesPos[14].y);

	////////////////////////////////////   BLUE Flag    ////////////////////////////////////////////////

	blue_flag_.setTexture(this->_data->assets.GetTexture("blueFlag"));
	blue_flag_.setOrigin(blue_flag_.getGlobalBounds().width / 2, blue_flag_.getGlobalBounds().height / 2);

	std::vector<b2Vec2> blueflag;
	blueflag.push_back(b2Vec2(1305.f / SCALE, 525.f / SCALE)); //Blue Pedestal
	for (auto i = 0; i < blueflag.size(); i++)
	{
		BodyDef.position = b2Vec2(blueflag[i]);
		BodyDef.type = b2_dynamicBody;
		blue_flag_body = world->CreateBody(&BodyDef);
		blue_flag_body->SetUserData(myStruct);

		b2PolygonShape Shape;
		Shape.SetAsBox(((red_flag_.getGlobalBounds().width / 2) / SCALE), ((red_flag_.getGlobalBounds().height / 2) / SCALE));

		b2FixtureDef FixtureDef;
		FixtureDef.density = 0.f;
		FixtureDef.shape = &Shape;
		FixtureDef.isSensor = true;
		FixtureDef.filter.categoryBits = BIT_BLUE_FLAG;
		FixtureDef.filter.maskBits = BIT_ENEMY | BIT_PLAYER | BIT_BLUE_PED;
		blue_flag_body->CreateFixture(&FixtureDef);

		b2Fixture* fixture = blue_flag_body->CreateFixture(&FixtureDef);
		fixture->SetUserData((void*)18); //Userdata is 18
	}

	sprites.push_back(blue_flag_); //Blue flag
	spritesPos.push_back(sf::Vector2f((1305.f / SCALE) * SCALE + 390.f, (525.f / SCALE) * SCALE + 15.f)); // Blue flag Position
	sprites[15].setPosition(spritesPos[15].x, spritesPos[15].y);// Blue flag

	this->_data->assets.save_sprites("StaticObjectsSprites", sprites);
}

void KStudio::StaticObjects::Update()
{
	this->_data->assets.getSprite("StaticObjectsSprites", 0).setPosition(spritesPos[0].x, spritesPos[0].y); // Middle Left Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 1).setPosition(spritesPos[1].x, spritesPos[1].y); // Middle Right Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 2).setPosition(spritesPos[2].x, spritesPos[2].y); // Left top Vert Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 3).setPosition(spritesPos[3].x, spritesPos[3].y); // Left Bottom vert Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 4).setPosition(spritesPos[4].x, spritesPos[4].y); // Right top vert Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 5).setPosition(spritesPos[5].x, spritesPos[5].y); // Right Bottom vert Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 6).setPosition(spritesPos[6].x, spritesPos[6].y); // Middle Top Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 7).setPosition(spritesPos[7].x, spritesPos[7].y); // Middle Bottom Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 8).setPosition(spritesPos[8].x, spritesPos[8].y); // Left Top hori Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 9).setPosition(spritesPos[9].x, spritesPos[9].y); // Left Bottom hori Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 10).setPosition(spritesPos[10].x, spritesPos[10].y); // Right Top hori Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 11).setPosition(spritesPos[11].x, spritesPos[11].y); // Right Bottom hori Bush
	this->_data->assets.getSprite("StaticObjectsSprites", 12).setPosition(spritesPos[12].x, spritesPos[12].y); // Red Flag Pedestal
	this->_data->assets.getSprite("StaticObjectsSprites", 13).setPosition(spritesPos[13].x, spritesPos[13].y); // Blue Flag Pedestal
	this->_data->assets.getSprite("StaticObjectsSprites", 14).setPosition(red_flag_body->GetPosition().x * SCALE + 390.f, red_flag_body->GetPosition().y * SCALE + 15.f); // Red Flag
	this->_data->assets.getSprite("StaticObjectsSprites", 15).setPosition(blue_flag_body->GetPosition().x * SCALE + 390.f, blue_flag_body->GetPosition().y * SCALE + 15.f); // Blue Flag
	
}

void KStudio::StaticObjects::Update(bool playerScore, bool enemyScore, bool blue_flag_returned, bool red_flag_returned, bool blue_flag_player, bool blue_flag_enemy, bool red_flag_player, bool red_flag_enemy, 
	b2Body* player_body, b2Body* enemy_body, bool has_player_died, bool has_enemy_died)
{
	////////////////////Handle Player and Flag collision//////////////////////////////////

	// Blue flag picked by player
	//if Blue flag(15) gets picked by player, blue flag position is set to player position
	if (blue_flag_player && !playerScore) 
	{
		blue_flag_picked_player = true;
		blue_flag_body->SetTransform(player_body->GetPosition(), player_body->GetAngle());
		previous_pos_blue_flag = player_body->GetPosition();

	}
	else
	{
		blue_flag_picked_player = false;
		
	}
	if(has_player_died && blue_flag_player)
	{
		blue_flag_body->SetTransform(b2Vec2(600.f / SCALE, 525.f / SCALE), blue_flag_body->GetAngle());
	}

	//if player successfully takes blue flag to red base
	//Player scores, and Blue flag(15) is reset
	if (playerScore)
	{
		blue_flag_body->SetTransform(b2Vec2(1305.f / SCALE, 525.f / SCALE), blue_flag_body->GetAngle());
	}


	// Red flag picked by player
	//if RED flag(14) gets picked by player, 
	//Red flag(14) position gets set to player position
	if (red_flag_player && !red_flag_returned) 
	{
		red_flag_picked_player = true;
		red_flag_body->SetTransform(player_body->GetPosition(), player_body->GetAngle());

	}
	else
	{
		red_flag_picked_player = false;
	}

	if (has_player_died && red_flag_player)
	{
		red_flag_body->SetTransform(b2Vec2(500.f / SCALE, 525.f / SCALE), red_flag_body->GetAngle());
	}

	//if player successfully takes red flag(14) to red base
	//Red flag gets places back to original position
	if (red_flag_returned)
	{
		red_flag_body->SetTransform(b2Vec2(-170.f / SCALE, 525.f / SCALE), red_flag_body->GetAngle());
	}


	///////////////////Handle Enemy and Flag Collision////////////////////////////////////////////////////////////////////////////
	//Red flag picked by enemy
	//if Red flag(14) gets picked by enemy, red flag position is set to enemy position
	if (red_flag_enemy && !enemyScore) // Red flag picked by enemy
	{
		red_flag_picked_enemy = true;
		red_flag_body->SetTransform(enemy_body->GetPosition(), enemy_body->GetAngle());

	}
	else
	{
		red_flag_picked_enemy = false;
	}

	if (has_enemy_died && red_flag_enemy)
	{
		red_flag_body->SetTransform(b2Vec2(600.f / SCALE, 525.f / SCALE), red_flag_body->GetAngle());
	}

	//if enemy successfully takes red flag to blue base
	//enemy scores, and red flag(14) is reset
	if (enemyScore)
	{
		red_flag_body->SetTransform(b2Vec2(-170.f / SCALE, 525.f / SCALE), red_flag_body->GetAngle());
	}

	// Blue flag picked by enemy
	//if blue flag(15) gets picked by enemy, 
	//Blue flag(15) position gets set to enemy position
	if (blue_flag_enemy && !blue_flag_returned)
	{
		blue_flag_picked_enemy = true;
		blue_flag_body->SetTransform(enemy_body->GetPosition(), enemy_body->GetAngle());

	}
	else
	{
		blue_flag_picked_enemy = false;
	}

	if (has_enemy_died && blue_flag_enemy)
	{
		blue_flag_body->SetTransform(b2Vec2(600.f / SCALE, 525.f / SCALE), blue_flag_body->GetAngle());
	}

	//if enemy successfully takes blue flag(15) to blue base
	//Blue flag gets places back to original position
	if (blue_flag_returned)
	{
		blue_flag_body->SetTransform(b2Vec2(1305.f / SCALE, 525.f / SCALE), blue_flag_body->GetAngle());
	}
}

void KStudio::StaticObjects::Draw()
{
	
	for (auto i = 0; i < sprites.size(); i++)
	{
		this->_data->window.draw(this->_data->assets.getSprite("StaticObjectsSprites", i));
		//this->_data->window.draw(sprites[i]); // Draws all the sprites as they are the same one
	}
}
