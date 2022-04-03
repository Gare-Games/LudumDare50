#include "item.h"

void Item::Update(float frameTime)
{
	if(!bDead)
	{
		duration = max(0.0f, duration-frameTime);
		if (duration == 0.0f)
		{
			bDead = true;
		}
	}
}

void Item::Draw()
{
	DrawTexture(GetTexture2D(), position.x , position.y, WHITE);
}

Texture2D Item::GetTexture2D()
{
	return TextureList::textureMap["player"]; 
}
