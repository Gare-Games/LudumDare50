#include "rifle.h"
#include "bulletlist.h"
#include "soundlist.h"
#include "garegames.h"


Rifle::Rifle(Player* playerInput)
{
	shotTimer = 0.0f;
	//Constant?
	shotCooldown = 0.25f;
	reloadTimer = 0.0f;
	reloadCooldown = 0.75f;
	player = playerInput;
	rndsPerReload = 20;
	rounds = rndsPerReload;
	weaponName = "Rifle";
	weaponIconTexture = "rifleIcon";
}

void Rifle::Trigger()
{
	if (bTriggerReload)
	{
		reloadTimer = reloadCooldown;
		bTriggerReload = false;
		rounds = 0;
	}
	else if (shotTimer == 0.0f && rounds != 0)
	{
		shotTimer = shotCooldown;
		rounds--;
		// Spawn bullet at player location.
		Bullet* bullet = new Bullet(WeaponExitPosition(player->position, player->shootDirection), player->shootDirection);
		bullet->damage = 2.0f;

		BulletList::AddBullet(bullet);

			PlaySound(SoundList::soundMap["shoot"]);
		if (rounds == 0)
		{
			PlaySound(SoundList::soundMap["blockEnd"]);
			reloadTimer = reloadCooldown;
		}
	}
	else if (rounds == 0 && reloadTimer == 0.0f)
	{
		rounds = rndsPerReload;
	}
	else
	{
	}
}

void Rifle::Update(float frameTime)
{
	shotTimer = max(0.0f, shotTimer-frameTime);
	reloadTimer = max(0.0f, reloadTimer-frameTime);
	if (reloadTimer == 0.0f && rounds == 0)
	{
		rounds = rndsPerReload;
	}
}

void Rifle::DrawWeapon()
{
}

Vector2 Rifle::WeaponExitPosition(Vector2 position, Direction shootDirection)
{
	switch(shootDirection)
	{
		case Direction::LEFT:
			return {position.x + 0, position.y + 13};
		case Direction::RIGHT:
			return {position.x + 18, position.y + 13};
		case Direction::UP:
			return {position.x + 9, position.y + 1};
		case Direction::DOWN:
			return {position.x + 9, position.y + 25};
		case Direction::UPLEFT:
			return {position.x + 2, position.y + 7};
		case Direction::UPRIGHT:
			return {position.x + 16, position.y + 7};
		case Direction::DOWNLEFT:
			return {position.x + 2, position.y + 19};
		case Direction::DOWNRIGHT:
			return {position.x + 16, position.y + 19};
		default:
			return position;
	}
}
