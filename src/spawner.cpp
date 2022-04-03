#include "spawner.h"


SpawnJob::SpawnJob(EnemyType enemyType, SpawnLocation location, int amount, float startTime, float interval)
{
	this->enemyType = enemyType;	
	this->location = location;	
	this->amount = amount;	
	this->startTime = startTime;	
	this->interval = interval;	
	this->startTimer = startTime;	
	this->intervalTimer = interval;	
}
void SpawnJob::Update(float frameTime)
{
	if(!bStart)
	{
		startTimer = max(0.0f, startTimer-frameTime);
		if (startTimer == 0.0f)
		{
			bStart = true;
			TraceLog(LOG_INFO, "Spawner Started");
		}
		else
		{
			TraceLog(LOG_INFO, "Spawner Waiting");
		}
	}
	else
	{
		TraceLog(LOG_INFO, "Attempting to sapwn Enemy");
		TraceLog(LOG_INFO, "Player: %f %f", GlobalVars::player->position.x, GlobalVars::player->position.y);
		intervalTimer = max(0.0f, intervalTimer-frameTime);

		if (intervalTimer == 0.0f)
		{
			Vector2 vector = {0,0};
			switch (location)
			{
				case SpawnLocation::LEFT:
					vector = {3.0f,285.0f};
					break;
				case SpawnLocation::RIGHT:
					vector = {797.0f,285.0f};
					break;
				case SpawnLocation::UP:
					vector = {415.0f,3.0f};
					break;
				case SpawnLocation::DOWN:
					vector = {415.0f,597.0f};
					break;
			}

			switch (enemyType)
			{
				default:
				case EnemyType::Main:
					Enemy* enemy = new Enemy(vector, GlobalVars::player);
					EnemyList::AddEnemy(enemy);
					TraceLog(LOG_INFO, "Enemy Spawned");
					break;
			}
			intervalTimer = interval;
		}
	}
}

Spawner::Spawner()
{
}
void Spawner::Update(float frameTime)
{
	for(SpawnJob* spawnJob : spawnJobs)
	{
		spawnJob->Update(frameTime);
	}
}
void Spawner::AddJob(EnemyType enemyType, SpawnLocation location, int amount, float startTime, float interval)
{	
	TraceLog(LOG_INFO, "Adding Job %i, %i, %f, %f, %f", enemyType, location, amount, startTime, interval);
	SpawnJob* spawnJob = new SpawnJob(enemyType, location, amount, startTime, interval);
	spawnJobs.push_back(spawnJob);
}
void Spawner::Start()
{
}
