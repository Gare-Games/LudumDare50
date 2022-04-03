#include "level.h"

Level::Level()
{
	spawner = new Spawner();
}

void Level::Start()
{
	bStart = true;
}

void Level::Stop()
{
	bStart = false;
}

void Level::Update(float frameTime)
{
	if(bStart)
		spawner->Update(frameTime);	
}
void Level::AddSpawnJob(EnemyType enemyType, SpawnLocation location, int amount, float startTime, float interval)
{
	spawner->AddJob(enemyType, location, amount, startTime, interval);
}
