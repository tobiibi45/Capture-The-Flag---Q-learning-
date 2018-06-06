#pragma once
#include <math.h>
#include "ENGINEDEFINITIONS.hpp"


namespace KStudio
{
	struct searchGrid
	{
	public:
		float xPos, yPos;
		int ID;

		searchGrid *parent;

		float DistTravelled;

		float targetDist;

		searchGrid() { parent = 0; }

		searchGrid(int x, int y, searchGrid *_parent = NULL) { xPos = x, yPos = y, parent = _parent, ID = y * WORLD_SIZE + x, DistTravelled = 0, targetDist = 0; }

		float getTotalDist() { return DistTravelled + targetDist; }

		float mDistance(searchGrid *nodeEnd)
		{
			float x = (float)(fabs((float)(this->xPos - nodeEnd->xPos)));

			float y = (float)(fabs((float)(this->yPos - nodeEnd->yPos)));

			return (x * SCALE)  + (y * SCALE);
		}

		float get_cell_size(float pos)
		{
			return pos / CELL_SIZE;
		}
	};
}