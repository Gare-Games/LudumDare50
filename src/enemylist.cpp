#include "enemylist.h"

vector<Enemy*> EnemyList::enemys;

void EnemyList::Initialize()
{
}
void EnemyList::RemoveEnemy()
{
}
void EnemyList::AddEnemy(Enemy* enemy)
{
	enemys.push_back(enemy);
}

void EnemyList::CleanUp()
{
	vector<Enemy*> newList;
	for(Enemy* enemy : enemys)
	{
		if(!enemy->bDead)
			newList.push_back(enemy);
	}
	enemys = newList;
	//enemys.clear();
	//enemys.insert(enemys.end(), newList.begin(), newList.end());
}
