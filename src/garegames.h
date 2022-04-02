/**
 * Purpose of this file is to extend some of the raylib functions.
 * For example there is no repeating DrawTexture module.
 *
 */

#include "raylib.h"

class GareGames
{
	public:
		// The purpose of this is to repeat until it fills up the whole width.
		// The way we will accomplish this is by iterating... a lot.
		static void DrawTextureRect(Texture2D texture, Vector2 position, int width, int height, Color tint);
		static void DrawTextureRect(Texture2D texture, float posX, float posY, int width, int height, Color tint);
};
