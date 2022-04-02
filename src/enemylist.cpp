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
