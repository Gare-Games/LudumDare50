#ifndef PISTOL_H
#define PISTOL_H

#include "weapon.h"
#include "player.h"
#include <algorithm>

using namespace std;

class Pistol : public Weapon {
	public: 
		Pistol(Player* playerInput);
		void Trigger();
		void Update(float frameTime);
		void DrawWeapon();
};

#endif
