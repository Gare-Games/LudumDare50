#ifndef SPAWNER_H
#define SPAWNER_H

#include "raylib.h"
#include "enemylist.h"
#include "globalvars.h"


enum class EnemyType { 
	Main = 1 
};

enum class SpawnLocation { 
	LEFT = 1 ,
	RIGHT = 2 ,
	UP = 3 ,
	DOWN = 4
};

class SpawnJob
{
	public:
		SpawnJob(EnemyType enemyType, SpawnLocation location, int amount, float startTime, float interval);
		EnemyType enemyType;
		SpawnLocation location;
		int amount;
		float startTimer;
		float startTime;
		float intervalTimer;
		float interval;
		bool bStart = false;
		void Update(float frameTime);
};

class Spawner
{
	public:
		Spawner();
		vector<SpawnJob*> spawnJobs;
		// Spawn what when at what rate?
		// Spawn 5 bungos at 0, every 0.125 seconds,
		// This allows you to define a level with a simple jobs.
		void AddJob(EnemyType enemyType, SpawnLocation location, int amount, float startTime, float interval);
		void Start();
		void Update(float frameTime);
	
};


#endif
