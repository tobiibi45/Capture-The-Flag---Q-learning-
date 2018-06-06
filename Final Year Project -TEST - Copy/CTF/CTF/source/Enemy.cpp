#include "Enemy.h"
#include "ENGINEDEFINITIONS.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

KStudio::Enemy::Enemy(GameDataRef data) : _data(data)
{

}

void KStudio::Enemy::Init(b2World* world)
{
	scene_changer = 0;

	ql.train(scene_changer);
	ql.test(scene_changer);
	qls.train(scene_changer);
	qls.test(scene_changer);
	states = begin;
	cout << "FirstState:  " << ql.current_state << endl;
	cout << "SecondState:  " << ql.next_state << endl;
	cout << "ThirdState:  " << ql.third_state << endl;

	b_at_base_ = true;;
	the_actorhealth = 0.f;
	enemy_radar_radius = 12;
	timer = 0;
	searc_timer.restart();
	for_health = false;
	m_speed = 2.f;
	acceleration = 0.1f;
	next_fire_time = 0;
	current_time.restart();
	actor_spawn = b2Vec2(1250.f / SCALE, 500.f / SCALE);
	respawn.restart();
	is_at_goal = false;
	radius = 0.5f;
	reset = true;
	reset1 = true;
	player_was_found = false;
	the_angle = 0;

	path_finder = new PathFinder(_data);
	path_finder->iniStartGoal = false;
	path_finder->foundGoal = false;
	path_finder->clearOpenList();
	path_finder->clearVisitedList();
	path_finder->cleaPathToGoal();

	e_sprite_.setTexture(this->_data->assets.GetTexture("EnemyDoctor"));
	healthbar.setTexture(this->_data->assets.GetTexture("healthbar"));
	healthbar_backg.setTexture(this->_data->assets.GetTexture("healthbar_backg"));

	//!set structure contents as necessary
	bodyUserData* myStruct = new bodyUserData;
	myStruct->type = 11;

	//!Set the Bodydef as necessary
	b2BodyDef BodyDef;
	BodyDef.position.Set(500.f / SCALE, 500.f / SCALE);
	BodyDef.type = b2_dynamicBody;
	e_body_ = world->CreateBody(&BodyDef);
	e_body_->SetUserData(myStruct);

	b2CircleShape circleShape;
	circleShape.m_radius = radius;

	//!Set the Fixturedef
	b2FixtureDef FixtureDef;
	FixtureDef.density = 100.f;
	FixtureDef.friction = 0.5f;
	FixtureDef.shape = &circleShape;
	FixtureDef.filter.categoryBits = BIT_ENEMY;
	FixtureDef.filter.maskBits = BIT_WALLS | BIT_BULLET | BIT_BORDER | BIT_BLUE_PED | BIT_RED_FLAG | BIT_BLUE_FLAG | BIT_ENEMY_BASE_AREA;
	e_body_->CreateFixture(&FixtureDef);

	e_body_->SetFixedRotation(true);

	//!Set the Fixture data as necessary
	fixture = e_body_->CreateFixture(&FixtureDef);
	fixture->SetUserData((void*)11);

	b2CircleShape circleShapeSens;
	circleShape.m_radius = 8;

	b2FixtureDef FixtureDefSensor;
	b2Vec2 vertices[8];
	vertices[0].Set(0, 0);
	for (int i = 0; i < 7; i++) {
		float angle = i / 6.0 * 360 * (b2_pi / 180) + 15;
		vertices[i + 1].Set(enemy_radar_radius * cosf(angle), enemy_radar_radius * sinf(angle));
	}
	b2PolygonShape p_shape;
	p_shape.Set(vertices, 8);
	FixtureDefSensor.shape = &p_shape;
	FixtureDefSensor.isSensor = true;
	FixtureDefSensor.filter.categoryBits = BIT_ENEMY_RADER;
	FixtureDefSensor.filter.maskBits = BIT_PLAYER | BIT_RED_FLAG | BIT_BLUE_FLAG | BIT_BULLET | BIT_WALLS;
	e_body_->CreateFixture(&FixtureDefSensor);

	b2Fixture* fixtureSensor = e_body_->CreateFixture(&FixtureDefSensor);
	fixtureSensor->SetUserData((void*)12);

	float radius1 = 10;
	b2Vec2 vertices1[8];
	vertices1[0].Set(0, 0);
	for (int i = 0; i < 7; i++) {
		float angle1 = i / 6.0 * 5 * (b2_pi / 180) + 15.7;
		vertices1[i + 1].Set(radius1 * cosf(angle1), radius1 * sinf(angle1));
	}
	b2FixtureDef FixtureDefCanShoot;
	b2PolygonShape b_shape;
	b_shape.Set(vertices1, 8);
	FixtureDefCanShoot.shape = &b_shape;
	FixtureDefCanShoot.isSensor = true;
	FixtureDefCanShoot.filter.categoryBits = BIT_ENEMY_OBJECT_FINDER;
	FixtureDefCanShoot.filter.maskBits =  BIT_BULLET | BIT_WALLS;
	e_body_->CreateFixture(&FixtureDefCanShoot);

	b2Fixture* fixtureCanShoot = e_body_->CreateFixture(&FixtureDefCanShoot);
	fixtureCanShoot->SetUserData((void*)21);

	//!Initialising the movement speed
	direction = 0;

	desirevelocityX = fmax(e_body_->GetLinearVelocity().x - acceleration,
		fmin(direction * m_speed, e_body_->GetLinearVelocity().x + acceleration));

	desirevelocityY = fmax(e_body_->GetLinearVelocity().y - acceleration,
		fmin(direction * m_speed, e_body_->GetLinearVelocity().y + acceleration));

	e_sprite_.setPosition((e_body_->GetPosition().x) * SCALE + 390.f, e_body_->GetPosition().y * SCALE + 15.f);
	e_sprite_.setScale(0.5f, 0.5f);
	e_sprite_.setOrigin(90.f, 45.f);

	healthbar.setOrigin(-20.f, 50.f);
	healthbar.setPosition(e_sprite_.getPosition().x, e_sprite_.getPosition().y);
	healthbar_backg.setPosition(healthbar.getPosition().x, healthbar.getPosition().y);
	healthbar_backg.setPosition(healthbar.getPosition().x, healthbar.getPosition().y);
	healthbar_backg.setOrigin(healthbar.getOrigin());
}

void KStudio::Enemy::Update(b2Body* body, float dt, sf::Vector2f targetPos, float actorhealth, bool enemy_score)
{
	the_actorhealth = actorhealth;
	const float player_angle = angle_to_target(e_sprite_.getPosition(), targetPos) * (b2_pi / 180);
	healthbar.setOrigin(-20.f, 50.f);
	healthbar.setPosition(e_sprite_.getPosition().x, e_sprite_.getPosition().y);
	healthbar.setRotation(e_sprite_.getRotation());
	healthbar_backg.setPosition(healthbar.getPosition().x, healthbar.getPosition().y);
	healthbar_backg.setOrigin(healthbar.getOrigin());
	healthbar_backg.setRotation(healthbar.getRotation());

	e_sprite_.setScale(0.5f, 0.5f);
	e_sprite_.setOrigin(90.f, 45.f);
	e_sprite_.setPosition((body->GetPosition().x) * SCALE + 390.f, body->GetPosition().y * SCALE + 15.f);
	e_sprite_.setRotation(body->GetAngle() * (180 / b2_pi));

	momentum = e_body_->GetLinearVelocity();
	// fOR VERTICAL MOVEMENT
	velocityChangeX = desirevelocityX - momentum.x;
	impulseX = e_body_->GetMass() * velocityChangeX;

	// fOR HORIZONTAL MOVEMENT
	velocityChangeY = desirevelocityY - momentum.y;
	impulseY = e_body_->GetMass() * velocityChangeY;

	if (actorhealth >= 0)
	{
		healthbar.setScale(1, actorhealth / actors_max_health);
		e_body_->ApplyLinearImpulse(b2Vec2(impulseX * dt, impulseY * dt), e_body_->GetWorldCenter(), true);
	}
}

void KStudio::Enemy::move_enemy(float direction, bool no_pp)
{
	if (no_pp)
	{
		desirevelocityX = -cos(direction) * (m_speed * 5.f);
		desirevelocityY = -sin(direction) * (m_speed * 5.f);
	}
	else
	{
		desirevelocityX = cos(direction) * (m_speed * 5.f);
		desirevelocityY = sin(direction) * (m_speed * 5.f);
	}
}

void KStudio::Enemy::stop_enemy()
{
	desirevelocityX = 0;
	desirevelocityY = 0;
}

void KStudio::Enemy::reset_actor(b2Body* body, float angle)
{
	e_body_->SetTransform(actor_spawn, angle);
}


void KStudio::Enemy::Draw()
{
	this->_data->window.draw(e_sprite_);
	if (the_actorhealth >= 0)
	{
		this->_data->window.draw(healthbar);
	}
	this->_data->window.draw(healthbar_backg);
}

void KStudio::Enemy::Draw_Pathfinder(sf::Sprite &sprite)
{
	path_finder->draw_debug(this->_data->window, sprite, getSprite());
}

sf::Vector2f KStudio::Enemy::getPosition()
{
	auto x = e_sprite_.getPosition().x;
	auto y = e_sprite_.getPosition().y;
	const sf::Vector2f position(x, y);
	return position;
}

b2Body*& KStudio::Enemy::getBody()
{
	b2Body* &body = e_body_;
	return body;
}

b2Fixture*& KStudio::Enemy::getFixture()
{
	b2Fixture* &fixture = this->fixture;
	return fixture;
}

sf::Sprite &KStudio::Enemy::getSprite()
{
	sf::Sprite &sprite = e_sprite_;
	return sprite;
}

void KStudio::Enemy::enemy_AI(sf::Vector2f player_pos, sf::Vector2f red_flag_pos, sf::Vector2f blue_flag_pos, sf::Vector2f base_pos, b2Body* body, int enemy_bullet, 
	float enemy_health, bool red_flag_picked_player, bool blue_flag_picked_player, bool red_flag_picked_enemy, bool blue_flag_picked_enemy, float player_health, bool player_in_range,
	bool red_flag_in_range, bool blue_flag_in_range, bool player_score, bool enemy_score, bool enemy_hit, bool player_dead, bool red_flag_at_base, bool blue_flag_at_base, bool object_found, bool full_health)
{

	path_finder->update();
	
	
	if (enemy_health > 0)
	{
		switch (states)
		{
		case begin:
		{

			path_finder->cleaPathToGoal();
			path_finder->clearOpenList();
			path_finder->clearVisitedList();
			path_finder->iniStartGoal = false;
			path_finder->foundGoal = false;
			is_at_goal = false;
			target_pos = red_flag_pos;
			reset_actor(body, angle_to_target(e_sprite_.getPosition(), target_pos) * (b2_pi / 180));
			states = searching;
		}
		break;

		case searching:
		{
			if (ql.current_state == 4 && !for_health)  //Blue Base
			{
				target_pos = base_pos;
				path_finder->findPath(e_sprite_.getPosition(), target_pos);
				is_at_goal = false;
				stop_enemy();
				if (path_finder->foundGoal)
				{
					states = found_base;
					std::cout << "SEARCHING AND FOUND Base" << std::endl;
				}
			}
			if ((ql.current_state == 4) && for_health)  //Blue Base
			{
				target_pos = base_pos;
				path_finder->findPath(e_sprite_.getPosition(), target_pos);
				is_at_goal = false;
				stop_enemy();
				if (path_finder->foundGoal)
				{
					states = found_base_health;
					std::cout << "SEARCHING AND FOUND Base for health" << std::endl;
				}
			}

				if ((ql.current_state == 1 || ql.current_state == 0))  //Red Flag
				{
					target_pos = red_flag_pos;
					path_finder->findPath(e_sprite_.getPosition(), target_pos);
					is_at_goal = false;
					stop_enemy();
					if (path_finder->foundGoal)
					{
						states = found_red_flag;
						std::cout << "SEARCHING AND FOUND RED FLAG" << std::endl;
					}
				}
				if (ql.current_state == 2)  //PLayer
				{
					target_pos = player_pos;
					path_finder->findPath(e_sprite_.getPosition(), target_pos);
					is_at_goal = false;
					stop_enemy();
					if (path_finder->foundGoal)
					{
						scene_changer_shoot = 0;
						ql.test(scene_changer);
						states = found_player;
						std::cout << "SEARCHING AND FOUND PLAYER " << std::endl;
					}
				}
			if (ql.current_state == 3) // BLUE FLAG
			{
				target_pos = blue_flag_pos;
				path_finder->findPath(e_sprite_.getPosition(), target_pos);
				is_at_goal = false;
				stop_enemy();
				if (path_finder->foundGoal)
				{
					states = found_blue_flag;
					std::cout << "SEARCHING AND FOUND BLUE FLAG" << std::endl;
				}
			}

			if (timer < static_cast<int>(searc_timer.getElapsedTime().asSeconds()))
			{
				scene_changer = 1; // Third state in the Q table (Player)
				ql.test(scene_changer);
				path_finder->cleaPathToGoal();
				stop_enemy();
				is_at_goal = false;
				path_finder->iniStartGoal = false;
				path_finder->foundGoal = false;
				states = searching;
				timer = static_cast<int>(searc_timer.getElapsedTime().asSeconds()) + 5;
			}

			if (target_pos.x < 0 || target_pos.x > WORLD_SIZE * CELL_SIZE || target_pos.y < 0 || target_pos.y > WORLD_SIZE *
				CELL_SIZE)
			{
				path_finder->iniStartGoal = false;
				path_finder->foundGoal = false;
				path_finder->clearOpenList();
				path_finder->clearVisitedList();
				stop_enemy();
				//std::cout << "SEARCHING and OUT OF BOUNDS" << std::endl;
			}
			//std::cout << "SEARCHING AND FINDING PLAYER" << std::endl;
		}
		break;

		case found_red_flag:
		{
			// state 1 in Q matirx
			dist = e_sprite_.getPosition() - red_flag_pos;

			if (!is_at_goal)
			{
				fire_bullet = false;
				dist_to_target_p = path_finder->nextPathpos(e_sprite_.getPosition()) - e_sprite_.getPosition();
				the_angle = angle_path_finder(dist_to_target_p);
				the_path_angle = angle_path_finder(dist);
				e_body_->SetTransform(body->GetPosition(), the_path_angle * (b2_pi / 180));
				move_enemy(the_angle * (b2_pi / 180), false);

				if (timer < static_cast<int>(searc_timer.getElapsedTime().asSeconds()))
				{
					scene_changer = 1; 
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					stop_enemy();
					is_at_goal = false;
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;
					timer = static_cast<int>(searc_timer.getElapsedTime().asSeconds()) + 5;
				}

				if (player_in_range && !player_dead)
				{
					for_health = true;
					scene_changer = 2;
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = false;
					stop_enemy();
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;
				}

				if (enemy_health == 0)
				{
					respawn.restart();
				}

			}

			if (!blue_flag_at_base)
			{
				scene_changer = 3; // Fifth state in the Q table (Blue Base Score)
				ql.test(scene_changer);
				path_finder->cleaPathToGoal();
				is_at_goal = true;
				path_finder->iniStartGoal = false;
				path_finder->foundGoal = false;
				cout << "CurrentState in Q:  " << ql.current_state << endl;
				states = searching;
			}

			dist_length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));
			if (red_flag_picked_enemy || enemy_health < ENEMY_HEALTH_RANGE)
			{
				if (red_flag_picked_enemy)
				{
					for_health = false;
					scene_changer = 4; // Fifth state in the Q table (Blue Base Score)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = true;
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					//ql->current_state = ql->next_state;
					cout << "CurrentState in Q:  " << ql.current_state << endl;
					states = searching;
				}

				if (enemy_health < 50)
				{
					for_health = true;
					scene_changer = 4; // Fifth state in the Q table (Blue Base Score)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = true;
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					cout << "CurrentState in Q:  " << ql.current_state << endl;
					states = searching;
				}
			}
		}
		break;

		case found_blue_flag:
		{
			b_at_base_ = false;
			dist = e_sprite_.getPosition() - blue_flag_pos;

			if (!is_at_goal)
			{
				fire_bullet = false;
				dist_to_target_p = path_finder->nextPathpos(e_sprite_.getPosition()) - e_sprite_.getPosition();
				the_angle = angle_path_finder(dist_to_target_p);
				the_path_angle = angle_path_finder(dist);
				e_body_->SetTransform(body->GetPosition(), the_path_angle * (b2_pi / 180));
				move_enemy(the_angle * (b2_pi / 180), false);

				if (timer < static_cast<int>(searc_timer.getElapsedTime().asSeconds()))
				{
					scene_changer = 3; // Third state in the Q table (Player)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					stop_enemy();
					is_at_goal = false;
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;
					timer = static_cast<int>(searc_timer.getElapsedTime().asSeconds()) + 2;
				}

				if (player_in_range && !player_dead)
				{
					for_health = true;
					scene_changer = 2;
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = false;
					stop_enemy();
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;
				}
			}
			if (enemy_health == 0)
			{
				respawn.restart();
			}

			dist_length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));
			if (enemy_health < 50 || blue_flag_picked_enemy)
			{
				if (enemy_health < ENEMY_HEALTH_RANGE)
				{
					for_health = true;
					scene_changer = 4; // Fifth state in the Q table (Blue Base Score)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = true;
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					cout << "CurrentState in Q:  " << ql.current_state << endl;
					states = searching;
				}

				if (blue_flag_picked_enemy)
				{
					for_health = false;
					scene_changer = 4; // Fifth state in the Q table (Blue Base Score)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = true;
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					cout << "CurrentState in Q:  " << ql.current_state << endl;
					states = searching;
				}
			}
		}
		break;

		case found_base_health:
		{
			// state 3 in Q matirx
			dist = e_sprite_.getPosition() - base_pos;

			if (!is_at_goal)
			{
				fire_bullet = false;
				dist_to_target_p = path_finder->nextPathpos(e_sprite_.getPosition()) - e_sprite_.getPosition();
				the_angle = angle_path_finder(dist_to_target_p);
				the_path_angle = angle_path_finder(dist);
				e_body_->SetTransform(body->GetPosition(), the_path_angle * (b2_pi / 180));
				move_enemy(the_angle * (b2_pi / 180), false);
			}

			if (enemy_health == 0)
			{
				respawn.restart();
			}

			dist_length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));
			if (dist_length < get_radius() * 2.f || enemy_health == 100)
			{
				for_health = false;
				scene_changer = 1; // Fifth state in the Q table (PLayer)
				ql.test(scene_changer);
				path_finder->cleaPathToGoal();
				is_at_goal = true;
				stop_enemy();
				path_finder->iniStartGoal = false;
				path_finder->foundGoal = false;
				states = searching;
			}
		}
		break;

		case found_base:
		{
			// state 3 in Q matirx
			dist = e_sprite_.getPosition() - base_pos;

			if (!is_at_goal)
			{
				fire_bullet = false;
				dist_to_target_p = path_finder->nextPathpos(e_sprite_.getPosition()) - e_sprite_.getPosition();
				the_angle = angle_path_finder(dist_to_target_p);
				the_path_angle = angle_path_finder(dist);
				e_body_->SetTransform(body->GetPosition(), the_path_angle * (b2_pi / 180));
				move_enemy(the_angle * (b2_pi / 180), false);

				if (player_in_range && !player_dead)
				{
					scene_changer = 2; // Third state in the Q table (Player)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = false;
					stop_enemy();
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;
				}
			}

			if (!blue_flag_at_base && !blue_flag_picked_enemy)
			{
				scene_changer = 3; // Fifth state in the Q table (Blue Base Score)
				ql.test(scene_changer);
				path_finder->cleaPathToGoal();
				is_at_goal = true;
				path_finder->iniStartGoal = false;
				path_finder->foundGoal = false;
				cout << "CurrentState in Q:  " << ql.current_state << endl;
				states = searching;
			}

			if (enemy_health == 0)
			{
				respawn.restart();
			}

			dist_length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));
			if (enemy_score || enemy_health < ENEMY_HEALTH_RANGE || blue_flag_at_base)
			{
				if(blue_flag_at_base && !b_at_base_)
				{
					for_health = false;
					scene_changer = 1; // Fifth state in the Q table (PLayer)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = true;
					stop_enemy();
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;
					b_at_base_ = true;
				}
				if (enemy_score )
				{
					for_health = false;
					scene_changer = 1; // Fifth state in the Q table (PLayer)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = true;
					stop_enemy();
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;
				}
				if (enemy_health < 50)
				{
					for_health = true;
					scene_changer = 4; // Fifth state in the Q table (PLayer)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = true;
					stop_enemy();
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;

				}
			}
		}
		break;

		case found_player:
		{
			// state 2 in Q matirx
			dist = e_sprite_.getPosition() - player_pos;
			if (!is_at_goal)
			{
				if (player_in_range && !player_dead)
				{
					scene_changer_shoot = 1;
					qls.test(scene_changer_shoot);
					if (!player_dead)
					{
						dist_to_target_p = path_finder->nextPathpos(e_sprite_.getPosition()) - e_sprite_.getPosition();
						the_angle = angle_path_finder(dist_to_target_p);
						the_path_angle = angle_path_finder(dist);
						e_body_->SetTransform(body->GetPosition(), the_path_angle * (b2_pi / 180)); //set angle to player
						move_enemy(the_angle * (b2_pi / 180), player_dead);
						if (!object_found && qls.current_state == 1)
						{
							fire_bullet = true;
						}
						else
						{
							fire_bullet = false;
						}

						if (timer < static_cast<int>(searc_timer.getElapsedTime().asSeconds()))
						{
							scene_changer = 2; // Third state in the Q table (Player)
							ql.test(scene_changer);
							path_finder->cleaPathToGoal();
							stop_enemy();
							is_at_goal = false;
							path_finder->iniStartGoal = false;
							path_finder->foundGoal = false;
							states = searching;
							timer = static_cast<int>(searc_timer.getElapsedTime().asSeconds()) + 2;
						}
					}
				}
			}

			if ((player_in_range && player_dead) || (!player_in_range && player_dead))
			{
				if (red_flag_at_base && blue_flag_at_base)   //Both red and blue flag are not picked
				{
					scene_changer = 1; // Second state in the Q table (Red Flag)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					is_at_goal = false;
					stop_enemy();
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					cout << "RFAB && BFAB" << endl;
					states = searching;
				}

				if (red_flag_at_base && !blue_flag_at_base)
				{
					if (red_flag_picked_enemy && blue_flag_picked_enemy)
					{
						scene_changer = 4; // Fourth state in the Q table (PLayer)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "BFPP OR !BFPP" << endl;
						states = searching;
					}
					else if (red_flag_picked_enemy && !blue_flag_picked_enemy)
					{
						scene_changer = 3; // Fourth state in the Q table (PLayer)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "BFPP OR !BFPP" << endl;
						states = searching;
					}
					else if (red_flag_picked_enemy && blue_flag_picked_player)
					{
						scene_changer = 3; // Fourth state in the Q table (PLayer)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "BFPP OR !BFPP" << endl;
						states = searching;
					}
					else if (!red_flag_picked_enemy && !blue_flag_picked_enemy)
					{
						scene_changer = 3; // Fourth state in the Q table (PLayer)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "BFPP OR !BFPP" << endl;
						states = searching;
					}
				}

				else if (!red_flag_at_base && !blue_flag_at_base) //Both red and blue flag have been picked
				{
					if ((red_flag_picked_enemy && blue_flag_picked_player) || (red_flag_picked_player && blue_flag_picked_enemy))
					{
						for_health = false;
						scene_changer = 4; // Third state in the Q table (Blue base)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "RFPE && BFPP OR RFPP && BFPE" << endl;
						states = searching;
					}
					else if (red_flag_picked_enemy && !blue_flag_picked_player)
					{
						for_health = false;
						scene_changer = 4; // Third state in the Q table (Red Flag)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "RFPE && !BFPP" << endl;
						states = searching;
					}
					else if (!red_flag_picked_enemy && blue_flag_picked_player)
					{
						scene_changer = 3; // Third state in the Q table (Red Flag)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "!RFPE && BFPP" << endl;
						states = searching;
					}
					else if (red_flag_picked_player && !blue_flag_picked_enemy)
					{
						scene_changer = 3; // Third state in the Q table (Red Flag)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "RFPP && !BFPE" << endl;
						states = searching;
					}
					else if (!red_flag_picked_player && blue_flag_picked_enemy)
					{
						for_health = false;
						scene_changer = 4; // Third state in the Q table (Red Flag)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "!RFPP && BFPE" << endl;
						states = searching;
					}
					else if (red_flag_picked_player && blue_flag_picked_player)
					{
						scene_changer = 3; // Third state in the Q table (Red Flag)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "!RFPP && BFPE" << endl;
						states = searching;
					}
					else if (red_flag_picked_enemy && blue_flag_picked_enemy)
					{
						for_health = false;
						scene_changer = 4; // Third state in the Q table (Red Flag)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "!RFPP && BFPE" << endl;
						states = searching;
					}
					else if ((!red_flag_picked_player && !blue_flag_picked_player) || (!red_flag_picked_enemy && !blue_flag_picked_player))
					{
						scene_changer = 3; // Third state in the Q table (Red Flag)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "!RFPP && !BFPP OR !RFPE && BFPP" << endl;
						states = searching;
					}
				}
				else if (!red_flag_at_base && blue_flag_at_base)
				{
					if (red_flag_picked_enemy)
					{
						for_health = false;
						scene_changer = 4; // Fifth state in the Q table (Blue Base)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << "RFPE" << endl;
						states = searching;
					}
					else if (!red_flag_picked_enemy || red_flag_picked_player || !red_flag_picked_enemy)
					{
						scene_changer = 1; // Second state in the Q table (PLayer)
						ql.test(scene_changer);
						path_finder->cleaPathToGoal();
						is_at_goal = false;
						stop_enemy();
						path_finder->iniStartGoal = false;
						path_finder->foundGoal = false;
						cout << """RFPE OR !RFPE OR RFPP" << endl;
						states = searching;
					}
				}
			}
			//if (!blue_flag_at_base || blue_flag_picked_player)
			//{
			//	scene_changer = 3; // Fifth state in the Q table (Blue Base Score)
			//	ql->test(scene_changer);
			//	path_finder->cleaPathToGoal();
			//	is_at_goal = true;
			//	path_finder->iniStartGoal = false;
			//	path_finder->foundGoal = false;
			//	cout << "CurrentState in Q:  " << ql->current_state << endl;
			//	states = searching;
			//}

			if (enemy_health == 0)
			{
				respawn.restart();
			}

			dist_length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));
			if (player_dead || (!player_in_range && !player_dead) || enemy_health < 50)
			{
				if (player_dead || (!player_in_range && !player_dead))
				{
					scene_changer_shoot = 2;
					qls.test(scene_changer_shoot);
					scene_changer = 1; // Second state in the Q table (Red Flag)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					path_finder->clearOpenList();
					path_finder->clearVisitedList();
					is_at_goal = true;
					stop_enemy();
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;
				}

				if (enemy_health < ENEMY_HEALTH_RANGE)
				{
					for_health = true;
					scene_changer = 4; // Fifth state in the Q table (PLayer)
					ql.test(scene_changer);
					path_finder->cleaPathToGoal();
					path_finder->clearOpenList();
					path_finder->clearVisitedList();
					is_at_goal = true;
					stop_enemy();
					path_finder->iniStartGoal = false;
					path_finder->foundGoal = false;
					states = searching;

				}
			}
		}
		break;
		}
	}
	else
	{
		stop_enemy();
		if (respawn.getElapsedTime().asSeconds() > RESPAWN_DELAY)
			{
				fire_bullet = false;
				reset_actor(body, angle_to_target(e_sprite_.getPosition(), target_pos) * (b2_pi / 180));
				scene_changer = 4; // Second state in the Q table (Red Flag)
				ql.test(scene_changer);
				path_finder->cleaPathToGoal();
				is_at_goal = false;
				path_finder->iniStartGoal = false;
				path_finder->foundGoal = false;
				states = searching;
			}
	}
}