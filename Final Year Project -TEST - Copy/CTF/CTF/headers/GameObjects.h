#pragma once

#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"


namespace KStudio
{
	class GameObjects
	{
	public:
		virtual void Init(b2World *world) {};
		virtual void Init(b2World *world, float posX, float posY, float shapeX, float shapeY, float angle) {};
		virtual void Init(b2World *world, float posX, float posY, float shapeX, float shapeY) {};
		virtual void Update() {};
		virtual void Update( bool playerScore, bool enemyScore, bool blue_flag_returned, bool red_flag_returned, bool blue_flag_player, 
		bool blue_flag_enemy, bool red_flag_player, bool red_flag_enemy, b2Body* player_body, b2Body* enemy_body, bool has_player_died, bool has_enemy_died) {};
		virtual void Draw() {};

		std::vector<sf::Sprite> sprites;
		std::vector<b2Body*> borders_bodies;
		bool blue_flag_picked_player = false;
		bool red_flag_picked_player = false;
		bool blue_flag_picked_enemy = false;
		bool red_flag_picked_enemy = false;

		b2Body* bush_body;
		b2Body* border_vert;
		b2Body* border_hori;
		sf::Sprite bush_sprite_;
		sf::Sprite bush_sprite_rotated_;
		sf::Sprite red_ped_;
		sf::Sprite blue_ped_;
		sf::Sprite red_flag_;
		sf::Sprite blue_flag_;
		//std::vector<sf::Sprite> sprites;
		std::vector<sf::Vector2f> spritesPos;
		b2Vec2 previous_pos_red_flag; //previous red flag postion
		b2Vec2 new_pos_red_flag; //new red flag 
		b2Vec2 previous_pos_blue_flag; //previous red flag postion
		b2Vec2 new_pos_blue_flag; //new red flag position

		virtual sf::Sprite &get_red_flag_sprite() //return red flag sprite
		{
			return  sprites[14];
		}

		virtual sf::Sprite &get_blue_flag_sprtie() //returns blue flag sprite
		{
			return  sprites[15];
		}

		virtual sf::Sprite &get_red_base_pos() // return red base sprite
		{
			return  sprites[12];
		}
		
		virtual sf::Sprite &get_blue_base_pos() // return blue base sprite
		{
			return sprites[13];
		}

		virtual sf::Sprite &get_vert_bush() // return blue base sprite
		{
			return sprites[0];
		}

		virtual b2Body* &get_bush_body() // return blue base sprite
		{
			b2Body* &body = bush_body;
			return body;
		}

		virtual bool get_blue_flag_enemy()
		{
			return blue_flag_picked_enemy;
		}

		virtual bool get_red_flag_enemy()
		{
			return  red_flag_picked_enemy;
		}
		virtual bool get_blue_flag_player()
		{
			return blue_flag_picked_player;
		}

		virtual bool get_red_flag_player()
		{
			return  red_flag_picked_player;
		}


	};
}

