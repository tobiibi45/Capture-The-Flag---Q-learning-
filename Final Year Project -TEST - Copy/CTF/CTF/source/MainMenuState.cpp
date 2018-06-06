#include <sstream>
#include "MainMenuState.hpp"
#include "ENGINEDEFINITIONS.hpp"
#include <iostream>
#include "GameState.hpp"
#include "SettingsState.h"

namespace KStudio
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		
		this->_data->assets.LoadMusic("gameplay", MUSIC_GAMEPLAY);
		if(this->_data->assets.GetMusic("gameplay").getStatus() == sf::SoundSource::Playing)
		{
			this->_data->assets.GetMusic("gameplay").stop();
		}

		this->_data->assets.LoadMusic("menu", MUSCI_MENU);
		this->_data->assets.GetMusic("menu").play();
		this->_data->assets.GetMusic("menu").setLoop(true);

		this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("New Game", MAIN_MENU_NEWGAME_FILEPATH);
		this->_data->assets.LoadTexture("Settings", MAIN_MENU_SETTINGS_FILEPATH);
		this->_data->assets.LoadTexture("Exit", MAIN_MENU_EXIT_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		this->_newgame.setTexture(this->_data->assets.GetTexture("New Game"));
		this->_settings.setTexture(this->_data->assets.GetTexture("Settings"));
		this->_exit.setTexture(this->_data->assets.GetTexture("Exit"));

		this->_newgame.setPosition((SCREEN_WIDTH / 2) - (this->_newgame.getGlobalBounds().width / 2), (this->_newgame.getGlobalBounds().height * 0.6));
		this->_settings.setPosition((SCREEN_WIDTH / 2) - (this->_settings.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_settings.getGlobalBounds().height / 2));
		this->_exit.setPosition((SCREEN_WIDTH / 2) - (this->_exit.getGlobalBounds().width / 2), (this->_exit.getGlobalBounds().height * 6.5));
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_newgame, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
				this->_data->game_Start = true;
			}
			if (this->_data->input.IsSpriteClicked(this->_settings, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new SettingsState(_data)), true);
			}
			if (this->_data->input.IsSpriteClicked(this->_exit, sf::Mouse::Left, this->_data->window))
			{
				this->_data->window.close();
			}
		}
	}

	void MainMenuState::Update(float dt)
	{
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_newgame);
		this->_data->window.draw(this->_settings);
		this->_data->window.draw(this->_exit);

		this->_data->window.display();
	}
}
