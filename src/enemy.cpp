#include "enemy.h"

Enemy::Enemy(Vector2 startPosition, Player* target)
{
	position.x = startPosition.x;
	position.y = startPosition.y;
	player = target;
	mode = EnemyMode::CHASE;
	diagnolSpeed = GareGames::ConvertToDiagnol(speed);
	hitpoints = 1.0f;
}
void Enemy::Update(float frameTime)
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	float xDiff;
	float yDiff;
	// MODE: CHASE
	switch (mode)
	{
		case EnemyMode::CHASE:
			if (position.x != player->position.x || position.y != player->position.y)
			{
				if (position.x < player->position.x)
					right = true;
				if (position.x > player->position.x)
					left = true;
				if (position.y < player->position.y)
					down = true;
				if (position.y > player->position.y)
					up = true;
				Move(up, down, left, right);

			}
			break;
		case EnemyMode::MOVETO:
				if (position.x < targetMove.x)
					right = true;
				if (position.x > targetMove.x)
					left = true;
				if (position.y < targetMove.y)
					down = true;
				if (position.y > targetMove.y)
					up = true;

				if (up && right)
				{
					if ((targetMove.x - position.x) < diagnolSpeed)
						position.x = targetMove.x;
					else
						position.x += diagnolSpeed;
					if (position.y - targetMove.y < diagnolSpeed)
					{
						position.y = targetMove.y;
					}
					else
						position.y -= diagnolSpeed;
				}
				else if (up && left)
				{
					if ((position.x - targetMove.x) < diagnolSpeed)
					{
						
						position.x = targetMove.x;
					}
					else
						position.x -= diagnolSpeed;
					if (position.y - targetMove.y < diagnolSpeed)
					{
						position.y = targetMove.y;
					}
					else
						position.y -= diagnolSpeed;
				}
				else if (down && right)
				{
					if ((targetMove.x - position.x) < diagnolSpeed)
						position.x = targetMove.x;
					else
						position.x += diagnolSpeed;
					if (targetMove.y - position.y < diagnolSpeed)
					{
						position.y = targetMove.y;
					}
					else
						position.y += diagnolSpeed;
				}
				else if (down && left)
				{
					if ((targetMove.x - position.x) < diagnolSpeed)
						position.x = targetMove.x;
					else
						position.x += diagnolSpeed;
					if (targetMove.y - position.y < diagnolSpeed)
					{
						position.y = targetMove.y;
					}
					else
						position.y += diagnolSpeed;
				}
				else if (up)
				{
					
					if (position.y - targetMove.y < speed)
					{
						position.y = targetMove.y;
					}
					else
						position.y -= speed;
				}
				else if (down)
				{
					if (targetMove.y - position.y < speed)
					{
						position.y = targetMove.y;
					}
					else
						position.y += speed;
				}
				else if (right)
				{
					if ((targetMove.x - position.x) < speed)
					{
						
						position.x = targetMove.x;
					}
					else
						position.x += speed;
				}
				else if (left)
				{
					if ((position.x - targetMove.x) < speed)
					{
						
						position.x = targetMove.x;
					}
					else
						position.x -= speed;
				}

				if (!(up || down || left || right))
				{
					mode = EnemyMode::CHASE;
				}
			break;
	}
	// MODE: Stumble
	
}

void Enemy::Move(bool up, bool down, bool left, bool right)
{
	if (up && right)
	{
		position.x += diagnolSpeed;
		position.y -= diagnolSpeed;
	}
	else if (up && left)
	{
		position.x -= diagnolSpeed;
		position.y -= diagnolSpeed;
	}
	else if (down && right)
	{
		position.x += diagnolSpeed;
		position.y += diagnolSpeed;
	}
	else if (down && left)
	{
		position.x -= diagnolSpeed;
		position.y += diagnolSpeed;
	}
	else if (up)
	{
		position.y -= diagnolSpeed;
	}
	else if (down)
	{
		position.y += diagnolSpeed;
	}
	else if (right)
	{
		position.x += diagnolSpeed;
	}
	else if (left)
	{
		position.x -= diagnolSpeed;
	}
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

Rectangle Enemy::GetAttackBoxLoc()
{
	return {position.x+5, position.y+ 25, width-10, 25};
}

void Enemy::TakeDamage(float amount)
{
	hitpoints -= amount;
	if (hitpoints <= 0.0f)
		bDead = true;
}
