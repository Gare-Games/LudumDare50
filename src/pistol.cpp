#include "pistol.h"
#include "bulletlist.h"


Pistol::Pistol(Player* playerInput)
{
	shotTimer = 0.0f;
	//Constant?
	shotCooldown = 0.125f;
	reloadTimer = 0.0f;
	reloadCooldown = 1.00f;
	player = playerInput;
	rounds = rndsPerReload;
}
void Pistol::Trigger()
{
	if (shotTimer == 0.0f && rounds != 0)
	{
		shotTimer = shotCooldown;
		rounds--;
		// Spawn bullet at player location.
		Bullet* bullet = new Bullet({player->position.x, player->position.y}, player->shootDirection);

		BulletList::AddBullet(bullet);
		
		bTriggerReload = true;
	}
	else if (bTriggerReload)
	{
		reloadTimer = reloadCooldown;
		bTriggerReload = false;
	}
	else if (rounds == 0 && reloadTimer == 0.0f)
	{
		rounds = rndsPerReload;
	}
	else
	{
	}
}
void Pistol::Update(float frameTime)
{
	shotTimer = max(0.0f, shotTimer-frameTime);
	reloadTimer = max(0.0f, reloadTimer-frameTime);
}
void Pistol::DrawWeapon()
{
}
