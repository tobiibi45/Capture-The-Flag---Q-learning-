#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace KStudio
{
	class SettingsState : public State
	{
	public:
		SettingsState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Music music;

		sf::Sprite _background;
		sf::Sprite _music_volume;
		sf::Sprite _effects_volume;
		sf::Sprite _exit;

		sf::Sprite _add;
		sf::Sprite _subtract;

		sf::Sprite e_add;
		sf::Sprite e_subtract;

		sf::String mVolume;
		sf::Text mText;
		sf::String eVolume;
		sf::Text eText;

		int i_mvolume;
		int i_evolume;



	};
}
