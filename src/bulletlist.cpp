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
	TraceLog(LOG_INFO, TextFormat("BULLET Addedt o list"));
	bullets.push_back(bullet);
}
