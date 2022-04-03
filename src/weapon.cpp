#include "weapon.h"

void Weapon::Trigger()
{
}
void Weapon::Update(float frameTime)
{
}
void Weapon::DrawWeapon()
{
}
Vector2 Weapon::WeaponExitPosition(Vector2 position, Direction shootDirection)
{
	return {position.x, position.y};
}

Texture2D Weapon::GetWeaponIconTexture2D()
{
	return TextureList::textureMap[weaponName]; 
}
