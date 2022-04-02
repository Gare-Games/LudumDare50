#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "garegames.h"
#include "texturelist.h"
#include "player.h"

class Player;
class Enemy {
	public:
		Enemy(Vector2 startPosition, Player* target);
		float hitpoints = 1.0f;
		Vector2 position;
		bool bDead = false;
		void Update(float frameTime);
		void Draw();
		Texture2D GetTexture2D();
		Player* player;
		Rectangle GetHitBoxLoc();
		int width = 20;
		int height = 50;
};

#endif
