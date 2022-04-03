#include "rifleitem.h"


void RifleItem::GetItem()
{
	bDead = true;
	PlaySound(SoundList::soundMap["getCash"]);
	// Create Rifle Object.
	Rifle* rifle = new Rifle(GlobalVars::player);
	GlobalVars::player->currentWeapon = rifle;
}
