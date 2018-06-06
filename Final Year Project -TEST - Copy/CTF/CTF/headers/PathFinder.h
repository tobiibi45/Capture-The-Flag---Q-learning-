#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "aStarSearch.h"
#include "GameObjects.h"
#include "Game.hpp"

using namespace std;
namespace KStudio
{
	class Actors;

	class PathFinder
	{
	public:

		PathFinder(GameDataRef data);
		~PathFinder(void) = default;

		GameDataRef _data;
		void findPath(sf::Vector2f myPos, sf::Vector2f targetPos);
		sf::Vector2f nextPathpos(sf::Vector2f target);
		void clearOpenList() { openList.clear(); }
		void clearVisitedList() { visitedList.clear(); }
		void cleaPathToGoal() { pathToGoal.clear(); }
		bool iniStartGoal;
		bool foundGoal;
		std::vector<sf::Vector2f*> pathToGoal;
		void draw_debug(sf::RenderWindow &win, sf::Sprite &sprite, sf::Sprite &e_Sprite);
		sf::Vector2f randomgoal();
		sf::RectangleShape shape;
		sf::RectangleShape shape1;
		void update();
		bool in_wall(int x, int y) const;

		sf::RectangleShape return_sahpe() const;
	private:
		void setStartGoals(searchGrid start, searchGrid goal);
		void pathOpen(int x, int y, float newCost, searchGrid *parent);
		searchGrid *getNextCell();
		void continuePath();

		searchGrid *startingCell;
		searchGrid *goalCell;
		std::vector<searchGrid*> openList;
		std::vector<searchGrid*> visitedList;

	};
}
