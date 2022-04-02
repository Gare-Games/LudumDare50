#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include "garegames.h"
#include "colors.h"

class Bullet {
	public:
		Bullet(Vector2 position, Direction targetDirection);
		Vector2 position;
		Vector2 lastPosition;
		int width;
		int height;
		Direction direction;
		float speed;
		float diagnolSpeed;
		void Update(float frameTime);
		void Draw();
};

#endif
