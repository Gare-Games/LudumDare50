#ifndef RIFLE_H
#define RIFLE_H

#include "weapon.h"
#include "player.h"
#include "garegames.h"
#include <algorithm>

using namespace std;

class Rifle : public Weapon {
	public: 
		Rifle(Player* playerInput);
		void Trigger();
		void Update(float frameTime);
		void DrawWeapon();
		Vector2 WeaponExitPosition(Vector2 position, Direction shootDirection);
};

#endif
