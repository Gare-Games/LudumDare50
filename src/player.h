#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "texturelist.h"
#include "weapon.h"
#include "pistol.h"

using namespace std;

class Player {
	public:
		Vector2 position;
		Weapon* currentWeapon;
		void DrawPlayer();
		Texture2D GetTexture2D();
		bool shootUp = false;
		bool shootLeft = false;
		bool shootRight = false;
		bool shootDown = false;
		bool shootUpLeft = false; 
		bool shootUpRight = false; 
		bool shootDownLeft = false; 
		bool shootDownRight = false; 

		bool moveUp = false;
		bool moveLeft = false;
		bool moveRight = false;
		bool moveDown = false;
		bool moveUpLeft = false; 
		bool moveUpRight = false; 
		bool moveDownLeft = false; 
		bool moveDownRight = false; 
	private:
};

#endif
