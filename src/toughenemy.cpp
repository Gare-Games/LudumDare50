#include "toughenemy.h"

ToughEnemy::ToughEnemy(Vector2 startPosition, Player* target) : Enemy::Enemy({startPosition, target})
{
	this->hitpoints = 10.0f;
}

Texture2D ToughEnemy::GetTexture2D()
{
	return TextureList::textureMap["enemy2"]; 
}
