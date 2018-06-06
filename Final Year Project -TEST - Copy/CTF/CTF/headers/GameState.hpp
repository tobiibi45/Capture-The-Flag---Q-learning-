#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Actors.hpp"
#include "GameObjects.h"
#include <vector>
#include "ENGINEDEFINITIONS.hpp"
#include <set>
#include "Contact.h"
#include "Bullet.h"
#include <Box2D/Box2D.h>
#include "raycast.h"

namespace KStudio
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;
		void CheckPlayerHasWon();
		void HandleScoresAndTime();
		void drawMessages();
		void removeBodiesA();
		void removeBodiesB();
		void shoot();
		void playershoot();
		b2Body* p_body;
		
		b2Vec2 p1, p2, collision, normal;
		float fraction;
		b2Fixture* fixture;
		raycast callback;
		
		b2Body* BodyIterator;
		bodyUserData* myStruct;
		b2Fixture* fix;
		sf::Sprite _player1;

	private:
		bool debug;
		bool the_player_shoot;
		int player_bullet_no_;
		int enemy_bullet_no_;
		bool blue_flag_returned;
		bool red_flag_returned;
		bool has_player_died;
		bool has_enemy_died;
		bool draw_path_finder_debug;
		int minute = 0;
		int p_time;
		bool full_health;

		Contact cl;
		b2World* myWorld;
		GameDataRef _data;
		sf::Clock player_base_timer;
		sf::Clock enemy_base_timer;
		sf::Clock _clock;
		sf::Clock _gameClock;
		sf::String _SgameClock;
		sf::Text _TgameClock;
		sf::String _SgameClockMinute;
		sf::Text _TgameClockMinute;

		int next_fire_time_enemy;
		int next_fire_time_player;

		sf::Sprite _background;
		sf::Sprite _pause;
		sf::Sprite _win;
		sf::Sprite _lose;
		sf::Sprite _draw;
		sf::Sprite _wall;
		sf::Sprite _flag_captured;
		sf::Sprite _flag_captured_enemy;

		std::vector<Actors*> v_actors;
		std::vector<GameObjects*> v_game_objects;
		std::set<b2Body*> ActorBodyToRemove;
		std::vector<Bullet*> v_bullets;

		int gameState;
		int playerCapture;
		bool playerWins;
		int enemyCapture;
		bool e_hit;

		bool game_over;
		bool restart_clock;

		float player_health;
		float enemy_health;
		float bullet_damage;
		float health_regen;
		int bullet_regen;

		sf::String _playerCaptureNo;
		sf::String _enemyCaptureNo;
		sf::Text _playerCaptureNoText;
		sf::Text _enemyCaptureNoText;

		sf::String player_bullet_no_string;
		sf::Text player_bullet_no_text;



	};
}
