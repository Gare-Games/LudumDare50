#include "bulletlist.h"

vector<Bullet*> BulletList::bullets;

void BulletList::Initialize()
{
}
void BulletList::RemoveBullet()
{
}
void BulletList::AddBullet(Bullet* bullet)
{
	bullets.push_back(bullet);
}
