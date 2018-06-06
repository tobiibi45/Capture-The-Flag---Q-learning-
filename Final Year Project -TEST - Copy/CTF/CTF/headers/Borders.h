#pragma once

#include "Box2D\Box2D.h"
#include "GameObjects.h"
#include "Game.hpp"


namespace KStudio
{
	class Borders : public GameObjects
	{
	public:
		Borders(GameDataRef _data);
		void Init(b2World *world)override;
	private:
		GameDataRef _data;



	};
}
