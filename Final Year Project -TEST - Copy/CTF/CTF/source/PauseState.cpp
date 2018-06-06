#include <sstream>
#include "PauseState.hpp"
#include "MainMenuState.hpp"
#include "ENGINEDEFINITIONS.hpp"
#include <iostream>
#include "GameState.hpp"
#include "SettingsState.h"

namespace KStudio
{
	PauseState::PauseState(GameDataRef data) : _data(data)
	{

	}

	PauseState::~PauseState()
	{
		
	}

	void PauseState::Init()
	{
		this->_data->assets.GetMusic("gameplay").pause();

		this->_data->assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Resume", PAUSE_RESUME_FILEPATH);
		this->_data->assets.LoadTexture("Settings", PAUSE_SETTINGS_FILEPATH);
		this->_data->assets.LoadTexture("Exit", PAUSE_EXIT_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Pause Background"));
		this->_resume.setTexture(this->_data->assets.GetTexture("Resume"));
		this->_settings.setTexture(this->_data->assets.GetTexture("Settings"));
		this->_exit.setTexture(this->_data->assets.GetTexture("Exit"));

		this->_resume.setPosition((SCREEN_WIDTH / 2) - (this->_resume.getGlobalBounds().width / 2), (this->_resume.getGlobalBounds().height * 0.6));
		this->_settings.setPosition((SCREEN_WIDTH / 2) - (this->_settings.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_settings.getGlobalBounds().height / 2));
		this->_exit.setPosition((SCREEN_WIDTH / 2) - (this->_exit.getGlobalBounds().width / 2), (this->_exit.getGlobalBounds().height * 6.5));

	}

	void PauseState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_resume, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.RemoveState();
				this->_data->assets.GetMusic("gameplay").play();
			}
			if (this->_data->input.IsSpriteClicked(this->_settings, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new SettingsState(_data)), false);
			}
			if (this->_data->input.IsSpriteClicked(this->_exit, sf::Mouse::Left, this->_data->window))
			{
				this->_data->assets.GetMusic("gameplay").stop();
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void PauseState::Update(float dt)
	{
	
	}

	void PauseState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_resume);
		this->_data->window.draw(this->_settings);
		this->_data->window.draw(this->_exit);

		this->_data->window.display();
	}
}
