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
	if(bDone) return;

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
		}
	}
	else
	{
		intervalTimer = max(0.0f, intervalTimer-frameTime);

		if (intervalTimer == 0.0f)
		{
			Vector2 vector = {0,0};
			Vector2 targetMove = {0,0};
			switch (location)
			{
				case SpawnLocation::LEFT:
					vector = {3.0f,285.0f};
					targetMove = {80.0f,285.0f};
					break;
				case SpawnLocation::RIGHT:
					vector = {797.0f,285.0f};
					targetMove = {717.0f,285.0f};
					break;
				case SpawnLocation::UP:
					vector = {415.0f,3.0f};
					targetMove = {415.0f,73.0f};
					break;
				case SpawnLocation::DOWN:
					vector = {415.0f,597.0f};
					targetMove = {415.0f,527.0f};
					break;
			}

			switch (enemyType)
			{
				default:
				case EnemyType::Main:
					Enemy* enemy = new Enemy(vector, GlobalVars::player);
					enemy->mode= EnemyMode::MOVETO;
					enemy->SetMoveTarget(targetMove);
					EnemyList::AddEnemy(enemy);
					spawned++;
					break;
			}
			intervalTimer = interval;

			if (spawned == amount) bDone = true;
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
