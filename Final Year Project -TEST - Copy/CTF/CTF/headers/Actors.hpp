#pragma once

#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"
#include "PathFinder.h"
#include "qlearning.h"


namespace KStudio
{
	class Actors
	{
	public:
		PathFinder* path_finder;
		virtual ~Actors() = default;
		virtual void Init(b2World* world) = 0;
		virtual void Update(b2Body* body, float dt, float actorhealth) = 0;
		virtual void Update(b2Body* body, float dt, sf::Vector2f target_pos, float actorhealth, bool enemy_score) {};
		virtual void keyInput(sf::Event event) = 0;
		virtual void keyRealease(sf::Event event) = 0;
		virtual void Draw() = 0;
	    virtual sf::Vector2f getPosition() = 0;
		virtual sf::Sprite &getSprite() =0;
		virtual b2Body* &getBody() = 0;
		virtual b2Fixture* &getFixture() = 0;
		sf::Sprite healthbar;
		sf::Sprite healthbar_backg;
		float actors_max_health = 100.f;
		bool fire_bullet = false;;
		virtual void enemy_AI(sf::Vector2f player_pos, sf::Vector2f red_flag_pos, sf::Vector2f blue_flag_pos, sf::Vector2f base_pos, b2Body* body, int enemy_bullet,
			float enemy_health, bool red_flag_picked_player, bool blue_flag_picked_player, bool red_flag_picked_enemy, bool blue_flag_picked_enemy, float player_health, bool player_in_range,
			bool red_flag_in_range, bool blue_flag_in_range, bool player_score, bool enemy_score, bool enemy_hit, bool player_dead, bool red_flag_at_base, bool blue_flag_at_base, bool object_found, bool full_health) {};
		virtual void reset_actor(b2Body* body, float angle) = 0;
		virtual void move_enemy(float direction, bool player_dead) {};
		virtual void stop_enemy() {};
		virtual void Draw_Pathfinder(sf::Sprite &sprite) {};
		sf::Clock current_time;
		int next_fire_time;
		b2Vec2 actor_spawn;
		sf::Clock respawn;
		float radius;
		virtual float get_radius()
		{
			return radius;
		}

		virtual float rotationAngle(sf::Vector2f SpritePos, sf::Vector2i mousePos)
		{
			auto a = SpritePos.x - mousePos.x;
			auto b = SpritePos.y - mousePos.y;
			const auto rotation = ((atan2(b, a)) * 180 / b2_pi);
			return (rotation + 180);
		}

		virtual float angle_to_target(sf::Vector2f SpritePos, sf::Vector2f targetPos)
		{
			auto a = SpritePos.x - targetPos.x;
			auto b = SpritePos.y - targetPos.y;
			const auto rotation = ((atan2(b, a)) * 180 / b2_pi);
			return (rotation);
		}

		virtual float angle_path_finder(sf::Vector2f angle)
		{
			const auto rotation = ((atan2(angle.y , angle.x)) * 180 / b2_pi);
			return (rotation);
		}

		virtual float angle_path_finder_2(sf::Vector2f angle)
		{
			const auto rotation = ((atan2(angle.x, angle.y)) * 180 / b2_pi);
			return (rotation);
		}

	

	};
}
