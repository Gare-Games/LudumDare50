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
		Vector2 position;
		Weapon* currentWeapon;
		void DrawPlayer();
		Texture2D GetTexture2D();
		Direction shootDirection;
		Direction moveDirection;
	private:
};

#endif
