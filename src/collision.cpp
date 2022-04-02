#include "collision.h"


// The most direct approach. Prefer this over others.
bool Collision::PointWithRect(Vector2 point, Rectangle rect)
{
	bool xCollision = false;
	bool yCollision = false;
	if (point.x >= rect.x && point.x <= rect.x + rect.width) xCollision = true;
	if (point.y >= rect.y && point.y <= rect.y + rect.height) yCollision = true;
	return xCollision && yCollision;
}

bool Collision::RectWithRect(Rectangle rect1, Rectangle rect2)
{
	if (
			(rect1.width + rect1.x) > rect2.x && 
			rect1.x < (rect2.width + rect2.x) && 
			(rect1.height + rect1.y) > rect2.y && 
			rect1.y < (rect2.height + rect2.y)
	)
	{
		return true;
	}
	return false;
}
