#ifndef ENEMYLIST_H
#define ENEMYLIST_H

#include <vector>
#include <string>
#include "raylib.h"
#include "enemy.h"

using namespace std;

class EnemyList {
	public:
		static void Initialize();
		static vector<Enemy*> enemys;
		static void RemoveEnemy();
		static void AddEnemy(Enemy* enemy);
		static void CleanUp();
	private:
};

#endif
