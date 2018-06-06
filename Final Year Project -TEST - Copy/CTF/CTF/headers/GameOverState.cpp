#include <sstream>
#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "ENGINEDEFINITIONS.hpp"
#include <iostream>
#include "GameState.hpp"

namespace KStudio
{
	GameOverState::GameOverState(GameDataRef data) : _data(data)
	{

	}

	void GameOverState::Init()
	{
		this->_data->assets.LoadTexture("gameover backg", PAUSE_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Retry", RETRY_MESSAGE_FILEPATH);
		this->_data->assets.LoadTexture("Exit", PAUSE_EXIT_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("gameover backg"));
		this->_retry.setTexture(this->_data->assets.GetTexture("Retry"));
		this->_exit.setTexture(this->_data->assets.GetTexture("Exit"));

		this->_retry.setPosition((SCREEN_WIDTH / 2) - (this->_retry.getGlobalBounds().width / 2), (this->_retry.getGlobalBounds().height * 0.6));
		this->_exit.setPosition((SCREEN_WIDTH / 2) - (this->_exit.getGlobalBounds().width / 2), (this->_exit.getGlobalBounds().height * 6.5));

	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_retry, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
			if (this->_data->input.IsSpriteClicked(this->_exit, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void GameOverState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > 3)
		{
			// Switch To Main Menu
			std::cout << "Go To game screen" << std::endl;
		}
	}

	void GameOverState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_retry);
		this->_data->window.draw(this->_exit);

		this->_data->window.display();
	}
}
