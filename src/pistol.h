#ifndef PISTOL_H
#define PISTOL_H

#include "weapon.h"
#include "player.h"
#include "garegames.h"
#include <algorithm>

using namespace std;

class Pistol : public Weapon {
	public: 
		Pistol(Player* playerInput);
		void Trigger();
		void Update(float frameTime);
		void DrawWeapon();
		Vector2 WeaponExitPosition(Vector2 position, Direction shootDirection);
};

#endif
