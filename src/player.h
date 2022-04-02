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
	private:
};

#endif
