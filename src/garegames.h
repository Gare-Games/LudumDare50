/**
 * Purpose of this file is to extend some of the raylib functions.
 * For example there is no repeating DrawTexture module.
 *
 */

#ifndef GAREGAMES_H
#define GAREGAMES_H

#include "raylib.h"
#include <cmath>

using namespace std;


enum class Direction {
	// Look at your numpad.
	UP = 8,
	DOWN = 2,
	LEFT = 4,
	RIGHT = 6,
	UPLEFT = 7,
	UPRIGHT = 9,
	DOWNLEFT = 1,
	DOWNRIGHT = 3
};

class GareGames
{
	public:
		// The purpose of this is to repeat until it fills up the whole width.
		// The way we will accomplish this is by iterating... a lot.
		static float ConvertToDiagnol(float speed);
		static void DrawTextureRect(Texture2D texture, Vector2 position, int width, int height, Color tint);
		static void DrawTextureRect(Texture2D texture, float posX, float posY, int width, int height, Color tint);
};

#endif
