#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AssetManager.hpp"
#include <iostream>

namespace KStudio
{
	bool AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		it = _textures.find(name);
		if (it != _textures.end())
		{
			std::cout << "Texture already Loaded " << name << '\n';
			return false;
		}

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex;
			std::cout << "Texture Loaded:  " << name << "  File Path:  " << fileName << std::endl;
			return true;
		}
	}

	sf::Texture &AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}


	bool AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		it2 = _fonts.find(name);
		if (it2 != _fonts.end())
		{
			return false;
		}

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;

		}
		return true;
	}

	sf::Font &AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}

	bool AssetManager::LoadSound(std::string name, std::string fileName)
	{
		sf::SoundBuffer s;

		it3 = _sound.find(name);
		if (it3 != _sound.end())
		{
			std::cout << "Sound already Loaded " << name << '\n';
			return false;
		}

		if (s.loadFromFile(fileName))
		{
			this->_sound[name] = s;
			std::cout << "Sound Loaded:  " << name << "  File Path:  " << fileName << std::endl;
		}
		return true;
	}

	sf::SoundBuffer &AssetManager::GetSound(std::string name)
	{
		return this->_sound.at(name);
	}

	bool AssetManager::LoadMusic(std::string name, std::string fileName)
	{
		it4 = _music.find(name);
		if (it4 != _music.end())
		{
			std::cout << "Music already Loaded " << name << '\n';
			return false;
		}

		if (this->_music[name].openFromFile(fileName))
		{
			this->_music[name];
			std::cout << "Music Loaded:  " << name << "  File Path:  " << fileName << std::endl;
		}
		return true;
	}

	sf::Music& AssetManager::GetMusic(std::string name)
	{
		return this->_music.at(name);
	}

	bool AssetManager::save_sprites(std::string name, std::vector<sf::Sprite>& sprites)
	{
		it5 = _the_sprites.find(name);
		if (it5 != _the_sprites.end())
		{

			return false;
		}
		this->_the_sprites[name] = sprites;
		return true;
	}

	sf::Sprite& AssetManager::getSprite(std::string name, int id)
	{
		return this->_the_sprites.at(name)[id];
	}

	bool AssetManager::ini_vector(std::string name)
	{
		sf::Vector2f vector;

		it6 = _vectors.find(name);
		if (it6 != _vectors.end())
		{
			return false;
		}
		this->_vectors[name] = vector;
		return true;
	}

	sf::Vector2f& AssetManager::getvector(std::string name)
	{
		return this->_vectors.at(name);
	}

	bool AssetManager::ini_vector_2(std::string name)
	{
		sf::Vector2f vector;

		it8 = _vectors_1.find(name);
		if (it8 != _vectors_1.end())
		{
			return false;
		}
		this->_vectors_1[name] = vector;
		return true;
	}

	sf::Vector2f& AssetManager::getvector2(std::string name)
	{
		return this->_vectors_1.at(name);
	}

	bool AssetManager::save_border_pos(std::string name, std::vector<b2Vec2>& b_vec)
	{
		it7 = _the_pos.find(name);
		if (it7 != _the_pos.end())
		{
			return false;
		}
		this->_the_pos[name] = b_vec;
		return true;
	}

	b2Vec2& AssetManager::getborderpos(std::string name, int id)
	{
		return this->_the_pos.at(name)[id];
	}
}
