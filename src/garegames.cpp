#include "garegames.h"


// This draws the texture and repeats it as many times as you want.
void GareGames::DrawTextureRect(Texture2D texture, int posX, int posY, int width, int height, Color tint)
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
			DrawTexture(texture, posX + (i*texture.width), posY + (j*texture.height), tint);
		}
	}


	for (int j = 0; j < repeatCntY; j++)
	{
		DrawTextureRec(texture, {0,0,extraX,texture.height}, {posX + (repeatCntX*texture.width), posY + (j*texture.height)}, tint);
	}

	for (int i = 0; i < repeatCntX; i++)
	{
		DrawTextureRec(texture, {0,0,texture.width,extraY}, {posX + (i*texture.width), posY + (repeatCntY*texture.height)}, tint);
	}

	DrawTextureRec(texture, {0,0,extraX,extraY}, {posX + (repeatCntX*texture.width), posY + (repeatCntY*texture.height)}, tint);
}
