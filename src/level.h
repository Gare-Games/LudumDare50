#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "spawner.h"

class Level
{
	public:
		Level();
		Spawner* spawner;
		void Start();
		void Stop();
		void Reset();
		void Update(float frameTime);
		void AddSpawnJob(EnemyType enemyType, SpawnLocation location, int amount, float startTime, float interval);
		bool bStart = false;
};

#endif
