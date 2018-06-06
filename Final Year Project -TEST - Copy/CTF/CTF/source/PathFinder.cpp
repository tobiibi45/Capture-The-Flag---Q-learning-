#include "PathFinder.h"
#include "ENGINEDEFINITIONS.hpp"
#include "Actors.hpp"
#include <iostream>
#include "GameObjects.h"

KStudio::PathFinder::PathFinder(GameDataRef data) : _data(data)
{
	iniStartGoal = false;
	foundGoal = false;
	
}

void KStudio::PathFinder::findPath(sf::Vector2f myPos, sf::Vector2f targetPos)
{
	if (!iniStartGoal)
	{
		for (int i = 0; i < openList.size(); i++)
		{
			delete openList[i];
		}
		openList.clear();

		for (int i = 0; i < visitedList.size(); i++)
		{
			delete visitedList[i];
		}
		visitedList.clear();
		for (int i = 0; i < pathToGoal.size(); i++)
		{
			delete pathToGoal[i];
		}
		pathToGoal.clear();

		//Begin Search
		searchGrid start;
		start.xPos = start.get_cell_size(myPos.x);
		start.yPos = start.get_cell_size(myPos.y);

		//Set Goals
		searchGrid goal;
		goal.xPos = goal.get_cell_size(targetPos.x);
		goal.yPos = goal.get_cell_size(targetPos.y);

		setStartGoals(start, goal);
		iniStartGoal = true;

	}

	if (iniStartGoal)
	{
		continuePath();
	}
}

void KStudio::PathFinder::setStartGoals(searchGrid start, searchGrid goal)
{
	startingCell = new searchGrid(start.xPos, start.yPos, NULL);
	goalCell = new searchGrid(goal.xPos, goal.yPos, &goal);

	startingCell->DistTravelled = 0;
	startingCell->targetDist = startingCell->mDistance(goalCell);
	startingCell->parent = 0;

	openList.push_back(startingCell);
}

KStudio::searchGrid* KStudio::PathFinder::getNextCell()
{
	float bestTotalDistance = 999999.0f;
	int index = -1;
	searchGrid* nextCell;
	nextCell = NULL;

	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->getTotalDist() < bestTotalDistance)
		{
			bestTotalDistance = openList[i]->getTotalDist();
			index = i;
		}
	}

	if (index >= 0)
	{
		nextCell = openList[index];
		visitedList.push_back(nextCell);
		openList.erase(openList.begin() + index);
	}

	return nextCell;
}

void KStudio::PathFinder::pathOpen(int x, int y, float newCost, searchGrid *parent)
{
	//std::cout << "  WALLX: " << (int)(return_sahpe().getGlobalBounds().width / CELL_SIZE) << std::endl;

	//if path is blocked ignore it
	if (in_wall(x,y))
	{
		return;
	}


	int id = y * WORLD_SIZE + x;
	for (int i = 0; i < visitedList.size(); i++)
	{
		if (id == visitedList[i]->ID) //checks if the cell is in the visited list
		{
			return; // return the id if it is.
		}
	}

	searchGrid* newCell = new searchGrid(x, y, parent);
	newCell->DistTravelled = newCost;
	newCell->targetDist = parent->mDistance(goalCell);

	for (int i = 0; i < openList.size(); i++)
	{
		if(id == openList[i]->ID)
		{
			float newFloat = newCell->DistTravelled + newCost + openList[i]->targetDist;

			if (openList[i]->getTotalDist() > newFloat) // if the new float is less than the old one we replace it with the new one 
			{
				openList[i]->DistTravelled = newCell->DistTravelled + newCost;
				openList[i]->parent = newCell;
			}

			else //if new float is greater than the old one we delete it
			{
				delete newCell;
				return;
			}
		}
	}

	openList.push_back(newCell);
}

void KStudio::PathFinder::continuePath()
{
	for (int i = 0; i < 4; i++) //makes it faster to search for whatever it searchs for
	{

		if (openList.empty()) //checks if the open list is empty
		{
			return;
		}

		searchGrid* currentCell = getNextCell();

		if (currentCell->ID == goalCell->ID)
		{
			goalCell->parent = currentCell->parent;

			searchGrid* getPath;

			for (getPath = goalCell; getPath != NULL; getPath = getPath->parent)
			{
				pathToGoal.push_back(new sf::Vector2f(getPath->xPos * CELL_SIZE, getPath->yPos * CELL_SIZE));
			}

			foundGoal = true;
			//return;
		}

		else
		{
			//Calculate Rightcell
			pathOpen(currentCell->xPos + 1, currentCell->yPos, currentCell->DistTravelled + 1, currentCell);

			//Calculate Leftcell
			pathOpen(currentCell->xPos - 1, currentCell->yPos, currentCell->DistTravelled + 1, currentCell);

			//Calculate Upcell
			pathOpen(currentCell->xPos, currentCell->yPos + 1, currentCell->DistTravelled + 1, currentCell);

			//Calculate Downcell
			pathOpen(currentCell->xPos, currentCell->yPos - 1, currentCell->DistTravelled + 1, currentCell);

			for (int i = 0; i < openList.size(); i++)
			{
				if (currentCell->ID == openList[i]->ID)
				{
					openList.erase(openList.begin() + i);
				}
			}

		}
	}
}

sf::Vector2f KStudio::PathFinder::nextPathpos(sf::Vector2f target)
{
	const auto index = 1;

	sf::Vector2f nextPos;
	nextPos.x = pathToGoal[pathToGoal.size() - index]->x + (CELL_SIZE / 2.f);
	nextPos.y = pathToGoal[pathToGoal.size() - index]->y + (CELL_SIZE / 2.f);

	auto dist_length = sqrtf(((nextPos - target).x * (nextPos - target).x) + ((nextPos - target).y * (nextPos - target).y));

	/*sf::Vector2f dist = nextPos - target;
	auto dist_l = sqrtf(dist.x * dist.x) + (dist.y * dist.y);
*/
	if (index < pathToGoal.size())
	{
		if ((dist_length) < 20.f)
		{
			pathToGoal.erase(pathToGoal.end() - index);
		}
	}
	return nextPos;
}


void KStudio::PathFinder::draw_debug(sf::RenderWindow &win, sf::Sprite &sprite, sf::Sprite &e_Sprite)
{
		for (auto & i : openList)
		{
			sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			shape.setOrigin(e_Sprite.getOrigin());
			shape.setPosition(i->xPos * CELL_SIZE + 90.f, i->yPos * CELL_SIZE + 45.f);
			shape.setFillColor(sf::Color::Red);
			win.draw(shape);
		}

		for (auto & i : visitedList)
		{
			sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			shape.setOrigin(e_Sprite.getOrigin());
			shape.setPosition(i->xPos * CELL_SIZE + 90.f, i->yPos * CELL_SIZE + 45.f);
			shape.setFillColor(sf::Color::Blue);
			win.draw(shape);
		}

		for (auto & i : pathToGoal)
		{
			sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			shape.setPosition(i->x, i->y);
			shape.setFillColor(sf::Color::White);
			win.draw(shape);
		}

		shape1.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
		shape1.setOrigin(sf::Vector2f((sprite.getGlobalBounds().width / 2), (sprite.getGlobalBounds().height / 2)));
		shape1.setPosition(_data->assets.getvector("v_MLB").x, _data->assets.getvector("v_MLB").y);
		shape1.setFillColor(sf::Color::Magenta);
		//win.draw(shape1);
}

void KStudio::PathFinder::update()
{
	/////////////////////// Middle Left Bush /////////////////////////////
	this->_data->assets.ini_vector("v_MLB");
	this->_data->assets.getvector("v_MLB") = this->_data->assets.getSprite("StaticObjectsSprites", 0).getPosition();
	this->_data->assets.ini_vector_2("v_MLB_L");
	this->_data->assets.getvector2("v_MLB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 0).getGlobalBounds().width / 2 * WALLS_BUFFER;
	this->_data->assets.getvector2("v_MLB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 0).getGlobalBounds().height / 2 * WALLS_BUFFER2;

	/////////////////////// Middle Right Bush ////////////////////////////
	this->_data->assets.ini_vector("v_MRB");
	this->_data->assets.getvector("v_MRB") = this->_data->assets.getSprite("StaticObjectsSprites", 1).getPosition();
	this->_data->assets.ini_vector_2("v_MRB_L");
	this->_data->assets.getvector2("v_MRB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 1).getGlobalBounds().width / 2 * WALLS_BUFFER;
	this->_data->assets.getvector2("v_MRB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 1).getGlobalBounds().height / 2 * WALLS_BUFFER2;
	
	////////////////////// Left Top vert Bush /////////////////////////////
	this->_data->assets.ini_vector("v_LTVB");
	this->_data->assets.getvector("v_LTVB") = this->_data->assets.getSprite("StaticObjectsSprites", 2).getPosition();
	this->_data->assets.ini_vector_2("v_LTVB_L");
	this->_data->assets.getvector2("v_LTVB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 2).getGlobalBounds().width / 2 * WALLS_BUFFER;
	this->_data->assets.getvector2("v_LTVB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 2).getGlobalBounds().height / 2 * WALLS_BUFFER2;

	////////////////////// Left Bottom vert Bush //////////////////////////
	this->_data->assets.ini_vector("v_LBVB");
	this->_data->assets.getvector("v_LBVB") = this->_data->assets.getSprite("StaticObjectsSprites", 3).getPosition();
	this->_data->assets.ini_vector_2("v_LBVB_L");
	this->_data->assets.getvector2("v_LBVB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 3).getGlobalBounds().width / 2 * WALLS_BUFFER;
	this->_data->assets.getvector2("v_LBVB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 3).getGlobalBounds().height / 2 * WALLS_BUFFER2;

	////////////////////// Right top vert Bush ////////////////////////////
	this->_data->assets.ini_vector("v_RTVB");
	this->_data->assets.getvector("v_RTVB") = this->_data->assets.getSprite("StaticObjectsSprites", 4).getPosition();
	this->_data->assets.ini_vector_2("v_RTVB_L");
	this->_data->assets.getvector2("v_RTVB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 4).getGlobalBounds().width / 2 * WALLS_BUFFER;
	this->_data->assets.getvector2("v_RTVB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 4).getGlobalBounds().height / 2 * WALLS_BUFFER2;

	////////////////////// Right Bottom vert Bush /////////////////////////
	this->_data->assets.ini_vector("v_RBVB");
	this->_data->assets.getvector("v_RBVB") = this->_data->assets.getSprite("StaticObjectsSprites", 5).getPosition();
	this->_data->assets.ini_vector_2("v_RBVB_L");
	this->_data->assets.getvector2("v_RBVB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 5).getGlobalBounds().width / 2 * WALLS_BUFFER;
	this->_data->assets.getvector2("v_RBVB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 5).getGlobalBounds().height / 2 * WALLS_BUFFER2;

	/////////////////////// Middle Top Bush /////////////////////////////
	this->_data->assets.ini_vector("v_MTB");
	this->_data->assets.getvector("v_MTB") = this->_data->assets.getSprite("StaticObjectsSprites", 6).getPosition();
	this->_data->assets.ini_vector_2("v_MTB_L");
	this->_data->assets.getvector2("v_MTB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 6).getGlobalBounds().width / 2 * WALLS_BUFFER2;
	this->_data->assets.getvector2("v_MTB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 6).getGlobalBounds().height / 2 * WALLS_BUFFER;

	////////////////////// Middle Bottom Bush ///////////////////////////
	this->_data->assets.ini_vector("v_MBB");
	this->_data->assets.getvector("v_MBB") = this->_data->assets.getSprite("StaticObjectsSprites", 7).getPosition();
	this->_data->assets.ini_vector_2("v_MBB_L");
	this->_data->assets.getvector2("v_MBB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 7).getGlobalBounds().width / 2 * WALLS_BUFFER2;
	this->_data->assets.getvector2("v_MBB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 7).getGlobalBounds().height / 2 * WALLS_BUFFER;

	////////////////////// Left Top hori Bush ///////////////////////////
	this->_data->assets.ini_vector("v_LTHB");
	this->_data->assets.getvector("v_LTHB") = this->_data->assets.getSprite("StaticObjectsSprites", 8).getPosition();
	this->_data->assets.ini_vector_2("v_LTHB_L");
	this->_data->assets.getvector2("v_LTHB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 8).getGlobalBounds().width / 2 * WALLS_BUFFER2;
	this->_data->assets.getvector2("v_LTHB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 8).getGlobalBounds().height / 2 * WALLS_BUFFER;

	////////////////////// Left Bottom hori Bush /////////////////////////
	this->_data->assets.ini_vector("v_LBHB");
	this->_data->assets.getvector("v_LBHB") = this->_data->assets.getSprite("StaticObjectsSprites", 9).getPosition();
	this->_data->assets.ini_vector_2("v_LBHB_L");
	this->_data->assets.getvector2("v_LBHB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 9).getGlobalBounds().width / 2 * WALLS_BUFFER2;
	this->_data->assets.getvector2("v_LBHB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 9).getGlobalBounds().height / 2 * WALLS_BUFFER;

	////////////////////// Right Top hori Bush ///////////////////////////
	this->_data->assets.ini_vector("v_RTHB");
	this->_data->assets.getvector("v_RTHB") = this->_data->assets.getSprite("StaticObjectsSprites", 10).getPosition();
	this->_data->assets.ini_vector_2("v_RTHB_L");
	this->_data->assets.getvector2("v_RTHB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 10).getGlobalBounds().width / 2 * WALLS_BUFFER2;
	this->_data->assets.getvector2("v_RTHB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 10).getGlobalBounds().height / 2 * WALLS_BUFFER;

	////////////////////// Right Bottom hori Bush /////////////////////////
	this->_data->assets.ini_vector("v_RBHB");
	this->_data->assets.getvector("v_RBHB") = this->_data->assets.getSprite("StaticObjectsSprites", 11).getPosition();
	this->_data->assets.ini_vector_2("v_RBHB_L");
	this->_data->assets.getvector2("v_RBHB_L").x = this->_data->assets.getSprite("StaticObjectsSprites", 11).getGlobalBounds().width / 2 * WALLS_BUFFER2;
	this->_data->assets.getvector2("v_RBHB_L").y = this->_data->assets.getSprite("StaticObjectsSprites", 11).getGlobalBounds().height / 2 * WALLS_BUFFER;
}

bool KStudio::PathFinder::in_wall(int x, int y) const
{
	auto pointX = x;
	auto pointY = y;

	// Just had to change around the math
	if (
		(pointX < (int)((_data->assets.getvector("v_MLB").x + _data->assets.getvector2("v_MLB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_MLB").x - _data->assets.getvector2("v_MLB_L").x) / CELL_SIZE) && //0
		pointY < (int)((_data->assets.getvector("v_MLB").y + _data->assets.getvector2("v_MLB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_MLB").y - _data->assets.getvector2("v_MLB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_MRB").x + _data->assets.getvector2("v_MRB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_MRB").x - _data->assets.getvector2("v_MRB_L").x) / CELL_SIZE) && //1
			pointY < (int)((_data->assets.getvector("v_MRB").y + _data->assets.getvector2("v_MRB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_MRB").y - _data->assets.getvector2("v_MRB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_LTVB").x + _data->assets.getvector2("v_LTVB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_LTVB").x - _data->assets.getvector2("v_LTVB_L").x) / CELL_SIZE) && //2
			pointY < (int)((_data->assets.getvector("v_LTVB").y + _data->assets.getvector2("v_LTVB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_LTVB").y - _data->assets.getvector2("v_LTVB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_LBVB").x + _data->assets.getvector2("v_LBVB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_LBVB").x - _data->assets.getvector2("v_LBVB_L").x) / CELL_SIZE) && //3
			pointY < (int)((_data->assets.getvector("v_LBVB").y + _data->assets.getvector2("v_LBVB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_LBVB").y - _data->assets.getvector2("v_LBVB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_RTVB").x + _data->assets.getvector2("v_RTVB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_RTVB").x - _data->assets.getvector2("v_RTVB_L").x) / CELL_SIZE) && //4
			pointY < (int)((_data->assets.getvector("v_RTVB").y + _data->assets.getvector2("v_RTVB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_RTVB").y - _data->assets.getvector2("v_RTVB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_RBVB").x + _data->assets.getvector2("v_RBVB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_RBVB").x - _data->assets.getvector2("v_RBVB_L").x) / CELL_SIZE) && //5
			pointY < (int)((_data->assets.getvector("v_RBVB").y + _data->assets.getvector2("v_RBVB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_RBVB").y - _data->assets.getvector2("v_RBVB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_MTB").x + _data->assets.getvector2("v_MTB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_MTB").x - _data->assets.getvector2("v_MTB_L").x) / CELL_SIZE) && //6
			pointY < (int)((_data->assets.getvector("v_MTB").y + _data->assets.getvector2("v_MTB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_MTB").y - _data->assets.getvector2("v_MTB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_MBB").x + _data->assets.getvector2("v_MBB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_MBB").x - _data->assets.getvector2("v_MBB_L").x) / CELL_SIZE) && //7
			pointY < (int)((_data->assets.getvector("v_MBB").y + _data->assets.getvector2("v_MBB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_MBB").y - _data->assets.getvector2("v_MBB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_LTHB").x + _data->assets.getvector2("v_LTHB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_LTHB").x - _data->assets.getvector2("v_LTHB_L").x) / CELL_SIZE) && //8
			pointY < (int)((_data->assets.getvector("v_LTHB").y + _data->assets.getvector2("v_LTHB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_LTHB").y - _data->assets.getvector2("v_LTHB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_LBHB").x + _data->assets.getvector2("v_LBHB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_LBHB").x - _data->assets.getvector2("v_LBHB_L").x) / CELL_SIZE) && //9
			pointY < (int)((_data->assets.getvector("v_LBHB").y + _data->assets.getvector2("v_LBHB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_LBHB").y - _data->assets.getvector2("v_LBHB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_RTHB").x + _data->assets.getvector2("v_RTHB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_RTHB").x - _data->assets.getvector2("v_RTHB_L").x) / CELL_SIZE) && //10
			pointY < (int)((_data->assets.getvector("v_RTHB").y + _data->assets.getvector2("v_RTHB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_RTHB").y - _data->assets.getvector2("v_RTHB_L").y) / CELL_SIZE))
		||
		(pointX < (int)((_data->assets.getvector("v_RBHB").x + _data->assets.getvector2("v_RBHB_L").x) / CELL_SIZE) && pointX >(int)((_data->assets.getvector("v_RBHB").x - _data->assets.getvector2("v_RBHB_L").x) / CELL_SIZE)  && //11
			pointY < (int)((_data->assets.getvector("v_RBHB").y + _data->assets.getvector2("v_RBHB_L").y) / CELL_SIZE) && pointY >(int)((_data->assets.getvector("v_RBHB").y - _data->assets.getvector2("v_RBHB_L").y) / CELL_SIZE))
		||
		pointX < 0 || pointY < 0 || pointX > WORLD_SIZE || pointY > WORLD_SIZE 
		|| 
		pointX < (this->_data->assets.getborderpos("VBorders", 0).x * SCALE + 385.f) / CELL_SIZE 
		|| 
		pointX > (this->_data->assets.getborderpos("VBorders", 1).x * SCALE + 360.f) / CELL_SIZE
		|| 
		pointY < (this->_data->assets.getborderpos("HBorders", 1).y * SCALE + 20.f) / CELL_SIZE 
		|| 
		pointY > (this->_data->assets.getborderpos("HBorders", 0).y * SCALE) / CELL_SIZE
		)
	{
		return true;
	}
	return false;
}

sf::RectangleShape KStudio::PathFinder::return_sahpe() const
{
	return shape;
}

sf::Vector2f KStudio::PathFinder::randomgoal()
{
	int rand_X = (int)(rand() % WORLD_SIZE + (WORLD_SIZE / 2.0f));
	int rand_Y = (int)(rand() % WORLD_SIZE + (WORLD_SIZE / 2.0f));

	return sf::Vector2f(static_cast<float>(rand_X), static_cast<float>(rand_Y));
}
