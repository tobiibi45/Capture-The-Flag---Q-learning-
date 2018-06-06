#pragma once

#include <sstream>
#include "SplashState.hpp"
#include "ENGINEDEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include <iostream>

namespace KStudio
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::Init()
	{
		this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Logo", LOGO_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
		_logo.setTexture(this->_data->assets.GetTexture("Logo"));

		_background.setPosition((SCREEN_WIDTH / 2) - (this->_background.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_background.getGlobalBounds().height / 2));
		_logo.setPosition((SCREEN_WIDTH / 2) - (this->_logo.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_logo.getGlobalBounds().height / 2));

	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// Switch To Main Menu
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
	}

	void SplashState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw( this->_logo );

		this->_data->window.display();
	}
}
