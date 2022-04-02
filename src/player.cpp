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
	if (moveDirection == Direction::UP)
	{
		position.y -= speed;
	}
	else if (moveDirection == Direction::DOWN)
	{
		position.y += speed;
	}
	else if (moveDirection == Direction::LEFT)
	{
		position.x -= speed;
	}
	else if (moveDirection == Direction::RIGHT)
	{
		position.x += speed;
	}
	else if (moveDirection == Direction::DOWNLEFT)
	{
		position.x -= diagnolSpeed;
		position.y += diagnolSpeed;
	}
	else if (moveDirection == Direction::DOWNRIGHT)
	{
		position.x += diagnolSpeed;
		position.y += diagnolSpeed;
	}
	else if (moveDirection == Direction::UPLEFT)
	{
		position.x -= diagnolSpeed;
		position.y -= diagnolSpeed;
	}
	else if (moveDirection == Direction::UPRIGHT)
	{
		position.x += diagnolSpeed;
		position.y -= diagnolSpeed;
	}
}
