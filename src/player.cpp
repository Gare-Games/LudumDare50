#include "player.h"

void Player::DrawPlayer()
{
	DrawTexture(GetTexture2D(), position.x , position.y, WHITE);
}

Texture2D Player::GetTexture2D()
{
	return TextureList::textureMap["player"]; 
}
