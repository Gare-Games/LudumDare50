#ifndef WEAPON_H
#define WEAPON_H

#include "raylib.h"
#include "garegames.h"
#include <string>
#include "texturelist.h"

using namespace std;

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
		int rndsPerReload;
		int rounds;
		bool bTriggerReload = false;
		string weaponName;
		string weaponIconTexture;
		Texture2D GetWeaponIconTexture2D();
};

#endif
