#include "garegames.h"


// This draws the texture and repeats it as many times as you want.
void GareGames::DrawTextureRect(Texture2D texture, Vector2 position, int width, int height, Color tint)
{
	int repeatCntX = width/texture.width;
	int repeatCntY = height/texture.height;
	int extraX = width % texture.width;
	int extraY = height % texture.height;

	//TraceLog(LOG_INFO, TextFormat("RepX: %i RepY: %i ExX: %i ExY: %i", repeatCntX, repeatCntY, extraX, extraY));

	for (int i = 0; i < repeatCntX; i++)
	{
		for (int j = 0; j < repeatCntY; j++)
		{
			DrawTexture(texture, position.x + (i*texture.width), position.y + (j*texture.height), tint);
		}
	}


	for (int j = 0; j < repeatCntY; j++)
	{
		DrawTextureRec(texture, {0,0,extraX,texture.height}, {position.x + (repeatCntX*texture.width), position.y + (j*texture.height)}, tint);
	}

	for (int i = 0; i < repeatCntX; i++)
	{
		DrawTextureRec(texture, {0,0,texture.width,extraY}, {position.x + (i*texture.width), position.y + (repeatCntY*texture.height)}, tint);
	}

	DrawTextureRec(texture, {0,0,extraX,extraY}, {position.x + (repeatCntX*texture.width), position.y + (repeatCntY*texture.height)}, tint);
}
void GareGames::DrawTextureRect(Texture2D texture, float posX, float posY, int width, int height, Color tint)
{
	GareGames::DrawTextureRect(texture, {posX, posY}, width, height, tint);
}
