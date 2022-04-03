#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "garegames.h"
#include "texturelist.h"
#include "player.h"

class Player;

enum class EnemyMode { CHASE = 1, MOVETO = 2 };

class Enemy {
	public:
		Enemy(Vector2 startPosition, Player* target);
		float hitpoints = 1.0f;
		Vector2 position;
		Vector2 targetMove;
		bool bDead = false;
		void Update(float frameTime);
		void Draw();
		void Move(bool up, bool down, bool left, bool right);
		Texture2D GetTexture2D();
		Player* player;
		Rectangle GetHitBoxLoc();
		void SetMoveTarget(Vector2 position);
		int width = 20;
		int height = 50;
		float speed = 1.5f;
		float diagnolSpeed;
		EnemyMode mode;
};

#endif
