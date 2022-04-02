#include "pistol.h"
#include "bulletlist.h"


Pistol::Pistol(Player* playerInput)
{
	shotTimer = 0.0f;
	//Constant?
	shotCooldown = 0.125f;
	reloadTimer = 0.0f;
	reloadCooldown = 1.0f;
	player = playerInput;
}
void Pistol::Trigger()
{
	//if (shotTimer == 0 && rounds != 0)
	if (shotTimer == 0 )
	{
		shotTimer = shotCooldown;
		rounds--;
		// Spawn bullet at player location.
		Bullet* bullet = new Bullet({player->position.x, player->position.y}, player->shootDirection);

		BulletList::AddBullet(bullet);
		TraceLog(LOG_INFO, TextFormat("BULLET MADE!"));
	}
}
void Pistol::Update(float frameTime)
{
	shotTimer = max(0.0f, shotTimer-frameTime);
	if (shotTimer > 0.0f)
		TraceLog(LOG_INFO, TextFormat("ShotTimer: %f", shotTimer));
}
void Pistol::DrawWeapon()
{
}
