#include "cash.h"

void Cash::GetItem()
{
	GlobalVars::score = GlobalVars::score + 50;
	bDead = true;
	PlaySound(SoundList::soundMap["getCash"]);
}
