#pragma once

#include "Box2D\Box2D.h"
#include "GameObjects.h"
#include "Game.hpp"
#include <SFML/Graphics.hpp>


namespace KStudio
{
	class StaticObjects : public GameObjects
	{
	public:
		StaticObjects(GameDataRef _data);
		void Init(b2World* world) override;
		void Update() override;
		void Update( bool playerScore, bool enemyScore, bool blue_flag_returned, bool red_flag_returned, bool blue_flag_player,
			bool blue_flag_enemy, bool red_flag_player, bool red_flag_enemy, b2Body* player_body, b2Body* enemy_body, bool has_player_died, bool has_enemy_died) override;
		void Draw() override;

	private:
		GameDataRef _data;
		b2Body* blue_flag_body;
		b2Body* red_flag_body;
		


	};
}

