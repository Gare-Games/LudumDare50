#ifndef ENEMY3_H
#define ENEMY3_H

#include "enemy.h"

class FastEnemy : public Enemy {
	public: 
		FastEnemy(Vector2 startPosition, Player* target);
		float hitpoints = 1.0f;
		Texture2D GetTexture2D();
};
#endif
