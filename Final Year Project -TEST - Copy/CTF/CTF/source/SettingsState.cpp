#include <sstream>
#include "SettingsState.h"
#include "ENGINEDEFINITIONS.hpp"
#include <iostream>
#include "GameState.hpp"
#include "MainMenuState.hpp"

namespace KStudio
{
	SettingsState::SettingsState(GameDataRef data) : _data(data)
	{

	}

	void SettingsState::Init()
	{
		i_mvolume = (int)this->_data->assets.GetMusic("menu").getVolume();
		i_evolume = (int)this->_data->bullet.getVolume();

		this->_data->assets.LoadFont("Score Font", SCORE_FONT);
		this->_data->assets.LoadTexture("Exit", SETTINGS_EXIT_FILEPATH);
		this->_data->assets.LoadTexture("musicV", SETTINGS_MUSIC_VOLUME_FILEPATH);
		this->_data->assets.LoadTexture("effectsV", SETTINGS_EFFECTS_VOLUME_FILEPATH);
		this->_data->assets.LoadTexture("Sbackg", SETTINGS_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("add", SETTINGS_ADD_FILEPATH);
		this->_data->assets.LoadTexture("subtract", SETTINGS_SUBTRACT_FILEPATH);

		this->_data->assets.LoadTexture("eadd", SETTINGS_ADD_FILEPATH);
		this->_data->assets.LoadTexture("esubtract", SETTINGS_SUBTRACT_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Sbackg"));
		this->_music_volume.setTexture(this->_data->assets.GetTexture("musicV"));
		this->_effects_volume.setTexture(this->_data->assets.GetTexture("effectsV"));
		this->_exit.setTexture(this->_data->assets.GetTexture("Exit"));
		this->_add.setTexture(this->_data->assets.GetTexture("add"));
		this->_subtract.setTexture(this->_data->assets.GetTexture("subtract"));

		this->e_add.setTexture(this->_data->assets.GetTexture("eadd"));
		this->e_subtract.setTexture(this->_data->assets.GetTexture("esubtract"));


		this->_music_volume.setPosition(SCREEN_WIDTH / 2 - (this->_exit.getGlobalBounds().width / 2) * 7, SCREEN_HEIGHT / 2 - (this->_exit.getGlobalBounds().height) * 3);
		this->_effects_volume.setPosition(SCREEN_WIDTH / 2 - (this->_exit.getGlobalBounds().width / 2) * 7, SCREEN_HEIGHT / 2 - (this->_exit.getGlobalBounds().height) * 0.2);

		this->_add.setPosition(SCREEN_WIDTH / 2 - (this->_exit.getGlobalBounds().width / 2) * - 1.5, SCREEN_HEIGHT / 2 - (this->_exit.getGlobalBounds().height) * 2.8);
		this->_subtract.setPosition(SCREEN_WIDTH / 2 - (this->_exit.getGlobalBounds().width / 2) * 1.5, SCREEN_HEIGHT / 2 - (this->_exit.getGlobalBounds().height) * 2.7);

		this->e_add.setPosition(SCREEN_WIDTH / 2 - (this->_exit.getGlobalBounds().width / 2) * -1.5, SCREEN_HEIGHT / 2 - (this->_exit.getGlobalBounds().height) * -0.1);
		this->e_subtract.setPosition(SCREEN_WIDTH / 2 - (this->_exit.getGlobalBounds().width / 2) * 1.5, SCREEN_HEIGHT / 2 - (this->_exit.getGlobalBounds().height) * -0.2);

		mVolume = std::to_string((int)this->_data->assets.GetMusic("menu").getVolume());
		mText.setString(mVolume);
		mText.setFont(this->_data->assets.GetFont("Score Font"));
		mText.setStyle(sf::Text::Bold);
		mText.setFillColor(sf::Color::White);
		mText.setPosition(SCREEN_WIDTH / 2 - (this->_exit.getGlobalBounds().width / 2) * 0, SCREEN_HEIGHT / 2 - (this->_exit.getGlobalBounds().height) * 2.8);

		eVolume = std::to_string((int)this->_data->bullet.getVolume());
		eText.setString(eVolume);
		eText.setFont(this->_data->assets.GetFont("Score Font"));
		eText.setStyle(sf::Text::Bold);
		eText.setFillColor(sf::Color::White);
		eText.setPosition(SCREEN_WIDTH / 2 - (this->_exit.getGlobalBounds().width / 2) * 0, SCREEN_HEIGHT / 2 - (this->_exit.getGlobalBounds().height) * -0.1);
		

		this->_exit.setPosition(SCREEN_WIDTH / 2 - (this->_exit.getGlobalBounds().width / 2) * 7, (this->_exit.getGlobalBounds().height * 6.5));
	}

	void SettingsState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_exit, sf::Mouse::Left, this->_data->window))
			{
				if(this->_data->game_Start == true)
				{
					this->_data->machine.RemoveState();
				}
				else
				{
					this->_data->machine.RemoveState();
					this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
				}
				
			}
		}
	}

	void SettingsState::Update(float dt)
	{
		
		if (this->_data->input.IsSpriteClicked(this->_add, sf::Mouse::Left, this->_data->window))
		{
			i_mvolume++;
			this->_data->assets.GetMusic("menu").setVolume(i_mvolume);
			
		}
		
		if (this->_data->input.IsSpriteClicked(this->_subtract, sf::Mouse::Left, this->_data->window))
		{
			i_mvolume--;
			this->_data->assets.GetMusic("menu").setVolume(i_mvolume);
			
		}

		if (this->_data->input.IsSpriteClicked(this->e_add, sf::Mouse::Left, this->_data->window))
		{
			i_evolume++;
			this->_data->bullet.setVolume(i_evolume);

		}

		if (this->_data->input.IsSpriteClicked(this->e_subtract, sf::Mouse::Left, this->_data->window))
		{
			i_evolume--;
			this->_data->bullet.setVolume(i_evolume);

		}

		if (i_mvolume > 100)
		{
			i_mvolume = 100;
		}
		if (i_mvolume < 0)
		{
			i_mvolume = 0;
		}

		if (i_evolume > 100)
		{
			i_evolume = 100;
		}
		if (i_evolume < 0)
		{
			i_evolume = 0;
		}

		mVolume = std::to_string((int)this->_data->assets.GetMusic("menu").getVolume());
		mText.setString(mVolume);

		eVolume = std::to_string((int)this->_data->bullet.getVolume());
		eText.setString(eVolume);

		this->_data->assets.GetMusic("gameplay").setVolume(this->_data->assets.GetMusic("menu").getVolume());

	}

	void SettingsState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_music_volume);
		this->_data->window.draw(this->_effects_volume);
		this->_data->window.draw(this->_add);
		this->_data->window.draw(this->_subtract);

		this->_data->window.draw(this->e_add);
		this->_data->window.draw(this->e_subtract);
		this->_data->window.draw(this->eText);

		this->_data->window.draw(this->mText);
		this->_data->window.draw(this->_exit);

		this->_data->window.display();
	}
}
