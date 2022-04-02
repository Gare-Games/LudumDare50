#ifndef WEAPON_H
#define WEAPON_H

class Player;
class Weapon {
	public:
		Player* player;
		virtual void Trigger();
		virtual void Update(float frameTime);
		virtual void DrawWeapon();
};

#endif
