#include "player.h"

Player::Player()
{
	speed = 3.5f;
	diagnolSpeed = GareGames::ConvertToDiagnol(speed);
}

void Player::DrawPlayer()
{
	DrawTexture(GetTexture2D(), position.x , position.y, WHITE);
}

Texture2D Player::GetTexture2D()
{
	return TextureList::textureMap["player"]; 
}

void Player::Move()
{
	bool moveFirst = false;
	bool moveSecond = false;
	if (moveDirection == Direction::UP)
	{
		if (position.y > 5)
			position.y -= speed;
	}
	else if (moveDirection == Direction::DOWN)
	{
		if (position.y < 527)
			position.y += speed;
	}
	else if (moveDirection == Direction::LEFT)
	{
		if (position.x > 24)
			position.x -= speed;
	}
	else if (moveDirection == Direction::RIGHT)
	{
		if (position.x < 758)
			position.x += speed;
	}
	else if (moveDirection == Direction::DOWNLEFT)
	{
		if (position.x > 24) moveFirst = true;
		if (position.y < 527) moveSecond = true;

		if (moveFirst && !moveSecond)
		{
			position.x -= speed;
		}
		else if(!moveFirst && moveSecond)
		{
			position.y += speed;
		}
		else if (moveFirst && moveSecond)
		{
			position.x -= diagnolSpeed;
			position.y += diagnolSpeed;
		}
			

	}
	else if (moveDirection == Direction::DOWNRIGHT)
	{
		if (position.x < 758) moveFirst = true;
		if (position.y < 527) moveSecond = true;

		if (moveFirst && !moveSecond)
		{
			position.x += speed;
		}
		else if(!moveFirst && moveSecond)
		{
			position.y += speed;
		}
		else if (moveFirst && moveSecond)
		{
			position.x += diagnolSpeed;
			position.y += diagnolSpeed;
		}
	}
	else if (moveDirection == Direction::UPLEFT)
	{
		if (position.x > 24) moveFirst = true;
		if (position.y > 5) moveSecond = true;

		if (moveFirst && !moveSecond)
		{
			position.x -= speed;
		}
		else if(!moveFirst && moveSecond)
		{
			position.y -= speed;
		}
		else if (moveFirst && moveSecond)
		{
			position.x -= diagnolSpeed;
			position.y -= diagnolSpeed;
		}
	}
	else if (moveDirection == Direction::UPRIGHT)
	{
		if (position.x < 758) moveFirst = true;
		if (position.y > 5) moveSecond = true;

		if (moveFirst && !moveSecond)
		{
			position.x += speed;
		}
		else if(!moveFirst && moveSecond)
		{
			position.y -= speed;
		}
		else if (moveFirst && moveSecond)
		{
			position.x += diagnolSpeed;
			position.y -= diagnolSpeed;
		}
	}
}
