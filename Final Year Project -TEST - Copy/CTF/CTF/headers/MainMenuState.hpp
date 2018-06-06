#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace KStudio
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init();

		// No pause() or resume() methods here as this
		// is a very simple example of a game state.

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Music music;

		sf::Sprite _background;
		sf::Sprite _newgame;
		sf::Sprite _settings;
		sf::Sprite _exit;
		sf::Sprite _title;
	};
}
