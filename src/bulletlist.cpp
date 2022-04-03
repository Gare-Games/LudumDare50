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

void BulletList::CleanUp()
{
	vector<Bullet*> newList;
	for(Bullet* bullet : bullets)
	{
		
		TraceLog(LOG_INFO, "BulletBDead:CleanUp: %i", bullet->bDead);
		if(!bullet->bDead)
		{
			newList.push_back(bullet);
		}
	}
	bullets = newList;
}
