#include "enemy.h"

Enemy::Enemy(Vector2 startPosition, Player* target)
{
	position.x = startPosition.x;
	position.y = startPosition.y;
	player = target;
	mode = EnemyMode::CHASE;
}
void Enemy::Update(float frameTime)
{
	// MODE: CHASE
	switch (mode)
	{
		case EnemyMode::CHASE:
			if (position.x != player->position.x || position.y != player->position.y)
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
			break;
		case EnemyMode::MOVETO:
			
			if (position.x == targetMove.x && position.y == targetMove.y)
				mode = EnemyMode::CHASE;
			else
			{
				if (position.x < targetMove.x)
					position.x++;
				if (position.x > targetMove.x)
					position.x--;
				if (position.y < targetMove.y)
					position.y++;
				if (position.y > targetMove.y)
					position.y--;
			}
			break;
	}
	// MODE: Stumble
	
}
void Enemy::SetMoveTarget(Vector2 position)
{
	targetMove.x = position.x;
	targetMove.y = position.y;
}

void Enemy::Draw()
{
	DrawTexture(GetTexture2D(), position.x , position.y, WHITE);
}

Texture2D Enemy::GetTexture2D()
{
	return TextureList::textureMap["enemy"]; 
}
Rectangle Enemy::GetHitBoxLoc()
{
	return {position.x+5, position.y+ 10, width-10, 40};
}
