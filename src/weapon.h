#ifndef WEAPON_H
#define WEAPON_H

#include "raylib.h"
#include "garegames.h"

class Player;
class Weapon {
	public:
		Player* player;
		virtual void Trigger();
		virtual void Update(float frameTime);
		virtual void DrawWeapon();
		virtual Vector2 WeaponExitPosition(Vector2 position, Direction shootDirection);
		float shotTimer;
		float reloadTimer;
		float shotCooldown;
		float reloadCooldown;
		int rndsPerReload = 7;
		int rounds;
		bool bTriggerReload = false;
};

#endif
