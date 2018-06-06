#pragma once
#include <Box2D/Box2D.h>
#include <vector>

namespace KStudio
{
	class Contact : public b2ContactListener
	{
	public:

		std::vector<b2Body*> bodiesToRemoveA;  //Vector that stores the bodies to remove
		std::vector<b2Body*> bodiesToRemoveB;  //Vector that stores the bodies to remove
		bool remove_player_bullet = false; // boolean to know player bullet can be deleted
		bool remove_enemy_bullet = false; // boolean to know enemy bullet can be deleted
		bool player_hit = false; //boolean to know ehn player is dead
		bool enemy_hit = false;
		bool enemy_was_shot = false;
		bool red_ped_hit_player = false;
		bool blue_ped_hit_enemy = false;
		bool player_score = false;
		bool enemy_score = false;
		bool player_can_shoot_ = true;
		bool player_found = false;
		bool enemy_in_base = false;
		bool player_in_base = false;
		bool player_has_blue_flag = false;
		bool player_has_red_flag = false;
		bool enemy_has_blue_flag = false;
		bool enemy_has_red_flag = false;
		bool blue_flag_in_range = false;
		bool red_flag_in_range = false;
		bool bush_in_range = false;
		bool wall_in_range = false;
		bool red_flag_at_base = true;
		bool blue_flag_at_base = true;


		//TODO REMOVE CONTACT WITH RADAR WHEN ENEMY HAS FLAGS

		void BeginContact(b2Contact* contact) override
		{
			auto fixtureUserDataA = contact->GetFixtureA()->GetUserData();
			auto fixtureUserDataB = contact->GetFixtureB()->GetUserData();

			////////////////Player and Enemy Bullet contacts //////////////////////////
			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 9)) 
			{
				bodiesToRemoveB.push_back(contact->GetFixtureB()->GetBody());
				player_hit = true;
				remove_enemy_bullet = true;

			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 9))
			{
				bodiesToRemoveA.push_back(contact->GetFixtureA()->GetBody());
				player_hit = true;
				remove_enemy_bullet = true;

			}

			////////////////Player and Enemy Radar sensor //////////////////////////
			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 12))
			{
				player_found = true;


			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 12))
			{
				player_found = true;


			}

			////////////////////Player Bullets and Bushes/Borders contacts/////////////

			if ((int)fixtureUserDataA == 10 && ((int)fixtureUserDataB == 2))
			{
				bodiesToRemoveA.push_back(contact->GetFixtureA()->GetBody());
				remove_player_bullet = true;
			}

			else if ((int)fixtureUserDataB == 10 && ((int)fixtureUserDataA == 2))
			{
				bodiesToRemoveB.push_back(contact->GetFixtureB()->GetBody());
				remove_player_bullet = true;
			}

			//////////////////// PLAYER AND RED PED /////////////////////

			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 3))
			{
				red_ped_hit_player = true;

			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 3))
			{
				red_ped_hit_player = true;

			}

			//////////////////// ENEMY AND BLUE PED ////////////////////////

			if ((int)fixtureUserDataA == 11 && ((int)fixtureUserDataB == 4))
			{
				blue_ped_hit_enemy = true;

			}

			else if ((int)fixtureUserDataB == 11 && ((int)fixtureUserDataA == 4))
			{
				blue_ped_hit_enemy = true;

			}

			//////////////////// Enemy Bullet AND Bush/Borders /////////////////////

			if ((int)fixtureUserDataA == 9 && ((int)fixtureUserDataB == 2))
			{
				bodiesToRemoveA.push_back(contact->GetFixtureA()->GetBody());
				remove_enemy_bullet = true;
			}

			else if ((int)fixtureUserDataB == 9 && ((int)fixtureUserDataA == 2))
			{
				bodiesToRemoveB.push_back(contact->GetFixtureB()->GetBody());
				remove_enemy_bullet = true;
			}

			//////////////////// Player Bullet AND Enemy /////////////////////

			if ((int)fixtureUserDataA == 10 && ((int)fixtureUserDataB == 11))
			{
				bodiesToRemoveA.push_back(contact->GetFixtureA()->GetBody());
				enemy_hit = true;
				enemy_was_shot = true;
				remove_player_bullet = true;

			}

			else if ((int)fixtureUserDataB == 10 && ((int)fixtureUserDataA == 11))
			{
				bodiesToRemoveB.push_back(contact->GetFixtureB()->GetBody());
				enemy_hit = true;
				enemy_was_shot = true;
				remove_player_bullet = true;
		
			}

			//////////////////// Enemy and Enemy base area collisions /////////////////////

			if ((int)fixtureUserDataA == 11 && ((int)fixtureUserDataB == 6))
			{
				enemy_in_base = true;
			}

			else if ((int)fixtureUserDataB == 11 && ((int)fixtureUserDataA == 6))
			{
				enemy_in_base = true;
			}

			//////////////////// Player and Player base area collisions /////////////////////

			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 5))
			{
				player_in_base = true;
			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 5))
			{
				player_in_base = true;
			}

			//////////////////// Player and BLUE FLAG /////////////////////

			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 18))
			{
				player_has_blue_flag = true;
			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 18))
			{
				player_has_blue_flag = true;
				
			}

			//////////////////// Player and Red FLAG /////////////////////

			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 17))
			{
				player_has_red_flag = true;
			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 17))
			{
				player_has_red_flag = true;
			}

			//////////////////// ENEMY and RED FLAG /////////////////////

			if ((int)fixtureUserDataA == 11 && ((int)fixtureUserDataB == 17))
			{
				enemy_has_red_flag = true;
			}

			else if ((int)fixtureUserDataB == 11 && ((int)fixtureUserDataA == 17))
			{
				enemy_has_red_flag = true;
			}

			//////////////////// ENEMY and BLUE FLAG /////////////////////

			if ((int)fixtureUserDataA == 11 && ((int)fixtureUserDataB == 18))
			{
				enemy_has_blue_flag = true;
			}

			else if ((int)fixtureUserDataB == 11 && ((int)fixtureUserDataA == 18))
			{
				enemy_has_blue_flag = true;
			}

			//////////////////// RED FLAG AND ENEMY RADAR /////////////////////

			if ((int)fixtureUserDataA == 17 && ((int)fixtureUserDataB == 12))
			{
				red_flag_in_range = true;
			}

			else if ((int)fixtureUserDataB == 17 && ((int)fixtureUserDataA == 12))
			{
				red_flag_in_range = true;
			}

			//////////////////// BLUE FLAG AND ENEMY RADAR /////////////////////

			if ((int)fixtureUserDataA == 18 && ((int)fixtureUserDataB == 12))
			{
				blue_flag_in_range = true;
			}

			else if ((int)fixtureUserDataB == 18 && ((int)fixtureUserDataA == 12))
			{
				blue_flag_in_range = true;
			}

			//////////////////// BUSHES AND ENEMY RADAR /////////////////////

			if ((int)fixtureUserDataA == 2 && ((int)fixtureUserDataB == 12))
			{
				bush_in_range = true;
			}

			else if ((int)fixtureUserDataB == 2 && ((int)fixtureUserDataA == 12))
			{
				bush_in_range = true;
			}

			//////////////////// Walls/Bushes AND ENEMY Object finder /////////////////////

			if ((int)fixtureUserDataA == 2 && ((int)fixtureUserDataB == 21))
			{
				wall_in_range = true;
			}

			else if ((int)fixtureUserDataB == 2 && ((int)fixtureUserDataA == 21))
			{
				wall_in_range = true;
			}

			//////////////////// RED FLAG AND RED PED /////////////////////

			if ((int)fixtureUserDataA == 17 && ((int)fixtureUserDataB == 3))
			{
					red_flag_at_base = true;
			}

			else if ((int)fixtureUserDataB == 17 && ((int)fixtureUserDataA == 3))
			{
					red_flag_at_base = true;
			}

			//////////////////// BLUE FLAG AND BLUE PED /////////////////////

			if ((int)fixtureUserDataA == 18 && ((int)fixtureUserDataB == 4))
			{
					blue_flag_at_base = true;
				
			}

			else if ((int)fixtureUserDataB == 18 && ((int)fixtureUserDataA == 4))
			{
				blue_flag_at_base = true;
			}
		}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		void EndContact(b2Contact* contact) override
		{
			auto fixtureUserDataA = contact->GetFixtureA()->GetUserData();
			auto fixtureUserDataB = contact->GetFixtureB()->GetUserData();

			////////////////Player and Enemy Bullet contacts //////////////////////////
			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 9))
			{
				remove_enemy_bullet = false;

			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 9))
			{
				remove_enemy_bullet = false;

			}

			////////////////Player and Enemy Radar sensor //////////////////////////
			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 12))
			{
				player_found = false;

			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 12))
			{
				player_found = false;

			}

			////////////////////PLayer Bullets and Bushes/Borders contacts////////////
			if ((int)fixtureUserDataA == 10 && ((int)fixtureUserDataB == 2))
			{
				remove_player_bullet = false;
				player_can_shoot_ = true;
			}

			else if ((int)fixtureUserDataB == 10 && ((int)fixtureUserDataA == 2))
			{
				remove_player_bullet = false;
				player_can_shoot_ = true;
			}

			//////////////////// PLAYER AND RED PED /////////////////////

			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 3))
			{
				red_ped_hit_player = false;
			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 3))
			{
				red_ped_hit_player = false;
			}

			//////////////////// ENEMY AND BLUE PED ////////////////////////

			if ((int)fixtureUserDataA == 11 && ((int)fixtureUserDataB == 4))
			{
				blue_ped_hit_enemy = false;
			}

			else if ((int)fixtureUserDataB == 11 && ((int)fixtureUserDataA == 4))
			{
				blue_ped_hit_enemy = false;
			}

			//////////////////// Enemy Bullet AND Bush /////////////////////

			if ((int)fixtureUserDataA == 9 && ((int)fixtureUserDataB == 2))
			{
				remove_enemy_bullet = false;
			}

			else if ((int)fixtureUserDataB == 9 && ((int)fixtureUserDataA == 2))
			{
				remove_enemy_bullet = false;
			}

			//////////////////// Player Bullet AND Enemy /////////////////////

			if ((int)fixtureUserDataA == 10 && ((int)fixtureUserDataB == 11))
			{
				remove_player_bullet = false;
				enemy_was_shot = false; 
				player_can_shoot_ = true;
			}

			else if ((int)fixtureUserDataB == 10 && ((int)fixtureUserDataA == 11))
			{
				remove_player_bullet = false;
				enemy_was_shot = false;
				player_can_shoot_ = true;
			}

			//////////////////// Enemy and Enemy base area collisions /////////////////////

			if ((int)fixtureUserDataA == 11 && ((int)fixtureUserDataB == 6))
			{
				enemy_in_base = false;
			}

			else if ((int)fixtureUserDataB == 11 && ((int)fixtureUserDataA == 6))
			{
				enemy_in_base = false;
			}

			//////////////////// Player and Player base area collisions /////////////////////

			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 5))
			{
				player_in_base = false;
			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 5))
			{
				player_in_base = false;
			}

			//////////////////// Player and BLUE FLAG /////////////////////

			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 18))
			{
				player_has_blue_flag = false;
			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 18))
			{
				player_has_blue_flag = false;
			}

			//////////////////// Player and Red FLAG /////////////////////

			if ((int)fixtureUserDataA == 1 && ((int)fixtureUserDataB == 17))
			{
				player_has_red_flag = false;
			}

			else if ((int)fixtureUserDataB == 1 && ((int)fixtureUserDataA == 17))
			{
				player_has_red_flag = false;
			}

			//////////////////// ENEMY and RED FLAG /////////////////////

			if ((int)fixtureUserDataA == 11 && ((int)fixtureUserDataB == 17))
			{
				enemy_has_red_flag = false;
			}

			else if ((int)fixtureUserDataB == 11 && ((int)fixtureUserDataA == 17))
			{
				enemy_has_red_flag = false;
			}

			//////////////////// ENEMY and BLUE FLAG /////////////////////

			if ((int)fixtureUserDataA == 11 && ((int)fixtureUserDataB == 18))
			{
				enemy_has_blue_flag = false;
			}

			else if ((int)fixtureUserDataB == 11 && ((int)fixtureUserDataA == 18))
			{
				enemy_has_blue_flag = false;
			}

			//////////////////// RED FLAG AND ENEMY RADAR /////////////////////

			if ((int)fixtureUserDataA == 17 && ((int)fixtureUserDataB == 12))
			{
				red_flag_in_range = false;
			}

			else if ((int)fixtureUserDataB == 17 && ((int)fixtureUserDataA == 12))
			{
				red_flag_in_range = false;
			}

			//////////////////// BLUE FLAG AND ENEMY RADAR /////////////////////

			if ((int)fixtureUserDataA == 18 && ((int)fixtureUserDataB == 12))
			{
				blue_flag_in_range = false;
			}

			else if ((int)fixtureUserDataB == 18 && ((int)fixtureUserDataA == 12))
			{
				blue_flag_in_range = false;
			}

			//////////////////// BUSHES AND ENEMY RADAR /////////////////////

			if ((int)fixtureUserDataA == 2 && ((int)fixtureUserDataB == 12))
			{
				bush_in_range = false;
			}

			else if ((int)fixtureUserDataB == 2 && ((int)fixtureUserDataA == 12))
			{
				bush_in_range = false;
			}

			//////////////////// Walls/Bushes AND ENEMY Object finder /////////////////////

			if ((int)fixtureUserDataA == 2 && ((int)fixtureUserDataB == 21))
			{
				wall_in_range = false;
			}

			else if ((int)fixtureUserDataB == 2 && ((int)fixtureUserDataA == 21))
			{
				wall_in_range = false;
			}

			//////////////////// RED FLAG AND RED PED /////////////////////

			if ((int)fixtureUserDataA == 17 && ((int)fixtureUserDataB == 3))
			{
				red_flag_at_base = false;
			}

			else if ((int)fixtureUserDataB == 17 && ((int)fixtureUserDataA == 3))
			{
				red_flag_at_base = false;
			}

			//////////////////// BLUE FLAG AND BLUE PED /////////////////////

			if ((int)fixtureUserDataA == 18 && ((int)fixtureUserDataB == 4))
			{
				blue_flag_at_base = false;
			}

			else if ((int)fixtureUserDataB == 18 && ((int)fixtureUserDataA == 4))
			{
				blue_flag_at_base = false;
			}
		}

		std::vector<b2Body*> &getBodyToRemoveA() { return bodiesToRemoveA; }
		std::vector<b2Body*> &getBodyToRemoveB() { return bodiesToRemoveB; }

	};
}