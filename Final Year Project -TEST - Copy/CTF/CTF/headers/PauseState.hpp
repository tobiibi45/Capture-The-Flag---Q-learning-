#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace KStudio
{
	class PauseState : public State
	{
	public:
		PauseState(GameDataRef data);
		~PauseState();

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Sprite _background;
		sf::Sprite _resume;
		sf::Sprite _settings;
		sf::Sprite _exit;

	};
}
