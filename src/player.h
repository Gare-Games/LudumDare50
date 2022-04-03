#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "texturelist.h"
#include "weapon.h"
#include "pistol.h"
#include "garegames.h"

using namespace std;

class Player {
	public:
		Player();
		Vector2 position;
		Weapon* currentWeapon;
		Weapon* defaultWeapon; // The pistol.
		void DrawPlayer();
		void Move();
		float speed;
		float diagnolSpeed;
		Texture2D GetTexture2D();
		Direction shootDirection;
		Direction moveDirection;
		Rectangle GetHitBoxLoc();
		int width = 20;
		int height = 50;
	private:
};

#endif
