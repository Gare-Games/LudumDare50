#ifndef ENEMY2_H
#define ENEMY2_H

#include "enemy.h"

class ToughEnemy : public Enemy {
	public: 
		ToughEnemy(Vector2 startPosition, Player* target);
		float hitpoints = 10.0f;
		Texture2D GetTexture2D();
};
#endif
