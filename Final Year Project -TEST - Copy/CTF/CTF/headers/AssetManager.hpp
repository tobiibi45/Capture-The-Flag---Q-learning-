#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include <unordered_map>

namespace KStudio
{
	class AssetManager
	{
	public:
		AssetManager() { }
		~AssetManager() { }

		bool LoadTexture(std::string name, std::string fileName);
		sf::Texture &GetTexture(std::string name);

		bool LoadSound(std::string name, std::string fileName);
		sf::SoundBuffer &GetSound(std::string name);

		bool LoadMusic(std::string name, std::string fileName);
		sf::Music &GetMusic(std::string name);

		bool LoadFont(std::string name, std::string fileName);
		sf::Font &GetFont(std::string name);

		bool save_sprites(std::string name, std::vector<sf::Sprite> &sprites);
		sf::Sprite &getSprite(std::string name, int id);

		bool ini_vector(std::string name);
		sf::Vector2f &getvector(std::string name);

		bool ini_vector_2(std::string name);
		sf::Vector2f &getvector2(std::string name);

		bool save_border_pos(std::string name, std::vector<b2Vec2> &b_vec);
		b2Vec2 &getborderpos(std::string name, int id);

	private:
		
		std::unordered_map<std::string, sf::Texture> _textures;
		std::unordered_map<std::string, sf::Texture>::iterator it;

		std::unordered_map<std::string, sf::Font> _fonts;
		std::unordered_map<std::string, sf::Font>::iterator it2;

		std::unordered_map<std::string, sf::SoundBuffer> _sound;
		std::unordered_map<std::string, sf::SoundBuffer>::iterator it3;

		std::unordered_map<std::string, sf::Music> _music;
		std::unordered_map<std::string, sf::Music>::iterator it4;

		std::unordered_map<std::string, std::vector<sf::Sprite>> _the_sprites;
		std::unordered_map<std::string, std::vector<sf::Sprite>>::iterator it5;

		std::unordered_map<std::string, std::vector<b2Vec2>> _the_pos;
		std::unordered_map<std::string, std::vector<b2Vec2>>::iterator it7;

		std::unordered_map<std::string, sf::Vector2f> _vectors;
		std::unordered_map<std::string, sf::Vector2f>::iterator it6;

		std::unordered_map<std::string, sf::Vector2f> _vectors_1;
		std::unordered_map<std::string, sf::Vector2f>::iterator it8;
	};
}
