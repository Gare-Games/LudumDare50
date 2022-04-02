#include "pistol.h"


Pistol::Pistol(Player* playerInput)
{
	shotTimer = 0.0f;
	//Constant?
	shotCooldown = 0.5f;
	reloadTimer = 0.0f;
	reloadCooldown = 1.0f;
	player = playerInput;
}
void Pistol::Trigger()
{
	if (shotTimer == 0 && rounds != 0)
	{
		shotTimer = shotCooldown;
		rounds--;
		// Spawn bullet at player location.
	}
}
void Pistol::Update(float frameTime)
{
	shotTimer -= max(0.0f, shotTimer-frameTime);
}
void Pistol::DrawWeapon()
{
}
