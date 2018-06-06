
#include "GameState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "ENGINEDEFINITIONS.hpp"
#include <iostream>
#include "Player.h"
#include "Borders.h"
#include "StaticObjects.h"
#include "Bullet.h"
#include "Enemy.h"


namespace KStudio
{

	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::Init()
	{
		game_over = false;

		this->_data->assets.GetMusic("menu").stop();
		this->_data->assets.GetMusic("gameplay").play();
		this->_data->assets.GetMusic("gameplay").setLoop(true);

		debug = false;
		e_hit = false;
		restart_clock = false;

		blue_flag_returned = false;
		red_flag_returned = false;
		next_fire_time_enemy = 0;
		next_fire_time_player = 0;
		draw_path_finder_debug = true;
		the_player_shoot = true;
		full_health = true;

		has_player_died = false;
		has_enemy_died = false;

		player_bullet_no_ = 50;
		enemy_bullet_no_ = 50;

		player_health = 100.f;
		enemy_health = 100.f;
		bullet_damage = 20.f;
		health_regen = 0.1f;
		bullet_regen = 2;

		const b2Vec2 gravity(0.f, 0.f);
		myWorld = new b2World(gravity);
		myWorld->SetContactListener(&cl); //Sets the contact listener
		myWorld->SetDebugDraw(&_data->fooDrawInstance);

		this->_gameClock.restart();
		player_base_timer.restart();
		enemy_base_timer.restart();
		gameState = STATE_PLAYING;
		playerCapture = 0;
		enemyCapture = 0;
		playerWins = false;
		this->_playerCaptureNo = std::to_string(playerCapture);
		this->_enemyCaptureNo = std::to_string(enemyCapture);
		this->player_bullet_no_string = std::to_string(player_bullet_no_);

		///////////////////////////Load Textures/////////////////////////////////
		this->_data->assets.LoadFont("Score Font", SCORE_FONT);
		this->_data->assets.LoadTexture("Game State Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("flagCap", FLAGS_CAPTURED_PLAYER);
		this->_data->assets.LoadTexture("flagCapE", FLAGS_CAPTURED_ENEMY);

		_data->assets.LoadTexture("BTexture", MIDDLE_BUSH_VERTICAL);
		_data->assets.LoadTexture("BRTexture", MIDDLE_BUSH_HORIZONTAL);
		_data->assets.LoadTexture("redPed", PEDESTAL_RED);
		_data->assets.LoadTexture("bluePed", PEDESTAL_BLUE);
		_data->assets.LoadTexture("PTexture", PLAYER1_FILEPATH);
		_data->assets.LoadTexture("EnemyDoctor", ENEMY_FILEPATH);
		_data->assets.LoadTexture("redbullet", RED_BULLET);
		_data->assets.LoadTexture("bluebullet", BLUE_BULLET);
		_data->assets.LoadTexture("redFlag", RED_FLAG);
		_data->assets.LoadTexture("blueFlag", BLUE_FLAG);
		_data->assets.LoadTexture("healthbar", HEALTHBAR);
		_data->assets.LoadTexture("healthbar_backg", HEALTHBAR_BACKG);

		this->_data->assets.LoadTexture("Win", WINNER_MESSAGE_FILEPATH);
		this->_data->assets.LoadTexture("Lose", LOSER_MESSAGE_FILEPATH);
		this->_data->assets.LoadTexture("Draw", DRAW_MESSAGE_FILEPATH);

		///////////////////////////////Load Sounds//////////////////////////////////////
		this->_data->assets.LoadSound("bullet", MUSIC_EFFECT_BULLET);
		this->_data->assets.LoadSound("death", MUSIC_EFFECT_DEATH);
		this->_data->assets.LoadMusic("countdown", MUSIC_EFFECT_TIMER);
		this->_data->bullet.setBuffer(this->_data->assets.GetSound("bullet"));
		this->_data->death.setBuffer(this->_data->assets.GetSound("death"));

		v_game_objects.push_back(new Borders(_data)); //GameObject 0
		v_game_objects.push_back(new StaticObjects(_data));  //GameObject 1
		v_bullets.push_back(new Bullet(_data)); //Bullet 0 PLayer
		v_bullets.push_back(new Bullet(_data)); //Bullet 1 Enemy

		for (auto & v_game_object : v_game_objects)
		{
			v_game_object->Init(myWorld);
		}

		v_actors.push_back(new Player(_data));
		v_actors.push_back(new Enemy(_data));

		for (auto & v_actor : v_actors)
		{
			v_actor->Init(myWorld);
		}

		this->_win.setTexture(this->_data->assets.GetTexture("Win"));
		this->_lose.setTexture(this->_data->assets.GetTexture("Lose"));
		this->_draw.setTexture(this->_data->assets.GetTexture("Draw"));
		this->_win.setPosition((SCREEN_WIDTH / 2) - (this->_win.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_win.getGlobalBounds().height / 2));
		this->_lose.setPosition((SCREEN_WIDTH / 2) - (this->_lose.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_lose.getGlobalBounds().height / 2));
		this->_draw.setPosition((SCREEN_WIDTH / 2) - (this->_draw.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_draw.getGlobalBounds().height / 2));

		this->_background.setTexture(this->_data->assets.GetTexture("Game State Background"));
		this->_pause.setTexture(this->_data->assets.GetTexture("Pause Button"));
		this->_pause.setPosition((this->_pause.getGlobalBounds().width * 1.4), this->_pause.getGlobalBounds().height * 0.8);

		this->_flag_captured.setTexture(this->_data->assets.GetTexture("flagCap"));
		this->_flag_captured.setPosition((SCREEN_WIDTH / 2) - (this->_flag_captured.getGlobalBounds().width) * 10.6f, (SCREEN_HEIGHT / 2) - this->_flag_captured.getGlobalBounds().height * 0.55);

		this->_flag_captured_enemy.setTexture(this->_data->assets.GetTexture("flagCapE"));
		this->_flag_captured_enemy.setPosition((SCREEN_WIDTH / 2) - (this->_flag_captured_enemy.getGlobalBounds().width * -9.6f), (SCREEN_HEIGHT / 2) - this->_flag_captured_enemy.getGlobalBounds().height * 0.55);

		this->_playerCaptureNoText.setFont(this->_data->assets.GetFont("Score Font"));
		this->_enemyCaptureNoText.setFont(this->_data->assets.GetFont("Score Font"));
		this->player_bullet_no_text.setFont(this->_data->assets.GetFont("Score Font"));

		this->_playerCaptureNoText.setString(_playerCaptureNo);
		this->_enemyCaptureNoText.setString(_enemyCaptureNo);
		this->player_bullet_no_text.setString("Bullets:  " + this->player_bullet_no_string);

		this->_playerCaptureNoText.setStyle(sf::Text::Bold);
		this->_playerCaptureNoText.setFillColor(sf::Color::Blue);
		this->_playerCaptureNoText.setPosition((this->_pause.getGlobalBounds().width * 5), (SCREEN_HEIGHT / 2) - _pause.getGlobalBounds().height * 0.9);
		this->_enemyCaptureNoText.setStyle(sf::Text::Bold);
		this->_enemyCaptureNoText.setFillColor(sf::Color::Red);
		this->_enemyCaptureNoText.setPosition((this->_pause.getGlobalBounds().width * 68), (SCREEN_HEIGHT / 2) - _pause.getGlobalBounds().height * 0.9);
		this->player_bullet_no_text.setStyle(sf::Text::Bold);
		this->player_bullet_no_text.setFillColor(sf::Color::White);
		this->player_bullet_no_text.setPosition((this->_pause.getGlobalBounds().width * 7.f), _pause.getGlobalBounds().height * 0.5);

		this->_SgameClockMinute = std::to_string(minute);
		this->_TgameClockMinute.setString(this->_SgameClockMinute + " :");
		this->_TgameClockMinute.setFont(this->_data->assets.GetFont("Score Font"));
		this->_TgameClockMinute.setStyle(sf::Text::Bold);
		this->_TgameClockMinute.setFillColor(sf::Color::White);
		this->_TgameClockMinute.setPosition((this->_pause.getGlobalBounds().width * 19.f), _pause.getGlobalBounds().height * 0.5);

		this->_SgameClock = std::to_string(this->_clock.getElapsedTime().asSeconds());
		this->_TgameClock.setString("Time:      " + this->_SgameClock);
		this->_TgameClock.setFont(this->_data->assets.GetFont("Score Font"));
		this->_TgameClock.setStyle(sf::Text::Bold);
		this->_TgameClock.setFillColor(sf::Color::White);
		this->_TgameClock.setPosition((this->_pause.getGlobalBounds().width * 15.f), _pause.getGlobalBounds().height * 0.5); //For some reason changing the position value, messes with all positions in the game!!!!
	}

	void GameState::HandleInput()
	{
			sf::Event event;

			while (this->_data->window.pollEvent(event))
			{
				if (sf::Event::Closed == event.type)
				{
					this->_data->window.close();
				}
				if (event.type == sf::Event::KeyPressed)
				{
					/** If Right is pressed */
					if (event.key.code == sf::Keyboard::Escape)
					{
						this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
					}
				}

				if (!game_over)
				{

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (!cl.remove_player_bullet && player_bullet_no_ > 0)
						{
							if (cl.player_can_shoot_)
							{
								this->_data->bullet.play();
								playershoot();
								player_bullet_no_ = player_bullet_no_ - 1;
							}
							cl.player_can_shoot_ = false;
						}
					}

					if (this->_data->input.IsSpriteClicked(this->_pause, sf::Mouse::Left, this->_data->window))
					{
						this->_data->bullet.stop();
						this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
					}


					if (event.type == sf::Event::KeyPressed)
					{
						if (STATE_DRAW != gameState || STATE_LOSE != gameState || STATE_WON != gameState)
						{
							if (!cl.player_hit)
							{
								v_actors[0]->keyInput(event);
							}
							if (event.key.code == sf::Keyboard::P)
							{
								debug = true;
							}
							else if (event.key.code == sf::Keyboard::O)
							{
								debug = false;
							}
							else if (event.key.code == sf::Keyboard::LBracket)
							{
								draw_path_finder_debug = false;
							}
							else if (event.key.code == sf::Keyboard::RBracket)
							{
								draw_path_finder_debug = true;
							}

						}
					}

					if (event.type == sf::Event::KeyReleased)
					{
						if (STATE_DRAW != gameState || STATE_LOSE != gameState || STATE_WON != gameState)
						{
							if (!cl.player_hit)
							{
								v_actors[0]->keyRealease(event);
							}
						}
					}
				}
		}
	}

	void GameState::Update(float dt)
	{
		if (!restart_clock)
		{
			CheckPlayerHasWon();
		}
			myWorld->Step(dt, 8, 3); //Hnadles the world step updates
			HandleScoresAndTime();
			

			int BodyCount = 0;
			for (BodyIterator = myWorld->GetBodyList(); BodyIterator != nullptr; BodyIterator = BodyIterator->GetNext())
			{
				if (BodyIterator->GetUserData())
				{
					//!Gives each object a unique number to know which is which
					myStruct = static_cast<bodyUserData*>(BodyIterator->GetUserData());
					if (STATE_DRAW != gameState || STATE_LOSE != gameState || STATE_WON != gameState)
					{
						if (myStruct->type == 1)
						{
							this->player_bullet_no_string = std::to_string(player_bullet_no_);
							this->player_bullet_no_text.setString("Bullets:  " + this->player_bullet_no_string);

							if (!cl.player_hit)
							{
								v_actors[0]->Update(BodyIterator, dt, player_health);
								++BodyCount;
							}
						}

						else if (myStruct->type == 3)
						{
							//b->Update();
							for (auto & v_game_object : v_game_objects)
							{
								v_game_object->Update();
								v_game_object->Update(cl.player_score, cl.enemy_score, blue_flag_returned, red_flag_returned,
									cl.player_has_blue_flag, cl.enemy_has_blue_flag, cl.player_has_red_flag,
									cl.enemy_has_red_flag, v_actors[0]->getBody(), v_actors[1]->getBody(), has_player_died, has_enemy_died);
							}
						}
						else if (myStruct->type == 10)
						{
							v_bullets[1]->Update(BodyIterator, dt);

						}
						else if (myStruct->type == 15)
						{
							v_bullets[0]->Update(BodyIterator, dt);
							//v_bullets[1]->Update(BodyIterator, dt);

						}

						else if (myStruct->type == 11)
						{
							v_actors[1]->Update(BodyIterator, dt, v_actors[0]->getPosition(), enemy_health, red_flag_returned);
							v_actors[1]->enemy_AI(v_actors[0]->getSprite().getPosition(),
								_data->assets.getSprite("StaticObjectsSprites", 14).getPosition(), _data->assets.getSprite("StaticObjectsSprites", 15).getPosition(),
								_data->assets.getSprite("StaticObjectsSprites", 13).getPosition(), BodyIterator, enemy_bullet_no_, enemy_health,
								v_game_objects[1]->get_red_flag_player(), v_game_objects[1]->get_blue_flag_player(), v_game_objects[1]->get_red_flag_enemy(),
								v_game_objects[1]->get_blue_flag_enemy(), player_health, cl.player_found, cl.red_flag_in_range,
								cl.blue_flag_in_range, cl.player_score, cl.enemy_score, e_hit, has_player_died, cl.red_flag_at_base, cl.blue_flag_at_base, cl.wall_in_range, full_health);

							if (!cl.remove_enemy_bullet)
							{
								if (enemy_bullet_no_ > 0)
								{
									if (v_actors[1]->fire_bullet)
									{
										if (next_fire_time_enemy < _gameClock.getElapsedTime().asSeconds())
										{
											this->_data->bullet.play();
											shoot();
											enemy_bullet_no_ = enemy_bullet_no_ - 1;
											next_fire_time_enemy = _gameClock.getElapsedTime().asSeconds() + SHOOTING_DELAY;

										}
									}
								}
							}
							++BodyCount;
						}
					}
				}
			}

			if (cl.remove_enemy_bullet || cl.remove_player_bullet)
			{
				removeBodiesA();
				removeBodiesB();
			}


			if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
			{
				if (GAME_OVER_SHOW_TIME > this->_clock.getElapsedTime().asSeconds())
				{
					this->_data->machine.AddState(StateRef(new GameOverState(_data)), true);
				}
			}
	}


	void GameState::Draw(float dt)
	{
			this->_data->window.clear();

			this->_data->window.draw(this->_background);
			this->_data->window.draw(this->_pause);

			for (BodyIterator = myWorld->GetBodyList(); BodyIterator != nullptr; BodyIterator = BodyIterator->GetNext())
			{
				if (BodyIterator->GetUserData())
				{
					//!Gives each object a unique number to know which is which
					myStruct = static_cast<bodyUserData*>(BodyIterator->GetUserData());

					if (STATE_DRAW != gameState || STATE_LOSE != gameState || STATE_WON != gameState)
					{
						if (myStruct->type == 1)
						{
							if (!cl.player_hit)
							{
								v_actors[0]->Draw();
							}
						}

						else if (myStruct->type == 11)
						{
							if (!cl.enemy_hit)
							{
								v_actors[1]->Draw();
							}
						}

						else if (myStruct->type == 3)
						{
							//b->Draw();
							for (auto & v_game_object : v_game_objects)
							{
								v_game_object->Draw();
							}
						}
						else if (myStruct->type == 10)
						{
							//v_bullets[0]->Draw(); // draw player bullet
							v_bullets[1]->Draw(); // draw enemy bullet
						}
						else if (myStruct->type == 15)
						{
							v_bullets[0]->Draw(); // draw player bullet
							//v_bullets[1]->Draw(); // draw enemy bullet
						}
					}
				}
			}

			if (draw_path_finder_debug)
			{
				v_actors[1]->Draw_Pathfinder(v_game_objects[1]->get_vert_bush());
			}

			this->_data->window.draw(this->_flag_captured);
			this->_data->window.draw(this->_flag_captured_enemy);
			this->_data->window.draw(this->_playerCaptureNoText);
			this->_data->window.draw(this->_enemyCaptureNoText);
			this->_data->window.draw(this->player_bullet_no_text);
			this->_data->window.draw(this->_TgameClockMinute);
			this->_data->window.draw(this->_TgameClock);

			drawMessages();

			if (debug)
			{
				myWorld->DrawDebugData();
			}

			this->_data->window.display();
	}

	void GameState::CheckPlayerHasWon()
	{
		if (minute == 3 && (int)this->_gameClock.getElapsedTime().asSeconds() == 00 && playerCapture > enemyCapture)
		{
			playerWins = true;
			gameState = STATE_WON;
		}
		else if (minute == 3 && (int)this->_gameClock.getElapsedTime().asSeconds() == 00 && enemyCapture > playerCapture)
		{
			playerWins = false;
			gameState = STATE_LOSE;
		}
		else if (minute == 3 && (int)this->_gameClock.getElapsedTime().asSeconds() == 00 && playerCapture == enemyCapture)
		{
			playerWins = false;
			gameState = STATE_DRAW;
		}
		if ((STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState))
		{
			this->_clock.restart();
			restart_clock = true;
			std::cout << this->_clock.getElapsedTime().asSeconds() << std::endl;
		}
	}

	void GameState::drawMessages()
	{
		if (gameState == STATE_WON)
		{
			this->_data->window.draw(this->_win);
			game_over = true;
		}
		else if (gameState == STATE_LOSE)
		{
			this->_data->window.draw(this->_lose);
			game_over = true;
		}
		else if (gameState == STATE_DRAW)
		{
			this->_data->window.draw(this->_draw);
			game_over = true;
		}
	}

	void GameState::HandleScoresAndTime()
	{

		//keeps track and updated the player and enemies scores
		this->_playerCaptureNo = std::to_string(playerCapture);
		this->_enemyCaptureNo = std::to_string(enemyCapture);
		this->_playerCaptureNoText.setString(_playerCaptureNo);
		this->_enemyCaptureNoText.setString(_enemyCaptureNo);

		//Begins the game clock
		this->_SgameClock = std::to_string((int)this->_gameClock.getElapsedTime().asSeconds());
		this->_TgameClock.setString("Time:      " + this->_SgameClock);

		if (static_cast<int>(this->_gameClock.getElapsedTime().asSeconds()) == 60)
		{
			minute = minute + 1;
			this->_gameClock.restart();
		}

		this->_SgameClockMinute = std::to_string(minute);
		this->_TgameClockMinute.setString(this->_SgameClockMinute + " :");

		if (minute == 1 && (int)this->_gameClock.getElapsedTime().asSeconds() == 54)
		{
			this->_data->assets.GetMusic("gameplay").stop();
			this->_data->assets.GetMusic("countdown").play();
		}

		/////////////////When player returns blue flag to base//////////////////////////
		if (v_game_objects[1]->get_blue_flag_player() && cl.red_ped_hit_player && !cl.player_score)
		{
			playerCapture++;
			cl.player_score = true;
		}
		else
		{
			cl.player_score = false;
		}

		/////////////When Enemy returns the red flag to base/////////////////////////
		if (v_game_objects[1]->get_red_flag_enemy() && cl.blue_ped_hit_enemy && !cl.enemy_score)
		{
			enemyCapture++;
			cl.enemy_score = true;
		}
		else
		{
			cl.enemy_score = false;
		}

		/////////////////When player returns RED flag to base//////////////////////////
		if (v_game_objects[1]->get_red_flag_player() && cl.red_ped_hit_player && !red_flag_returned)
		{
			red_flag_returned = true;
		}
		else
		{
			red_flag_returned = false;
		}

		/////////////When Enemy returns the BLUE flag to base/////////////////////////
		if (v_game_objects[1]->get_blue_flag_enemy() && cl.blue_ped_hit_enemy && !blue_flag_returned)
		{
			blue_flag_returned = true;
		}
		else
		{
			blue_flag_returned = false;
		}

		///////////////////Checks for Player health//////////////////////////////
		if (cl.player_hit)
		{
			v_actors[0]->respawn.restart();
			if (player_health > 0)
			{
				player_health = player_health - bullet_damage;
				cl.player_hit = false;
				std::cout << "PLAYER HEALTH:  " << player_health << std::endl;
			}
			else
			{
				player_health = 0;
				cl.player_hit = false;
			}
		}
		if (player_health <= 0)
		{
			has_player_died = true;
		}
		else
		{
			has_player_died = false;
		}

		if (cl.player_in_base && (player_health < 100 || player_bullet_no_ < 50))
		{
			const auto time = static_cast<int>(player_base_timer.getElapsedTime().asSeconds());
			if (time > 2)
			{
				if (player_health < 101)
				{
					player_health = player_health + health_regen;
					if (player_health >= 100)
					{
						player_health = 100;
					}
				}

				if (player_bullet_no_ < 50)
				{
					player_bullet_no_ = 50;

				}
			}
			std::cout << "BASE TIMER:  " << static_cast<int>(player_base_timer.getElapsedTime().asSeconds()) << std::endl;
		}

		else
		{
			player_base_timer.restart();
		}

		///////////////////Checks for Enemy health//////////////////////////////
		if (cl.enemy_hit)
		{
			e_hit = true;
			v_actors[1]->respawn.restart();
			if (enemy_health > 0)
			{
				enemy_health = enemy_health - bullet_damage;
				cl.enemy_hit = false;
				std::cout << "ENEMY HEALTH:  " << enemy_health << std::endl;
				cout << "ENEMY BULLET FULL:  " << enemy_bullet_no_ << endl;
			}
			else
			{
				enemy_health = 0;
				cl.enemy_hit = false;
			}
		}
		else
		{
			e_hit = false;
		}

		if(enemy_health == 100)
		{
			full_health = true;
		}
		else
		{
			full_health = false;
		}

		if (enemy_health <= 0)
		{
			has_enemy_died = true;
		}
		else
		{
			has_enemy_died = false;
		}

		if (cl.enemy_in_base && (enemy_health < 100 || enemy_bullet_no_ < 50))
		{
			const auto time = static_cast<int>(enemy_base_timer.getElapsedTime().asSeconds());
			if (time > 2)
			{
				if (enemy_health < 101)
				{
					enemy_health = enemy_health + health_regen;
					if (enemy_health >= 100)
					{
						enemy_health = 100;
					}
				}

				if (enemy_bullet_no_ < 50)
				{
					enemy_bullet_no_ = 50;
					cout << "ENEMY BULLET FULL:  " << enemy_bullet_no_ << endl;
				}
			}
			//std::cout << "BASE TIMER:  " << static_cast<int>(enemy_base_timer.getElapsedTime().asSeconds()) << std::endl;
		}

		else
		{
			enemy_base_timer.restart();
		}

	}

	void GameState::removeBodiesA()
	{
		std::vector<b2Body*> &ToRemove = cl.getBodyToRemoveA();
		for (int i = 0; i < ToRemove.size(); i++)
		{
			b2Body* b = ToRemove.at(i);
			myWorld->DestroyBody(b);

		}
		ToRemove.clear();
	}

	void GameState::removeBodiesB()
	{
		std::vector<b2Body*> &ToRemove = cl.getBodyToRemoveB();
		for (int i = 0; i < ToRemove.size(); i++)
		{
			b2Body* b = ToRemove.at(i);
			myWorld->DestroyBody(b);

		}
		ToRemove.clear();
	}

	void GameState::shoot()
	{
		v_bullets[1]->Init(myWorld, v_actors[1]->getBody()->GetPosition().x, v_actors[1]->getBody()->GetPosition().y,
			v_actors[1]->getBody(), v_actors[0]->getPosition(), (v_actors[1]->getSprite().getRotation() + 180) * (b2_pi / 180)); //Enemy Bullet Id is 9
	}

	void GameState::playershoot()
	{
		v_bullets[0]->Init(myWorld, v_actors[0]->getBody()->GetPosition().x, v_actors[0]->getBody()->GetPosition().y,
		v_actors[0]->getBody()->GetAngle(), v_actors[0]->getBody()); //Player Bullet Id is 10
	}
}
