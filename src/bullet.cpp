#include "bullet.h"

Bullet::Bullet(Vector2 startPosition, Direction targetDirection)
{
	
	position.x = startPosition.x;
	position.y = startPosition.y;
	direction = targetDirection;
	width = 5;
	height = 5;
	speed = 5.0f;
	diagnolSpeed = GareGames::ConvertToDiagnol(speed);
}

void Bullet::Update(float frameTime)
{
	lastPosition.x = position.x;
	lastPosition.y = position.y;
	

	if (direction == Direction::UP)
	{
		position.y -= speed;
	}
	else if (direction == Direction::DOWN)
	{
		position.y += speed;
	}
	else if (direction == Direction::LEFT)
	{
		position.x -= speed;
	}
	else if (direction == Direction::RIGHT)
	{
		position.x += speed;
	}
	else if (direction == Direction::DOWNLEFT)
	{
		position.x -= diagnolSpeed;
		position.y += diagnolSpeed;
	}
	else if (direction == Direction::DOWNRIGHT)
	{
		position.x += diagnolSpeed;
		position.y += diagnolSpeed;
	}
	else if (direction == Direction::UPLEFT)
	{
		position.x -= diagnolSpeed;
		position.y -= diagnolSpeed;
	}
	else if (direction == Direction::UPRIGHT)
	{
		position.x += diagnolSpeed;
		position.y -= diagnolSpeed;
	}
}

void Bullet::Draw()
{
	DrawRectangle(position.x, position.y, width, height, DB32_BLACK);
}
