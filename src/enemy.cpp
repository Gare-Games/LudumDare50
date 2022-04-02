#include "enemy.h"

Enemy::Enemy(Vector2 startPosition, Player* target)
{
	position.x = startPosition.x;
	position.y = startPosition.y;
	player = target;
}
void Enemy::Update(float frameTime)
{
	// MODE: CHASE
	if (position.x != player->position.x)
	{
		if (position.x < player->position.x)
			position.x++;
		if (position.x > player->position.x)
			position.x--;
		if (position.y < player->position.y)
			position.y++;
		if (position.y > player->position.y)
			position.y--;
	}
	// MODE: Stumble
	
}

void Enemy::Draw()
{
	if (!bDead)
		DrawTexture(GetTexture2D(), position.x , position.y, WHITE);
}

Texture2D Enemy::GetTexture2D()
{
	return TextureList::textureMap["enemy"]; 
}
Rectangle Enemy::GetHitBoxLoc()
{
	return {position.x, position.y, width, height};
}
