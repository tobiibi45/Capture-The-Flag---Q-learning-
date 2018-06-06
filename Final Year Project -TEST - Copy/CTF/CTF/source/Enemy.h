#pragma once
#include "Actors.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "qlearning.h"
#include "qlearningShooting.h"

namespace KStudio
{
	class Enemy : public Actors
	{
	public:

		enum states {begin, searching, found_red_flag, found_blue_flag, found_player, found_base, found_base_health};

		qlearning ql;
		qlearningShooting qls;
		Enemy(GameDataRef data);
		void Init(b2World* world) override;
		void Update(b2Body* body, float dt, float actorhealth) override {};
		void Update(b2Body* body, float dt, sf::Vector2f target_pos, float actorhealth, bool enemy_score) override;
		void keyInput(sf::Event event) override {};
		void keyRealease(sf::Event event) override {};
		void Draw() override;
		sf::Vector2f getPosition() override;
		b2Body* &getBody()override;
		b2Fixture* &getFixture()override;
		sf::Sprite &getSprite() override;
		void enemy_AI(sf::Vector2f player_pos, sf::Vector2f red_flag_pos, sf::Vector2f blue_flag_pos, sf::Vector2f base_pos, b2Body* body, int enemy_bullet, float enemy_health,
			bool red_flag_picked_player, bool blue_flag_picked_player, bool red_flag_picked_enemy, bool blue_flag_picked_enemy, float player_health, bool player_in_range,
			bool red_flag_in_range, bool blue_flag_in_range, bool player_score, bool enemy_score, bool enemy_hit, bool player_dead, bool red_flag_at_base, bool blue_flag_at_base, bool object_found, bool full_health) override;
		void move_enemy(float direction, bool player_dead) override;
		void reset_actor(b2Body* body, float angle) override;
		void stop_enemy() override;
		void Draw_Pathfinder(sf::Sprite &sprite) override;

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
		float acceleration;
		bool is_at_goal;
		bool reset;
		bool reset1;
		bool player_was_found;

		sf::Vector2f dist_to_target_p;
		sf::Vector2f dist_to_target_t;
		float the_angle;
		float the_path_angle;
		sf::Vector2f dist;
		float dist_length;
		bool for_health;

		float enemy_radar_radius;
		int timer;
		sf::Clock searc_timer;

		bool b_at_base_;
		float the_actorhealth;

		sf::Vector2f target_pos;
		GameDataRef _data;
		states states;
		sf::Sprite e_sprite_;
		b2Body* e_body_;
		b2Fixture* fixture;

		int scene_changer;
		int scene_changer_shoot;


	};
}
