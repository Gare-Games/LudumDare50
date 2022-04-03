#include "fastenemy.h"

FastEnemy::FastEnemy(Vector2 startPosition, Player* target) : Enemy::Enemy({startPosition, target})
{
	this->hitpoints = 10.0f;
}

Texture2D FastEnemy::GetTexture2D()
{
	return TextureList::textureMap["enemy3"]; 
}
