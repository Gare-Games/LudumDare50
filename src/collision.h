#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"

class Collision 
{
	public:
		static bool PointWithRect(Vector2 point, Rectangle rect);
		static bool RectWithRect(Rectangle rect1, Rectangle rect2);
};

#endif
