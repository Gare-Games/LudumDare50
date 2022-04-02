#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "texturelist.h"

using namespace std;

class Player {
	public:
		Vector2 position;
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
	private:
};

#endif
