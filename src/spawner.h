#ifndef SPAWNER_H
#define SPAWNER_H

#include "raylib.h"
#include "enemylist.h"
#include "itemlist.h"
#include "globalvars.h"
#include "enemy.h"
#include "item.h"
#include "cash.h"
#include "rifleitem.h"
#include "toughenemy.h"
#include "garegames.h"

// Spawn anything.
enum class EnemyType { 
	Main, 
	Tough,
	ITEM_Rifle,
	ITEM_Cash,
	ITEM_PistolDmg,
	ITEM_PistolMagSize,
	ITEM_EXPLODEMAP,
	ITEM_SHIELD,
	ITEM_RANDOM
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
		int spawned = 0;
		float startTimer;
		float startTime;
		float intervalTimer;
		float interval;
		bool bStart = false;
		bool bDone = false;
		void Update(float frameTime);
		void Reset();
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
		void Reset();
		void Update(float frameTime);
	
};


#endif
